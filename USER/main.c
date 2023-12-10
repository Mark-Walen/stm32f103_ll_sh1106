/**
 ******************************************************************************
 * @file    Project/STM32F10x_StdPeriph_Template/main.c
 * @author  MCD Application Team
 * @version V3.6.0
 * @date    20-September-2021
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2011 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "spi.h"
#include "oled_sh1106.h"

#ifdef DMA_ENABLE
#include "dma.h"
#endif

/** @addtogroup STM32F10x_StdPeriph_Template
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
	/* Add your application code here */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	uart_init(115200);
	
	GPIO_Configuration();
	OLED_Init();

	/* Infinite loop */
	while (1)
	{
		for (uint16_t i = 0; i < OLED_COLUMN*2; i++) {
		  OLED_NewFrame();
		  OLED_DrawImage((OLED_COLUMN - (bilibiliImg.w)) / 2, 0, &bilibiliImg, OLED_COLOR_NORMAL);
		  OLED_PrintString(OLED_COLUMN - i, 64 - 16, "波特律动hello", &font16x16, OLED_COLOR_NORMAL);
		  OLED_ShowFrame();
		  delay_ms(100);
		}
	}
}

/**
 * @}
 */
