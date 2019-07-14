#include "display.h"
#include <limits.h>

uint16_t frameBuffer[TILE_RES_X * TILE_RES_Y];
int16_t depthBuffer[TILE_RES_X * TILE_RES_Y];

void initDisplay(void) {
	delay_init();
  LCD_Initializtion();
  LCD_Clear(Black);
}

void clearFrameBuffer(void) {
	uint32_t i;
	for(i = 0; i < TILE_RES_X * TILE_RES_Y; i++) {
		frameBuffer[i] = 0;
	}
}

void clearDepthBuffer(void) {
	uint32_t i;
	for(i = 0; i < TILE_RES_X * TILE_RES_Y; i++) {
		depthBuffer[i] = SHRT_MAX;
	}
}

void displayFrameBuffer(rect_t *tileRect) {
	LCD_FillImage(tileRect->x0, tileRect->y0, tileRect->x1 - tileRect->x0, tileRect->y1 - tileRect->y0, frameBuffer);
}
