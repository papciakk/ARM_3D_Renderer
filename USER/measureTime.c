#include "measureTime.h"

void initCycleCounter(void) {
		ARM_CM_DEMCR      |= TRCENA;
		ARM_CM_DWT_CYCCNT  = 0;
		ARM_CM_DWT_CTRL   |= CYCCNTENA;
}

uint32_t getCycleCount(void) {
	return ARM_CM_DWT_CYCCNT;
}

void resetCycleCounter(void) {
	ARM_CM_DWT_CYCCNT = 0;
}
