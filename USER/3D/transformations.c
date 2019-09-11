#include "transformations.h"
#include "sinCos.h"
#include <stdio.h>

int16_t rotX = 0, rotY = 0, rotZ = 180;
int16_t lightRotX = 0, lightRotY = 0;
int16_t scale = 256;

extern point3d_t lightDir;

__inline point3d_32_t transformScale(point3d_32_t pIn, int16_t scale);
__inline point3d_32_t transformRotation(point3d_t pIn, int16_t rotX, int16_t rotY, int16_t rotZ);

__inline point3d_32_t transformScale(point3d_32_t pIn, int16_t scale) {
	point3d_32_t pOut;
	
	pOut.x = pIn.x * scale / 256;
	pOut.y = pIn.y * scale / 256;
	pOut.z = pIn.z;
	
	return pOut;
}

__inline point3d_32_t transformRotation(point3d_t pIn, int16_t rotX, int16_t rotY, int16_t rotZ) {
	point3d_32_t p;
	int32_t tmp;
	
	int16_t sinX, cosX;
	int16_t sinY, cosY;
	int16_t sinZ, cosZ;
	
	p.x = pIn.x; p.y = pIn.y; p.z = pIn.z;
	
	getSinCos(rotX, &sinX, &cosX);
	getSinCos(rotY, &sinY, &cosY);
	getSinCos(rotZ, &sinZ, &cosZ);	
	
	// z rot
	tmp = (int32_t)(p.x * cosZ - p.y * sinZ) >> 13;
	p.y = (int32_t)(p.x * sinZ + p.y * cosZ) >> 13;
	p.x = tmp;
	
	// y rot
	tmp = (int32_t)(p.z * sinY + p.x * cosY)  >> 13;
	p.z = (int32_t)(p.z * cosY - p.x * sinY)  >> 13;
	p.x = tmp;
	
	// x rot
	tmp = (int32_t)(p.y * cosX - p.z * sinX) >> 13;
	p.z = (int32_t)(p.y * sinX + p.z * cosX) >> 13;
	p.y = tmp;
	
	return p;
}

void transform(vertex_attr_t *vaIn, vertex_attr_32_t *vaOut) {
	point3d_32_t p;
	
	p = transformRotation(vaIn->pos, rotX, rotY, rotZ);
	p = transformScale(p, scale);
	
	vaOut->pos.x = p.x;
	vaOut->pos.y = p.y;
	vaOut->pos.z = p.z;
	vaOut->normal.x = vaIn->normal.x; 
	vaOut->normal.y = vaIn->normal.y; 
	vaOut->normal.z = vaIn->normal.z;
}

void transformLight(void) {
	point3d_32_t p = transformRotation(lightDir, lightRotX, lightRotY, 0);
	lightDir.x = p.x; lightDir.y = p.y; lightDir.z = p.z;
	//printf("%i %i %i\n", lightDir.x, lightDir.y, lightDir.z);
}
