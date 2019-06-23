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

#include "tileSystem.h"
#include "triangleRenderer.h"
#include "mesh.h"

uint16_t frameBuffer[TILE_RES_X * TILE_RES_Y];

extern const uint16_t TILES_CNT;

extern rect_t tileRects[];

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

const uint16_t HALF_FULLSCREEN_RES_X = FULLSCREEN_RES_X / 2;
const uint16_t HALF_FULLSCREEN_RES_Y = FULLSCREEN_RES_Y / 2;

vertex_attr_t *rescale_attributes(const vertex_attr_t *va) {
	vertex_attr_t *_va = (vertex_attr_t *)malloc(sizeof(vertex_attr_t));
	
	_va->pos.x = (va->pos.x >> 7) + HALF_FULLSCREEN_RES_X;
	_va->pos.y = va->pos.y >> 7;
	_va->pos.z = (va->pos.z >> 7) + HALF_FULLSCREEN_RES_Y;
	
	_va->normal.x = va->normal.x;
	_va->normal.y = va->normal.y;
	_va->normal.z = va->normal.z;
	
	return _va;
}

int main(void)
{
	uint16_t tile_id, triangle_id;
	triangle2d_t *triangle;
	rect_t *currentRect;
	vertex_attr_t *v1, *v2, *v3;
	
  delay_init();
  LCD_Initializtion();
  LCD_Clear(Blue);
	
	initTileSystem();
	
	triangle = (triangle2d_t *)malloc(sizeof(triangle2d_t));
	
  while (1)
  {
		for(tile_id = 0; tile_id < TILES_CNT; tile_id++) {
			
			currentRect = &tileRects[tile_id];
			
			clearFrameBuffer();
			
			for(triangle_id = 0; triangle_id < num_indices; triangle_id++) {
				v1 = rescale_attributes(&vertices[indices[triangle_id].a]);
				v2 = rescale_attributes(&vertices[indices[triangle_id].b]);
				v3 = rescale_attributes(&vertices[indices[triangle_id].c]);
				
				triangle->a[0].x = v1->pos.x;
				triangle->a[0].y = v1->pos.z;
				triangle->a[1].x = v2->pos.x;
				triangle->a[1].y = v2->pos.z;
				triangle->a[2].x = v3->pos.x;
				triangle->a[2].y = v3->pos.z;
				
				renderTriangle(frameBuffer, triangle, currentRect);
				
				free(v1);
				free(v2);
				free(v3);
			}
			
			
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
