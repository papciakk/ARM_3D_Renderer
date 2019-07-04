#include "transformations.h"

uint16_t rotX = 0, rotY = 0, rotZ = 0;
uint16_t scale = 1;

__inline void transformScale(vertex_attr_t *vaIn, vertex_attr_t *vaOut,
	uint16_t scale
);

__inline void transformRot(vertex_attr_t *vaIn, vertex_attr_t *vaOut,
	uint16_t rotX, uint16_t rotY, uint16_t rotZ
);

__inline void transformScale(vertex_attr_t *vaIn, vertex_attr_t *vaOut,
	uint16_t scale
) {
	
	vaOut->pos.x = vaIn->pos.x + ((vaIn->pos.x * scale) >> 4);
	vaOut->pos.y = vaIn->pos.y + ((vaIn->pos.y * scale) >> 4);
	vaOut->pos.z = vaIn->pos.z + ((vaIn->pos.z * scale) >> 4);	
}

__inline void transformRot(vertex_attr_t *vaIn, vertex_attr_t *vaOut,
	uint16_t rotX, uint16_t rotY, uint16_t rotZ
) {
	// TODO
	vaOut->pos.x = vaIn->pos.x; vaOut->pos.y = vaIn->pos.y; vaOut->pos.z = vaIn->pos.z;	
}

void transform(vertex_attr_t *vaIn, vertex_attr_t *vaOut) {
	vaOut->normal.x = vaIn->normal.x; vaOut->normal.y = vaIn->normal.y; vaOut->normal.z = vaIn->normal.z;
	transformRot(vaIn, vaOut, rotX, rotY, rotZ);
	transformScale(vaIn, vaOut, scale);
}
