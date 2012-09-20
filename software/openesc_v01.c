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
	initDio();
	initRcPwm();
	// initUsart();
	// initUsb();
	// initMcPwm();
}

void
initClock(void)
{
	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();

	/* Enable Prefetch Buffer */
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

	/* Flash 2 wait state */
	FLASH_SetLatency(FLASH_Latency_2);

	// HSE on
	RCC->CR |= (1 << 16);

	// Wait for HSE to start
	bool hseRdy = 0;

	while(!hseRdy){
		hseRdy = (bool)(0b1 & (RCC->CR  >> 17));
	}

	// pllInput = hseInput/2 = 16MHz/2 = 8MHz
	RCC->CFGR |= (0b1 << 17);

	// pllOutput = pllInput x 9 = 8MHz x 9 = 72MHz
	RCC->CFGR |= (0b0111 << 18);

	// pllSrc = hse
	RCC->CFGR |= (0b1 << 16);

	// PLL ON
	RCC->CFGR |= (0b1 << 24);

	// Wait for PLL to lock
	bool pllRdy = 0;

	while(!pllRdy){
		pllRdy = (bool)(0b1 & (RCC->CR >> 25));
	}

	// Set system clock as PLL
	RCC->CFGR |= (0b10);

	// Wait for system clock to complete switch
	while(((RCC->CFGR >> 2) & 0x11) != 0b10);

	// APB1 = 36MHz
	RCC->CFGR |= (0b100 << 8);

	// ADCPRE = PCLK2/6 = 72MHz/6 = 12MHz (14MHz max)
	RCC->CFGR |= (0b10 << 14);



	// Enable peripheral clocks
	RCC->APB2ENR |= ((1 << 11)		// TIM1
					+ (1 << 10)		// ADC2
					+ (1 << 9)		// ADC1
					+ (1 << 4)		// IO port C
					+ (1 << 3)		// IO port B
					+ (1 << 2));	// IO port A

	RCC->APB1ENR |= ((1 << 23)		// USB
					+ (1 << 17)		// USART2
					+ (1 << 1));	// TIM3
}

void
initDio(void)
{
	// Setup LED pins


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
