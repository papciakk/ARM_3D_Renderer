#ifndef DISPLAY_H
#define DISPLAY_H

#include "definitions.h"
#include "GLCD.h"
#include "systick.h"

void initDisplay(void);
void clearFrameBuffer(void);
void clearDepthBuffer(void);
void displayFrameBuffer(rect_t *tileRect);

#endif // DISPLAY_H
