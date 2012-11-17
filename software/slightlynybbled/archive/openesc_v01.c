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

// Function implementations here
void
initHseClock(void)
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
	RCC->CFGR |= (0b10 << 0);

	// Wait for system clock to complete switch
	while(((RCC->CFGR >> 2) & 0xfffc) != 0b10);

	// APB1 = 36MHz, APB2 = 72MHz
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

	openEsc.clockFreq = 72000000;
}

void
initHsiClock(void)
{
	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();

	/* Enable Prefetch Buffer */
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

	/* Flash 2 wait state */
	FLASH_SetLatency(FLASH_Latency_2);

	// pllOutput = pllInput x 16 = 8MHz/2 x 9 = 64MHz
	RCC->CFGR |= (uint32_t)(0b1111 << 18);

	// PLL ON
	RCC->CR |= (uint32_t)(0b1 << 24);

	// Wait for PLL to lock
	bool pllRdy = false;

	while(pllRdy == false){
		pllRdy = (bool)(0b1 & (RCC->CR >> 25));
	}

	// Set system clock as PLL
	RCC->CFGR |= (uint32_t)(0b10 << 0);

	// Wait for system clock to complete switch
	uint32_t clock = 0;

	while(clock != 0b10){
		clock = (uint32_t)((RCC->CFGR >> 2) & 0x00000003);
	}

	// APB1 = 32MHz, APB2 = 64MHz
	RCC->CFGR |= (uint32_t)(0b100 << 8);

	// ADCPRE = PCLK2/6 = 72MHz/6 = 10.67MHz (14MHz max)
	RCC->CFGR |= (uint32_t)(0b10 << 14);

	// Enable peripheral clocks
	RCC->APB2ENR |= (uint32_t)((1 << 11)		// TIM1
					+ (1 << 10)		// ADC2
					+ (1 << 9)		// ADC1
					+ (1 << 4)		// IO port C
					+ (1 << 3)		// IO port B
					+ (1 << 2));	// IO port A

	RCC->APB1ENR |= (uint32_t)((1 << 17)		// USART2
					+ (1 << 1));	// TIM3

	openEsc.clockFreq = 64000000;
}


