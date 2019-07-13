#include "definitions.h"
#include <string.h>
#include "GLCD.h"
#include "systick.h"

void initDisplay(void);
void clearFrameBuffer(void);
void clearDepthBuffer(void);
void displayFrameBuffer(rect_t *tileRect);
