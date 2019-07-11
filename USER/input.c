#include "input.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

extern int16_t rotX, rotY, rotZ;
extern int16_t scale;

void initInputs(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_BTN_USER, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_JOY, ENABLE);
 
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_InitStruct.GPIO_Pin = PIN_BTN_USER;
	GPIO_Init(PORT_BTN_USER, &GPIO_InitStruct);
		
	GPIO_InitStruct.GPIO_Pin = 
		PIN_JOY_UP | PIN_JOY_DOWN | 
		PIN_JOY_LEFT | PIN_JOY_RIGHT | 
		PIN_JOY_SEL;
	GPIO_Init(PORT_JOY, &GPIO_InitStruct);
}

void handleInputs(void) {
	if(IS_BTN_USER_PRESSED()) {
		scale--;
	} else if(IS_JOY_SEL()) {
		scale++;
	} else if(IS_JOY_LEFT()) {
		rotZ += 10;
	} else if(IS_JOY_RIGHT()) {
		rotZ -= 10;
	} else if(IS_JOY_UP()) {
		rotY += 10;
	} else if(IS_JOY_DOWN()) {
		rotY -= 10;
	} 
	
	if(rotX < 0) {
		rotX = 359;
	} else if(rotX > 360) {
		rotX = 1;
	}
	
	if(rotY < 0) {
		rotY = 359;
	} else if(rotY > 360) {
		rotY = 1;
	}
	
	if(rotZ == 0) {
		rotZ = 359;
	} else if(rotZ > 360) {
		rotZ = 1;
	}
}
