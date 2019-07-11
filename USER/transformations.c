#include "transformations.h"
#include "sinCos.h"

int16_t rotX = 0, rotY = 0, rotZ = 0;
int16_t scale = 1;

__inline point3d_32_t transformScale(point3d_32_t pIn, int16_t scale);
__inline point3d_32_t transformRotation(point3d_t pIn, int16_t rotX, int16_t rotY, int16_t rotZ);

__inline point3d_32_t transformScale(point3d_32_t pIn, int16_t scale) {
	point3d_32_t pOut;
	
	pOut.x = pIn.x + ((pIn.x * scale) >> 3);
	pOut.y = pIn.y + ((pIn.y * scale) >> 3);
	pOut.z = pIn.z + ((pIn.z * scale) >> 3);
	
	return pOut;
}

__inline point3d_32_t transformRotation(point3d_t pIn, int16_t rotX, int16_t rotY, int16_t rotZ) {
	point3d_32_t p;
	
	int16_t sinX, cosX;
	int16_t sinY, cosY;
	int16_t sinZ, cosZ;
	
	p.x = pIn.x; p.y = pIn.y; p.z = pIn.z;
	
	getSinCos(rotX, &sinX, &cosX);
	getSinCos(rotY, &sinY, &cosY);
	getSinCos(rotZ, &sinZ, &cosZ);
	
	// x rot
	p.y = (p.y * cosX - p.z * sinX) >> 13;
	p.z = (p.y * sinX + p.z * cosX) >> 13;
	
	// y rot
	p.x = (p.z * sinY + p.x * cosY) >> 13;
	p.z = (p.z * cosY - p.x * sinY) >> 13;
	
	// z rot
	p.x = (p.x * cosZ - p.y * sinZ) >> 13;
	p.y = (p.x * sinZ + p.y * cosZ) >> 13;
	

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
