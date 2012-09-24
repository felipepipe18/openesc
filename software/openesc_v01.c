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
	// initMotor();
	// initUsart();
	// initUsb();
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
}

void
initDio(void)
{
	// Setup LED pins
	// LED pins are not remapped
	GPIOB->CRL += (uint32_t)((PORT_CNF_OUTPUT_PP + PORT_MODE_OUTPUT) << (4 * 4));	// Error LED
	GPIOB->CRL += (uint32_t)((PORT_CNF_OUTPUT_PP + PORT_MODE_OUTPUT) << (5 * 4));	// Status LED

	// Setup analog input pins
	// Analog input pins are not remapped
	GPIOA->CRL += (uint32_t)((PORT_CNF_INPUT_ANALOG + PORT_MODE_INPUT) << (0 * 4));	// PA0 - PHA FBK
	GPIOA->CRL += (uint32_t)((PORT_CNF_INPUT_ANALOG + PORT_MODE_INPUT) << (1 * 4));	// PA1 - PHB FBK
	GPIOA->CRL += (uint32_t)((PORT_CNF_INPUT_ANALOG + PORT_MODE_INPUT) << (2 * 4));	// PA2 - PHC FBK
	GPIOA->CRL += (uint32_t)((PORT_CNF_INPUT_ANALOG + PORT_MODE_INPUT) << (3 * 4));	// PA3 - Bus Voltage
	GPIOB->CRL += (uint32_t)((PORT_CNF_INPUT_ANALOG + PORT_MODE_INPUT) << (0 * 4));

	// Setup current fault as a pull-up to eliminate external pull-ups
	// Overcurrent sensing pin is not remapped
	GPIOA->CRL += (uint32_t)((PORT_CNF_INPUT_PU_OR_PD + PORT_MODE_INPUT) << (7 * 4));	// PA7 - Overcurrent

	// Setup RC PWM input pin
	// RC PWM input pin is not remapped
	GPIOB->CRL += (uint32_t)((PORT_CNF_FLOATING_INPUT + PORT_MODE_INPUT) << (1 * 4));	// PB1 - RC PWM Input

    // Setup TIM1 outputs
	// TIM1 pins are not remapped
	GPIOB->CRL += (uint32_t)((PORT_CNF_OUTPUT_ALT_PP + PORT_MODE_OUTPUT) << ((13 - 8) * 4));	// PB13 - TIM1_CH1N
	GPIOB->CRL += (uint32_t)((PORT_CNF_OUTPUT_ALT_PP + PORT_MODE_OUTPUT) << ((14 - 8) * 4));	// PB14 - TIM1_CH2N
	GPIOB->CRL += (uint32_t)((PORT_CNF_OUTPUT_ALT_PP + PORT_MODE_OUTPUT) << ((15 - 8) * 4));	// PB15 - TIM1_CH3N
	GPIOA->CRL += (uint32_t)((PORT_CNF_OUTPUT_ALT_PP + PORT_MODE_OUTPUT) << ((8 - 8) * 4));		// PA8 - TIM1_CH1
	GPIOA->CRL += (uint32_t)((PORT_CNF_OUTPUT_ALT_PP + PORT_MODE_OUTPUT) << ((9 - 8) * 4));		// PA9 - TIM1_CH2
	GPIOA->CRL += (uint32_t)((PORT_CNF_OUTPUT_ALT_PP + PORT_MODE_OUTPUT) << ((10 - 8) * 4));	// PA10 - TIM1_CH3
}
