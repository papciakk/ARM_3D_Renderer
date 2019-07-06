#include "transformations.h"

int16_t rotX = 0, rotY = 0, rotZ = 0;
int16_t scale = 1;

__inline point3d_32_t transformScale(point3d_t pIn, int16_t scale);
__inline point3d_t transformRot(point3d_t pIn, int16_t rotX, int16_t rotY, int16_t rotZ);

__inline point3d_32_t transformScale(point3d_t pIn, int16_t scale) {
	point3d_32_t pOut;
	
	pOut.x = pIn.x + ((pIn.x * scale) >> 3);
	pOut.y = pIn.y + ((pIn.y * scale) >> 3);
	pOut.z = pIn.z + ((pIn.z * scale) >> 3);
	
	return pOut;
}

__inline point3d_t transformRot(point3d_t pIn, int16_t rotX, int16_t rotY, int16_t rotZ) {
	
	return pIn;
}

void transform(vertex_attr_t *vaIn, vertex_attr_32_t *vaOut) {
	point3d_t p;
	point3d_32_t p32;
	
	p = transformRot(vaIn->pos, rotX, rotY, rotZ);
	p32 = transformScale(p, scale);
	
	vaOut->pos.x = p32.x;
	vaOut->pos.y = p32.y;
	vaOut->pos.z = p32.z;
	vaOut->normal.x = vaIn->normal.x; 
	vaOut->normal.y = vaIn->normal.y; 
	vaOut->normal.z = vaIn->normal.z;
}
