#include "triangleRenderer.h"
#include <limits.h>
#include <stdio.h>

extern int16_t depthBuffer[];

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
	int16_t area, point3d_t *depths) {
		
	int16_t e0, e1, e2;
	srect_t *renderRect;
	int16_t x, y;
	uint16_t bufferAddr;
	uint8_t r, g, b;
	int16_t depth;
		
	point2d_t p;
	
	renderRect = getCurrentRenderingBoundingBox(triangle, tileRect);
	
	for(y = renderRect->y0; y < renderRect->y1; y++) {
		for(x = renderRect->x0; x < renderRect->x1; x++) {
			p.x = x;
			p.y = y;
			
			e0 = EDGE_FUNCTION(triangle->a[1],triangle->a[2],p);
			e1 = EDGE_FUNCTION(triangle->a[2],triangle->a[0],p);
			e2 = EDGE_FUNCTION(triangle->a[0],triangle->a[1],p);
			
			if(e0 >= 0 && e1 >= 0 && e2 >= 0) {
				
				r = (e0 * color1->r + e1 * color2->r + e2 * color3->r) / area;
				g = (e0 * color1->g + e1 * color2->g + e2 * color3->g) / area;
				b = (e0 * color1->b + e1 * color2->b + e2 * color3->b) / area;
				
				bufferAddr = TILE_RES_Y * (x - tileRect->x0) + (y - tileRect->y0);				
				
#ifdef Z_BUFFERING
				depth = (e0 * depths->x + e1 * depths->y + e2 * depths->z) / area;
	
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
