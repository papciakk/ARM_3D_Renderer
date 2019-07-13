#ifndef INPUT_H
#define INPUT_H

#include "definitions.h"

#define RCC_KBD RCC_APB2Periph_GPIOD
#define PORT_KBD GPIOD

#define PIN_KBD_H0 GPIO_Pin_3
#define PIN_KBD_H1 GPIO_Pin_2
#define PIN_KBD_H2 GPIO_Pin_1
#define PIN_KBD_H3 GPIO_Pin_0

#define PIN_KBD_V0 GPIO_Pin_4
#define PIN_KBD_V1 GPIO_Pin_8
#define PIN_KBD_V2 GPIO_Pin_9
#define PIN_KBD_V3 GPIO_Pin_10

#define IS_KBD_H0_ACTIVE() \
	!(GPIO_ReadInputData(PORT_KBD) & PIN_KBD_H0)
	
#define IS_KBD_H1_ACTIVE() \
	!(GPIO_ReadInputData(PORT_KBD) & PIN_KBD_H1)
	
#define IS_KBD_H2_ACTIVE() \
	!(GPIO_ReadInputData(PORT_KBD) & PIN_KBD_H2)
	
#define IS_KBD_H3_ACTIVE() \
	!(GPIO_ReadInputData(PORT_KBD) & PIN_KBD_H3)
	
	
#define SET_KBD_V_BITS() \
	GPIO_SetBits(PORT_KBD, PIN_KBD_V0 | PIN_KBD_V1 | PIN_KBD_V2 | PIN_KBD_V3)
	
#define RESET_KBD_V0() \
	GPIO_ResetBits(PORT_KBD, PIN_KBD_V0)
	
#define RESET_KBD_V1() \
	GPIO_ResetBits(PORT_KBD, PIN_KBD_V1)
	
#define RESET_KBD_V2() \
	GPIO_ResetBits(PORT_KBD, PIN_KBD_V2)
	
#define RESET_KBD_V3() \
	GPIO_ResetBits(PORT_KBD, PIN_KBD_V3)

#define KBD_SCALE_UP 3
#define KBD_SCALE_DOWN 7
#define KBD_ROT_X_PLUS 1
#define KBD_ROT_X_MINUS 5
#define KBD_ROT_Y_PLUS 6
#define KBD_ROT_Y_MINUS 4
#define KBD_ROT_Z_PLUS 2
#define KBD_ROT_Z_MINUS 0

#define ROT_STEP 10

void initInputs(void);
void updateInputs(void);
void handleInputs(void);

#endif // INPUT_H
