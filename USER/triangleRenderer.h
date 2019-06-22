#ifndef TRIANGLE_RENDERER_H
#define TRIANGLE_RENDERER_H

#include "definitions.h"
#include "common.h"
#include "GLCD.h"

void renderTriangle(uint16_t *frameBuffer, triangle2d_t *triangle, rect_t *tileRect);

#endif // TRIANGLE_RENDERER_H
