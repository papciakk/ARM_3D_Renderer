#include "meshRenderer.h"
#include "lighting.h"
#include "mesh.h"
#include "transformations.h"

extern const uint16_t TILES_CNT;
extern rect_t tileRects[];
extern uint16_t frameBuffer[];

const uint16_t HALF_FULLSCREEN_RES_X = FULLSCREEN_RES_X / 2;
const uint16_t HALF_FULLSCREEN_RES_Y = FULLSCREEN_RES_Y / 2;

__inline void rescaleAttributes(vertex_attr_t *rescaled_va, vertex_attr_t *va);
__inline void rescaleAllAttributes(
	vertex_attr_t *v1In, vertex_attr_t *v2In, vertex_attr_t *v3In,
	vertex_attr_t *v1Out, vertex_attr_t *v2Out, vertex_attr_t *v3Out);
__inline void prepareTriangleVertices(uint16_t triangleId, vertex_attr_t *v1, vertex_attr_t *v2, vertex_attr_t *v3);
__inline int32_t getTriangleArea(vertex_attr_t *v1, vertex_attr_t *v2, vertex_attr_t *v3);

void initMeshRenderer(void) {
	initTileSystem();
}

__inline void rescaleAttributes(vertex_attr_t *rescaled_va, vertex_attr_t *va) {	
	rescaled_va->pos.x = (va->pos.x >> 7) + HALF_FULLSCREEN_RES_X;
	rescaled_va->pos.y = va->pos.y >> 7;
	rescaled_va->pos.z = (va->pos.z >> 7) + HALF_FULLSCREEN_RES_Y;
	
	rescaled_va->normal.x = va->normal.x;
	rescaled_va->normal.y = va->normal.y;
	rescaled_va->normal.z = va->normal.z;
}

__inline void prepareTriangleVertices(uint16_t triangleId, vertex_attr_t *v1, vertex_attr_t *v2, vertex_attr_t *v3) {
	*v1 = vertices[indices[triangleId].a];
	*v2 = vertices[indices[triangleId].b];
	*v3 = vertices[indices[triangleId].c];
}

__inline void rescaleAllAttributes(
	vertex_attr_t *v1In, vertex_attr_t *v2In, vertex_attr_t *v3In,
	vertex_attr_t *v1Out, vertex_attr_t *v2Out, vertex_attr_t *v3Out) {
		
	rescaleAttributes(v1Out, v1In);
	rescaleAttributes(v2Out, v2In);
	rescaleAttributes(v3Out, v3In);
}

__inline void prepareTriangle(vertex_attr_t *v1, vertex_attr_t *v2, vertex_attr_t *v3, triangle2d_t *triangle) {
	triangle->a[0].x = v1->pos.x;
	triangle->a[0].y = v1->pos.z;
	triangle->a[1].x = v2->pos.x;
	triangle->a[1].y = v2->pos.z;
	triangle->a[2].x = v3->pos.x;
	triangle->a[2].y = v3->pos.z;
}

__inline int32_t getTriangleArea(vertex_attr_t *v1, vertex_attr_t *v2, vertex_attr_t *v3) {
	return (v1->pos.x - v2->pos.x) * (v3->pos.z - v2->pos.z) - 
		     (v1->pos.z - v2->pos.z) * (v3->pos.x - v2->pos.x);
}

void renderMesh(void)
{
	uint16_t tileId, triangleId;
	rect_t *currentRect;
	
	triangle2d_t triangle;
	vertex_attr_t v1_raw, v2_raw, v3_raw;
	vertex_attr_t v1_t, v2_t, v3_t;
	vertex_attr_t v1, v2, v3;
	color_t color1, color2, color3;
	int32_t area;
	point3d_t depths;
	
	for(tileId = 0; tileId < TILES_CNT; tileId++) {
		currentRect = &tileRects[tileId];
		
		clearFrameBuffer();
		clearDepthBuffer();
		
		for(triangleId = 0; triangleId < num_indices; triangleId++) {
			prepareTriangleVertices(triangleId, &v1_raw, &v2_raw, &v3_raw);
			transform(&v1_raw, &v1_t);
			transform(&v2_raw, &v2_t);
			transform(&v3_raw, &v3_t);
			rescaleAllAttributes(&v1_t, &v2_t, &v3_t, &v1, &v2, &v3);
			prepareTriangle(&v1, &v2, &v3, &triangle);
			
			calcLightingForTriangle(&v1, &v2, &v3, &color1, &color2, &color3);
			
			depths.x = v1.pos.y; depths.y = v2.pos.y; depths.z = v3.pos.y;
			area = getTriangleArea(&v1, &v2, &v3);
			
			renderTriangle(
				frameBuffer, &triangle, currentRect,
				&color1, &color2, &color3,
				area, &depths
			);
		}
		
		displayFrameBuffer(currentRect);
	}
}
