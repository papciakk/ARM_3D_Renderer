#include "lighting.h"
#include <stdio.h>
#include <math.h>

point3d_t lightDir;
int16_t ambientDiffuse = 10;

__inline void calcLightingForVertex(vertex_attr_32_t *v, color_t *color);

void resetLightPosition(void) {
	lightDir.x = 0;
	lightDir.y = 0;
	lightDir.z = -512;
}

void calcLightingForTriangle(
	vertex_attr_32_t *v1, vertex_attr_32_t *v2, vertex_attr_32_t*v3, 
	color_t *color1, color_t *color2, color_t *color3) {
	
	calcLightingForVertex(v1, color1);
	calcLightingForVertex(v2, color2);
	calcLightingForVertex(v3, color3);
}
	
__inline void calcLightingForVertex(vertex_attr_32_t *v, color_t *color) {
	uint8_t diffuse;
	int32_t diffuse_raw;
	
	diffuse_raw = (
		v->normal.x * lightDir.x +
		v->normal.y * lightDir.y +
		v->normal.z * lightDir.z
	) >> 16;
	
	if(diffuse_raw < 0) diffuse = ambientDiffuse;
	else if(diffuse_raw + ambientDiffuse > 255) diffuse = 255;
	else diffuse = diffuse_raw + ambientDiffuse;
	
	
	color->r = diffuse;
	color->g = diffuse;
	color->b = diffuse;
}
