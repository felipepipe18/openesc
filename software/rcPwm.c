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
#include "rcPwm.h"

struct rcpwm rcPwm;

void
initRcPwm(void)
{
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// TODO: write interrupt routine
	// Interrupt on Capture/Compare 4
	TIM3->DIER |= 0x0010;

	// Capture current value of counter
	//	on and set appropriate interrupt
	//	flags on capture (CC3 and 4)
	TIM3->EGR |= 0x0018;

	// CC4 is an input, IC4 is mapped on TI4
	TIM3->CCMR2 |= 0x0100;

	// CC3 is an input, IC3 is mapped on TI4
	TIM3->CCMR2 |= 0x0002;

	// CC3 capture occurs on rising edge, CC3 is enabled
	TIM3->CCER |= 0x0100;

	// CC4 capture occurs on falling edge, CC4 is enabled
	TIM3->CCER |= 0x3000;

	// Enable the counter
	TIM3->CR1 |= 0x0001;

	// TODO: initialize rcPwm.longestPulseTime and rcPwm.shortestPulseTime
	//	to reasonable starting values (maybe 1.25ms and 1.75ms?)
}

void
TIM3_CC_IRQHandler (void)
{
	// Find the current pulse time.
	//	pulseWidth = risingEdgeTime - fallingEdgeTime
	uint16_t pulseWidth = TIM3->CCR4 - TIM3->CCR3;

	// Determine if the current pulse is the longest or the shortest
	//	measured thus far (for calibration purposes)
	if(pulseWidth > rcPwm.longestPulseTime)
		rcPwm.longestPulseTime = pulseWidth;
	else if(pulseWidth < rcPwm.shortestPulseTime)
		rcPwm.shortestPulseTime = pulseWidth;

	// Calculate the pulse range and the pulse width
	uint16_t range = rcPwm.longestPulseTime - rcPwm.shortestPulseTime;
	uint16_t pulse = pulseWidth - rcPwm.shortestPulseTime;

	// Determine the speed demand as a percentage of the range
	//	TODO: Verify this works as intended.  ARM Cortex-M3 has
	//	a 32bit unsigned divide instruction with a 32-bit result
	rcPwm.demandQ15 = (uint32_t)(pulse << 16)/(uint32_t)range;

	// Reset the flag
	TIM3->SR = 0;
}
