#include "meshRenderer.h"
#include "mesh.h"

extern const uint16_t TILES_CNT;
extern rect_t tileRects[];
extern uint16_t frameBuffer[];

const uint16_t HALF_FULLSCREEN_RES_X = FULLSCREEN_RES_X / 2;
const uint16_t HALF_FULLSCREEN_RES_Y = FULLSCREEN_RES_Y / 2;

__inline void rescale_attributes(vertex_attr_t *rescaled_va, const vertex_attr_t *va);
__inline void cleanUp(vertex_attr_t *v1, vertex_attr_t *v2, vertex_attr_t *v3, triangle2d_t *triangle);
__inline void prepareTriangleVertices(uint16_t triangleId, vertex_attr_t *v1, vertex_attr_t *v2, vertex_attr_t *v3);

void initMeshRenderer(void) {
	initTileSystem();
}

__inline void rescale_attributes(vertex_attr_t *rescaled_va, const vertex_attr_t *va) {	
	rescaled_va->pos.x = (va->pos.x >> 7) + HALF_FULLSCREEN_RES_X;
	rescaled_va->pos.y = va->pos.y >> 7;
	rescaled_va->pos.z = (va->pos.z >> 7) + HALF_FULLSCREEN_RES_Y;
	
	rescaled_va->normal.x = va->normal.x;
	rescaled_va->normal.y = va->normal.y;
	rescaled_va->normal.z = va->normal.z;
}

__inline void cleanUp(vertex_attr_t *v1, vertex_attr_t *v2, vertex_attr_t *v3, triangle2d_t *triangle) {
	free(v1);
	free(v2);
	free(v3);
	free(triangle);
}

__inline void prepareTriangleVertices(uint16_t triangleId, vertex_attr_t *v1, vertex_attr_t *v2, vertex_attr_t *v3) {
	rescale_attributes(v1, &vertices[indices[triangleId].a]);
	rescale_attributes(v2, &vertices[indices[triangleId].b]);
	rescale_attributes(v3, &vertices[indices[triangleId].c]);
}

__inline void prepareTriangle(vertex_attr_t *v1, vertex_attr_t *v2, vertex_attr_t *v3, triangle2d_t *triangle) {
	triangle->a[0].x = v1->pos.x;
	triangle->a[0].y = v1->pos.z;
	triangle->a[1].x = v2->pos.x;
	triangle->a[1].y = v2->pos.z;
	triangle->a[2].x = v3->pos.x;
	triangle->a[2].y = v3->pos.z;
}

void renderMesh(void)
{
	uint16_t tileId, triangleId;
	rect_t *currentRect;
	
	triangle2d_t *triangle;
	vertex_attr_t *v1, *v2, *v3;
	
	triangle = (triangle2d_t *)malloc(sizeof(triangle2d_t));
	v1 = (vertex_attr_t *)malloc(sizeof(vertex_attr_t));
	v2 = (vertex_attr_t *)malloc(sizeof(vertex_attr_t));
	v3 = (vertex_attr_t *)malloc(sizeof(vertex_attr_t));
	
	for(tileId = 0; tileId < TILES_CNT; tileId++) {
		currentRect = &tileRects[tileId];
		
		clearFrameBuffer();
		
		for(triangleId = 0; triangleId < num_indices; triangleId++) {
			prepareTriangleVertices(triangleId, v1, v2, v3);
			prepareTriangle(v1, v2, v3, triangle);
			renderTriangle(frameBuffer, triangle, currentRect);
		}
		
		displayFrameBuffer(currentRect);
	}
	
	cleanUp(v1, v2, v3, triangle);
}
