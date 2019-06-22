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
#include <string.h>
#include "stm32f10x.h"
#include "systick.h"
#include "GLCD.h"
#include "triangleRenderer.h"

const uint16_t TILES_X_CNT = FULLSCREEN_RES_X / TILE_RES_X;
const uint16_t TILES_Y_CNT = FULLSCREEN_RES_Y / TILE_RES_Y;
const uint16_t TILES_CNT = TILES_X_CNT * TILES_Y_CNT;

uint16_t frameBuffer[TILE_RES_X * TILE_RES_Y];

rect_t tileRects[TILES_CNT];


void clearFrameBuffer() {
	memset(frameBuffer, 0, sizeof(uint16_t) * TILE_RES_X * TILE_RES_Y);
}

void displayFrameBuffer(rect_t *tileRect) {
	uint16_t x, y;
	for(y = 0; y < TILE_RES_Y; y++) {
		for(x = 0; x < TILE_RES_X; x++) {
			LCD_SetPoint(tileRect->x0 + x, tileRect->y0 + y, frameBuffer[TILE_RES_X * y + x]);
		}
	}
}

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

int main(void)
{
	int i;
	triangle2d_t *triangle;
	rect_t *currentRect;
	
  delay_init();
  LCD_Initializtion();
  LCD_Clear(Blue);
	
	prepareTileRects();
	
	triangle = (triangle2d_t *)malloc(sizeof(triangle2d_t));
	triangle->a[0].x = 26;
	triangle->a[0].y = 19;
	triangle->a[1].x = 114;
	triangle->a[1].y = 214;
	triangle->a[2].x = 294;
	triangle->a[2].y = 129;
	
  while (1)
  {
		for(i = 0; i < TILES_CNT; i++) {
			
			currentRect = &tileRects[i];
			
			clearFrameBuffer();
			renderTriangle(frameBuffer, triangle, currentRect);
			displayFrameBuffer(currentRect);
		}
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
