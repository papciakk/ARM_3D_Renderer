#include "sinCos.h"
#include "math.h"

static uint16_t sinLUT[90];

void initSinCos(void) {
	uint8_t i;
	for(i = 0; i < 90; i++) {
		sinLUT[i] = (int)(8192.0 * sin((double)i * 0.0174533));
	}
}

void getSinCos(int16_t angle, int16_t *sin, int16_t *cos) {
	if(angle >= 270) {
		*sin = -sinLUT[360 - angle];
		*cos =  sinLUT[angle - 270];
	} else if(angle >= 180) {
		*sin = -sinLUT[angle - 180];
		*cos = -sinLUT[270 - angle];
	} else if(angle >= 90) {
		*sin =  sinLUT[180 - angle];
		*cos = -sinLUT[angle - 90];
	} else {
		*sin =  sinLUT[angle];
		*cos =  sinLUT[90 - angle];
	}
}
