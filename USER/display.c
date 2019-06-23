#include "display.h"

uint16_t frameBuffer[TILE_RES_X * TILE_RES_Y];

void initDisplay(void) {
	delay_init();
  LCD_Initializtion();
  LCD_Clear(Blue);
}

void clearFrameBuffer(void) {
	memset(frameBuffer, 0, sizeof(uint16_t) * TILE_RES_X * TILE_RES_Y);
}

void displayFrameBuffer(rect_t *tileRect) {
	uint16_t x, y;
	for(y = 0; y < TILE_RES_Y; y++) {
		for(x = 0; x < TILE_RES_X; x++) {
			LCD_SetPoint(tileRect->x0 + x, tileRect->y0 + y, frameBuffer[TILE_RES_X * y + x]);
		}
	}
}
