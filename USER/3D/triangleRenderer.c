#include "triangleRenderer.h"
#include <limits.h>
#include <stdio.h>

extern int16_t depthBuffer[];

#define CROSS_PRODUCT(x,y,p2,p3) \
	(((x) - (p3).x) * ((p2).y - (p3).y) - ((p2).x - (p3).x) * ((y) - (p3).y))
#define INTERPOLATE_COLOR_COMPONENT(c0,c1,c2,e0,e1,e2,area) \
	(int32_t)((e0) * (c0) + (e1) * (c1) + (e2) * (c2)) / (area)
#define INTERPOLATE_DEPTH(depths,e0,e1,e2,area) \
	(int32_t)((e0) * (depths)->z + (e1) * (depths)->x + (e2) * (depths)->y) / (area)

__inline srect_t *getTriangleBoundingBox(triangle2d_t *triangle);
__inline srect_t *getTriangleAndTileIntersectedBoundingBox(srect_t *triangleBB, rect_t *tileBB);
__inline srect_t *getCurrentRenderingBoundingBox(triangle2d_t *triangle, rect_t *tileRect);

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
			e0 = CROSS_PRODUCT(x,y,triangle->a[0],triangle->a[1]);
			e1 = CROSS_PRODUCT(x,y,triangle->a[1],triangle->a[2]);
			e2 = CROSS_PRODUCT(x,y,triangle->a[2],triangle->a[0]);
			
			if(e0 <= 0 && e1 <= 0 && e2 <= 0) {
				r = INTERPOLATE_COLOR_COMPONENT(color3->r,color1->r,color2->r,e0,e1,e2,area);
				g = INTERPOLATE_COLOR_COMPONENT(color3->g,color1->g,color2->g,e0,e1,e2,area);
				b = INTERPOLATE_COLOR_COMPONENT(color3->b,color1->b,color2->b,e0,e1,e2,area);
	
				bufferAddr = TILE_RES_X * (y - tileRect->y0) + (x - tileRect->x0);				
				
#ifdef Z_BUFFERING
				depth = INTERPOLATE_DEPTH(depths, e0, e1, e2, area);
	
				if(depth < depthBuffer[bufferAddr]) {
					depthBuffer[bufferAddr] = depth;
					frameBuffer[bufferAddr] = RGB565(r,g,b);
				}
#else
				frameBuffer[bufferAddr] = RGB565(r,g,b);
#endif // Z_BUFFERING
			}
		}
	}	
	
	free(renderRect);
}
