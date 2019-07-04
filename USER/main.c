/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x.h"
#include "meshRenderer.h"
#include "display.h"
#include "sinCos.h"

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

extern uint16_t rotX, rotY, rotZ;
extern uint16_t scale;

void initButtons(void) {
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

int main(void)
{		
	initButtons();
	initDisplay();
	initSinCos();
	initMeshRenderer();
	
  while (1)
  {
		if(IS_BTN_USER_PRESSED()) {
			scale -= 1;
		}
		
		if(IS_JOY_SEL()) {
			scale += 1;
		}
		
		renderMesh();
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
