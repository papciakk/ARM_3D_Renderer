#ifndef MEASURE_TIME_H
#define MEASURE_TIME_H

#include <stdint.h>

#define  ARM_CM_DEMCR      (*(uint32_t *)0xE000EDFC)
#define  ARM_CM_DWT_CTRL   (*(uint32_t *)0xE0001000)
#define  ARM_CM_DWT_CYCCNT (*(uint32_t *)0xE0001004)

#define TRCENA (1 << 24)
#define CYCCNTENA (1 << 0)

void initCycleCounter(void);
uint32_t getCycleCount(void);
void resetCycleCounter(void);

#endif // MEASURE_TIME_H
