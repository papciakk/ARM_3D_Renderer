#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdlib.h>
#include <stdint.h>
#include "cfg.h"

// TYPEDEFS

typedef struct {
	uint8_t r, g, b;
} color_t;

typedef struct {
	uint16_t x0, x1, y0, y1;
} rect_t;

typedef struct {
	int16_t x0, x1, y0, y1;
} srect_t;

typedef struct {
	int16_t x, y;
} point2d_t;

typedef struct {
	int16_t x, y, z;
} point3d_t;

typedef struct {
	int32_t x, y, z;
} point3d_32_t;

typedef struct {
	point2d_t a[3];
} triangle2d_t;

typedef struct {
	point3d_t a[3];
} triangle3d_t;

typedef struct {
	color_t a[3];
} triangle_colors_t;

typedef struct {
	point3d_t pos;
	point3d_t normal;
} vertex_attr_t;

typedef struct {
	uint16_t a, b, c;
} triangle_index_t;

typedef struct {
	vertex_attr_t a[3];
} triangle_t;

#define VA(px,py,pz,nx,ny,nz) {{(px), (py), (pz)}, {(nx), (ny), (nz)}}
#define IDX(a,b,c) {(a), (b), (c)}

#define FULLSCREEN_RECT { \
	.x0 = 0,  \
	.x1 = FULLSCREEN_RES_X - 1, \
	.y0 = 0, \
	.y1 = FULLSCREEN_RES_Y - 1 \
}

#define COLOR_BLACK {0}
#define COLOR_WHITE {255}

#endif // DEFINITIONS_H
