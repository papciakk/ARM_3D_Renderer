#include "definitions.h"
#include "common.h"

int16_t minimum3(int16_t x, int16_t y, int16_t z) {
	if (x < y) {
		return (x < z) ? x : z;
	} else {
		return (y < z) ? y : z;
	}
}

int16_t maximum3(int16_t x, int16_t y, int16_t z) {
	if (x > y) {
		return (x > z) ? x : z;
	} else {
		return (y > z) ? y : z;
	}
}


int16_t minimum2(int16_t x, int16_t y) {
	return (x < y) ? x : y;
}

int16_t maximum2(int16_t x, int16_t y) {
	return (x > y) ? x : y;
}
