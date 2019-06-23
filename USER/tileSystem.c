#include "tileSystem.h"

const uint16_t TILES_X_CNT = FULLSCREEN_RES_X / TILE_RES_X;
const uint16_t TILES_Y_CNT = FULLSCREEN_RES_Y / TILE_RES_Y;
const uint16_t TILES_CNT = TILES_X_CNT * TILES_Y_CNT;

rect_t tileRects[TILES_CNT];

rect_t getTileRect(uint16_t x, uint16_t y);
void prepareTileRects(void);

rect_t getTileRect(uint16_t x, uint16_t y) {
	rect_t r;
	r.x0 = x * TILE_RES_X;
	r.x1 = (x + 1) * TILE_RES_X;
	r.y0 = y * TILE_RES_Y;
	r.y1 = (y + 1) * TILE_RES_Y;
	return r;
}

void prepareTileRects(void) {
	uint16_t x, y;
	
	for(y = 0; y < TILES_Y_CNT; y++) {
		for(x = 0; x < TILES_X_CNT; x++) {
			tileRects[TILES_X_CNT * y + x] = getTileRect(x, y);
		}
	}
}

void initTileSystem(void) {
	prepareTileRects();
}
