#include "input.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <string.h>
#include "display.h"

extern int16_t rotX, rotY, rotZ;
extern int16_t lightRotX, lightRotY, lightRotZ;
extern int16_t scale;

uint8_t keyboard[16];

void applyConstraints(void);

void initInputs(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_KBD, ENABLE);
	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = PIN_KBD_H0 | PIN_KBD_H1 | PIN_KBD_H2 | PIN_KBD_H3;
	GPIO_Init(PORT_KBD, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = PIN_KBD_V0 | PIN_KBD_V1 | PIN_KBD_V2 | PIN_KBD_V3;
	GPIO_Init(PORT_KBD, &GPIO_InitStruct);
}

void updateInputs(void) {
	memset(keyboard, 0, sizeof(uint8_t)*16);
	
	SET_KBD_V_BITS();
	RESET_KBD_V1();
	if(IS_KBD_H0_ACTIVE()) keyboard[KBD_ROT_Z_MINUS] = 1;
	if(IS_KBD_H1_ACTIVE()) keyboard[KBD_ROT_Y_MINUS] = 1;
	if(IS_KBD_H2_ACTIVE()) keyboard[KBD_LIGHT_ROT_Z_MINUS] = 1;
	if(IS_KBD_H3_ACTIVE()) keyboard[KBD_LIGHT_ROT_Y_MINUS] = 1;
	
	delay_ms(1);
	
	SET_KBD_V_BITS();
	RESET_KBD_V2();
	if(IS_KBD_H0_ACTIVE()) keyboard[KBD_ROT_X_PLUS] = 1;
	if(IS_KBD_H1_ACTIVE()) keyboard[KBD_ROT_X_MINUS] = 1;
	if(IS_KBD_H2_ACTIVE()) keyboard[KBD_LIGHT_ROT_X_PLUS] = 1;
	if(IS_KBD_H3_ACTIVE()) keyboard[KBD_LIGHT_ROT_X_MINUS] = 1;
	
	delay_ms(1);
	
	SET_KBD_V_BITS();
	RESET_KBD_V3();
	if(IS_KBD_H0_ACTIVE()) keyboard[KBD_ROT_Z_PLUS] = 1;
	if(IS_KBD_H1_ACTIVE()) keyboard[KBD_ROT_Y_PLUS] = 1;
	if(IS_KBD_H2_ACTIVE()) keyboard[KBD_LIGHT_ROT_Z_PLUS] = 1;
	if(IS_KBD_H3_ACTIVE()) keyboard[KBD_LIGHT_ROT_Y_PLUS] = 1;
	
	delay_ms(1);
	
	SET_KBD_V_BITS();
	RESET_KBD_V0();
	if(IS_KBD_H0_ACTIVE()) keyboard[KBD_SCALE_UP] = 1;
	if(IS_KBD_H1_ACTIVE()) keyboard[KBD_SCALE_DOWN] = 1;
	if(IS_KBD_H2_ACTIVE()) keyboard[11] = 1;
	if(IS_KBD_H3_ACTIVE()) keyboard[15] = 1;
	
	delay_ms(1);
}

void handleInputs(void) {
	if(keyboard[KBD_SCALE_DOWN]) {
		scale--;
	} else if(keyboard[KBD_SCALE_UP]) {
		scale++;
	} else if(keyboard[KBD_ROT_X_MINUS]) {
		rotX -= ROT_STEP;
	} else if(keyboard[KBD_ROT_X_PLUS]) {
		rotX += ROT_STEP;
	} else if(keyboard[KBD_ROT_Y_MINUS]) {
		rotY -= ROT_STEP;
	} else if(keyboard[KBD_ROT_Y_PLUS]) {
		rotY += ROT_STEP;
	} else if(keyboard[KBD_ROT_Z_MINUS]) {
		rotZ -= ROT_STEP;
	} else if(keyboard[KBD_ROT_Z_PLUS]) {
		rotZ += ROT_STEP;
	} else if(keyboard[KBD_LIGHT_ROT_X_MINUS]) {
		lightRotX -= ROT_STEP;
	} else if(keyboard[KBD_LIGHT_ROT_X_PLUS]) {
		lightRotX += ROT_STEP;
	} else if(keyboard[KBD_LIGHT_ROT_Y_MINUS]) {
		lightRotY -= ROT_STEP;
	} else if(keyboard[KBD_LIGHT_ROT_Y_PLUS]) {
		lightRotY += ROT_STEP;
	} else if(keyboard[KBD_LIGHT_ROT_Z_MINUS]) {
		lightRotZ -= ROT_STEP;
	} else if(keyboard[KBD_LIGHT_ROT_Z_PLUS]) {
		lightRotZ += ROT_STEP;
	}

	lightRotY += ROT_STEP;
	//delay_ms(500);
	
	applyConstraints();
}

void applyConstraints(void) {
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
	
	if(rotZ < 0) {
		rotZ = 359;
	} else if(rotZ > 360) {
		rotZ = 1;
	}
	
	if(lightRotX < 0) {
		lightRotX = 359;
	} else if(lightRotX > 360) {
		lightRotX = 1;
	}
	
	if(lightRotY < 0) {
		lightRotY = 359;
	} else if(lightRotY > 360) {
		lightRotY = 1;
	}
	
	if(lightRotZ < 0) {
		lightRotZ = 359;
	} else if(lightRotZ > 360) {
		lightRotZ = 1;
	}
}
