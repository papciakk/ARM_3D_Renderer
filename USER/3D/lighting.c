#include "lighting.h"

point3d_32_t lightDir;

__inline void calcLightingForVertex(vertex_attr_t *v, color_t *color);

void initLighting(void) {
	lightDir.x = 180;
	lightDir.y = 0;
	lightDir.z = 180;
}

void calcLightingForTriangle(
	vertex_attr_t *v1, vertex_attr_t *v2, vertex_attr_t *v3, 
	color_t *color1, color_t *color2, color_t *color3) {
	
	calcLightingForVertex(v1, color1);
	calcLightingForVertex(v2, color2);
	calcLightingForVertex(v3, color3);
}
	
__inline void calcLightingForVertex(vertex_attr_t *v, color_t *color) {
	uint8_t diffuse;
	int32_t diffuse_raw = (
		v->normal.x * lightDir.x +
		v->normal.y * lightDir.y +
		v->normal.z * lightDir.z
	) >> 16;
	
	if(diffuse_raw > 0) {
		if(diffuse_raw > 255) {
			diffuse = 255;
		} else {
			diffuse = abs(diffuse_raw);
		}
	} else {
		diffuse = 0;
	}
	
	color->r = diffuse;
	color->g = diffuse;
	color->b = diffuse;
}
