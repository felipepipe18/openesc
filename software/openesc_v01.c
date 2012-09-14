/**************************************************
 * Copyright 2012 OpenESC
 *
 * This file is part of OpenESC
 *
 * OpenESC is free software: you can redistribute
 *	it and/or modify it under the terms of the GNU
 *	General Public License as published by the
 *	Free Software Foundation, either version 3 of
 *	the License, or (at your option) any later
 *	version.
 *
 * OpenESC is distributed in the hope that it will
 *	be useful, but WITHOUT ANY WARRANTY; without
 *	even the implied warranty of MERCHANTABILITY
 *	or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 * You should have received a copy of the GNU
 *	General Public License along with OpenESC. If
 *	not, see http://www.gnu.org/licenses/.
*************************************************/

/**************************************************
 * Purpose: To setup all hardware-related peripherals
 * 	so that the driver functions can simply operate on
 * 	the peripheral itself.  This makes the code more
 * 	flexible and transferrable to other devices since
 * 	the number of files that change with hardware are
 * 	limited.
 *
 * Usage: Initialize all hardware-related registers and
 * 	variables.
*************************************************/


#include "stm32f10x.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

#include "openesc_v01.h"

// Declare any global variables here
GPIO_InitTypeDef GPIO_InitStructure;
RCC_ClocksTypeDef RCC_ClockFreq;
ErrorStatus HSEStartUpStatus;

// Function implementations here
void
setupOpenESC(void)
{
	initClock();
	// initDio();
	// initUsart();
	// initRcPwm();
	// initMcPwm();
}

void
initClock(void)
{
	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();

	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);

	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	/* Enable Prefetch Buffer */
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

	/* Flash 2 wait state */
	FLASH_SetLatency(FLASH_Latency_2);

	/* HCLK = SYSCLK */
	RCC_HCLKConfig(RCC_SYSCLK_Div1);

	/* PCLK2 = HCLK */
	RCC_PCLK2Config(RCC_HCLK_Div1);

	/* PCLK1 = HCLK/2 */
	RCC_PCLK1Config(RCC_HCLK_Div2);

	/* PLLCLK = (16MHz/2) * 9 = 72 MHz */
	// For USB to work correctly, PLL output frequency
	//	must be 48MHz or 72MHz according to ref man para 7.2.3
	RCC_PLLConfig(RCC_PLLSource_HSE_Div2, RCC_PLLMul_9);

	/* Enable PLL */
	RCC_PLLCmd(ENABLE);

	/* Wait till PLL is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
	{
	}

	/* Select PLL as system clock source */
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	/* Wait till PLL is used as system clock source */
	while (RCC_GetSYSCLKSource() != 0x08)
	{
	}
}

void
initDio(void)
{
	// Setup STATUS and ERROR LED's
	GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = ERROR_LED_PIN|STATUS_LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Setup analog input pins
    GPIO_InitStructure.GPIO_Pin = ANALOG_PHA_FBK_PIN|ANALOG_PHB_FBK_PIN|ANALOG_PHC_FBK_PIN|ANALOG_BUS_VOLT_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ANALOG_CURR_SENSE_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Setup current fault as a pull-up to eliminate an external resistor
    GPIO_InitStructure.GPIO_Pin = FAULT_INPUT_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Setup RC PWM input pin
    GPIO_InitStructure.GPIO_Pin = RC_PWM_IN_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Setup TIM1 outputs
    GPIO_InitStructure.GPIO_Pin = MCPWM_AH_PIN|MCPWM_BH_PIN|MCPWM_CH_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = MCPWM_AL_PIN|MCPWM_BL_PIN|MCPWM_CL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
