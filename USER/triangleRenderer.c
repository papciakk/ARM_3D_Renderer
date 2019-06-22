#include "triangleRenderer.h"

srect_t *getTriangleBoundingBox(triangle2d_t *triangle);
srect_t *getTriangleAndTileIntersectedBoundingBox(srect_t *triangleBB, rect_t *tileBB);
srect_t *getCurrentRenderingBoundingBox(triangle2d_t *triangle, rect_t *tileRect);

int32_t crossProduct(int16_t x, int16_t y, point2d_t *p2, point2d_t *p3);


srect_t *getTriangleBoundingBox(triangle2d_t *triangle) {
	srect_t *r = (srect_t *)malloc(sizeof(srect_t));
	r->x0 = minimum3(triangle->a[0].x, triangle->a[1].x, triangle->a[2].x);
	r->y0 = minimum3(triangle->a[0].y, triangle->a[1].y, triangle->a[2].y);
	r->x1 = maximum3(triangle->a[0].x, triangle->a[1].x, triangle->a[2].x);
	r->y1 = maximum3(triangle->a[0].y, triangle->a[1].y, triangle->a[2].y);
	return r;
}

srect_t *getTriangleAndTileIntersectedBoundingBox(srect_t *triangleBB, rect_t *tileBB) {
	srect_t *r = (srect_t *)malloc(sizeof(srect_t));
	r->x0 = maximum2(triangleBB->x0, tileBB->x0);
	r->y0 = maximum2(triangleBB->y0, tileBB->y0);
	r->x1 = minimum2(triangleBB->x1, tileBB->x1);
	r->y1 = minimum2(triangleBB->y1, tileBB->y1);
	return r;
}

srect_t *getCurrentRenderingBoundingBox(triangle2d_t *triangle, rect_t *tileRect) {
	return getTriangleAndTileIntersectedBoundingBox(
		getTriangleBoundingBox(triangle),
		tileRect
	);
}

int32_t crossProduct(int16_t x, int16_t y, point2d_t *p2, point2d_t *p3) {
	return ((x - p3->x) * (p2->y - p3->y) - (p2->x - p3->x) * (y - p3->y));
}

void renderTriangle(uint16_t *frameBuffer, triangle2d_t *triangle, rect_t *tileRect) {
	int32_t e0, e1, e2;
	srect_t *renderRect;
	int16_t x, y;
	
	renderRect = getCurrentRenderingBoundingBox(triangle, tileRect);
	
	for(y = renderRect->y0; y < renderRect->y1; y++) {
		for(x = renderRect->x0; x < renderRect->x1; x++) {
			e0 = crossProduct(x, y, &triangle->a[0], &triangle->a[1]);
			e1 = crossProduct(x, y, &triangle->a[1], &triangle->a[2]);
			e2 = crossProduct(x, y, &triangle->a[2], &triangle->a[0]);
			
			if(e0 <= 0 && e1 <= 0 && e2 <= 0) {
				frameBuffer[TILE_RES_X * (y - tileRect->y0) + (x - tileRect->x0)] = White;
			}
		}
	}
}
