#ifndef INPUT_H
#define INPUT_H

#include "definitions.h"

#define RCC_BTN_USER RCC_APB2Periph_GPIOA
#define PIN_BTN_USER GPIO_Pin_8
#define PORT_BTN_USER GPIOA

#define RCC_JOY RCC_APB2Periph_GPIOD
#define PIN_JOY_SEL GPIO_Pin_0
#define PIN_JOY_DOWN GPIO_Pin_1
#define PIN_JOY_LEFT GPIO_Pin_2
#define PIN_JOY_RIGHT GPIO_Pin_3
#define PIN_JOY_UP GPIO_Pin_4
#define PORT_JOY GPIOD

#define IS_BTN_USER_PRESSED() \
	(GPIO_ReadInputData(PORT_BTN_USER) & PIN_BTN_USER)
	
#define IS_JOY_UP() \
	(GPIO_ReadInputData(PORT_JOY) & PIN_JOY_UP)
	
#define IS_JOY_DOWN() \
	(GPIO_ReadInputData(PORT_JOY) & PIN_JOY_DOWN)
	
#define IS_JOY_LEFT() \
	(GPIO_ReadInputData(PORT_JOY) & PIN_JOY_LEFT)
	
#define IS_JOY_RIGHT() \
	(GPIO_ReadInputData(PORT_JOY) & PIN_JOY_RIGHT)

#define IS_JOY_SEL() \
	(GPIO_ReadInputData(PORT_JOY) & PIN_JOY_SEL)
	

void initInputs(void);
void handleInputs(void);

#endif // INPUT_H
