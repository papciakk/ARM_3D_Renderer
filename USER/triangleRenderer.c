#include "triangleRenderer.h"

extern uint16_t depthBuffer[];

__inline srect_t *getTriangleBoundingBox(triangle2d_t *triangle);
__inline srect_t *getTriangleAndTileIntersectedBoundingBox(srect_t *triangleBB, rect_t *tileBB);
__inline srect_t *getCurrentRenderingBoundingBox(triangle2d_t *triangle, rect_t *tileRect);
__inline int32_t crossProduct(int16_t x, int16_t y, point2d_t *p2, point2d_t *p3);
__inline uint8_t interpolateColorComponent(
	uint8_t c0, uint8_t c1, uint8_t c2,
	int32_t e0, int32_t e1, int32_t e2,
	int32_t area);
__inline int32_t interpolateDepth(
	point3d_t *depths, 
	int32_t e0, int32_t e1, int32_t e2, 
	int32_t area);


__inline srect_t *getTriangleBoundingBox(triangle2d_t *triangle) {
	srect_t *r = (srect_t *)malloc(sizeof(srect_t));
	r->x0 = MIN3(triangle->a[0].x,triangle->a[1].x,triangle->a[2].x);
	r->y0 = MIN3(triangle->a[0].y,triangle->a[1].y,triangle->a[2].y);
	r->x1 = MAX3(triangle->a[0].x,triangle->a[1].x,triangle->a[2].x);
	r->y1 = MAX3(triangle->a[0].y,triangle->a[1].y,triangle->a[2].y);
	return r;
}

__inline srect_t *getTriangleAndTileIntersectedBoundingBox(srect_t *triangleBB, rect_t *tileBB) {
	srect_t *r = (srect_t *)malloc(sizeof(srect_t));
	r->x0 = MAX2(triangleBB->x0,tileBB->x0);
	r->y0 = MAX2(triangleBB->y0,tileBB->y0);
	r->x1 = MIN2(triangleBB->x1,tileBB->x1);
	r->y1 = MIN2(triangleBB->y1,tileBB->y1);
	return r;
}

__inline srect_t *getCurrentRenderingBoundingBox(triangle2d_t *triangle, rect_t *tileRect) {
	srect_t *triangleBB = getTriangleBoundingBox(triangle);
	srect_t *r = getTriangleAndTileIntersectedBoundingBox(
		triangleBB,
		tileRect
	);
	free(triangleBB);
	return r;
}

__inline int32_t crossProduct(int16_t x, int16_t y, point2d_t *p2, point2d_t *p3) {
	return ((x - p3->x) * (p2->y - p3->y) - (p2->x - p3->x) * (y - p3->y));
}

__inline uint8_t interpolateColorComponent(
	uint8_t c0, uint8_t c1, uint8_t c2,
	int32_t e0, int32_t e1, int32_t e2,
	int32_t area) {
		
	return (int32_t)(e0 * c0 + e1 * c1 + e2 * c2) / area;
}
	
__inline int32_t interpolateDepth(
	point3d_t *depths, 
	int32_t e0, int32_t e1, int32_t e2, 
	int32_t area) {
	
	return 256 - (int32_t)(e0 * depths->z + e1 * depths->x + e2 * depths->y) / area;
}

void renderTriangle(uint16_t *frameBuffer, triangle2d_t *triangle, rect_t *tileRect,
	color_t *color1, color_t *color2, color_t *color3,
	int32_t area, point3d_t *depths) {
		
	int32_t e0, e1, e2;
	srect_t *renderRect;
	int16_t x, y;
	uint16_t bufferAddr;
	uint8_t r, g, b;
	int32_t depth;
	
	renderRect = getCurrentRenderingBoundingBox(triangle, tileRect);
	
	for(y = renderRect->y0; y < renderRect->y1; y++) {
		for(x = renderRect->x0; x < renderRect->x1; x++) {
			e0 = crossProduct(x, y, &triangle->a[0], &triangle->a[1]);
			e1 = crossProduct(x, y, &triangle->a[1], &triangle->a[2]);
			e2 = crossProduct(x, y, &triangle->a[2], &triangle->a[0]);
			
			if(e0 <= 0 && e1 <= 0 && e2 <= 0) {
				r = interpolateColorComponent(color3->r, color1->r, color2->r, e0, e1, e2, area);
				g = interpolateColorComponent(color3->g, color1->g, color2->g, e0, e1, e2, area);
				b = interpolateColorComponent(color3->b, color1->b, color2->b, e0, e1, e2, area);
				depth = interpolateDepth(depths, e0, e1, e2, area);
				
				bufferAddr = TILE_RES_X * (y - tileRect->y0) + (x - tileRect->x0);
				if(depth + 127 > depthBuffer[bufferAddr]) {
					depthBuffer[bufferAddr] = depth + 127;
					frameBuffer[bufferAddr] = RGB565(r,g,b);
				}
			}
		}
	}
	
	free(renderRect);
}
