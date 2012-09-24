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
	/* TIM3 clock enable @36MHz */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// Interrupt enable on Capture/Compare 4
	TIM3->DIER |= (uint16_t)(0b1 << 4);

	// Capture current value of counter
	//	on and set appropriate interrupt
	//	flags on capture (CC3 and 4)
	TIM3->EGR |= (uint16_t)((0b1 << 4)	// chan 4
						+ (0b1 << 3));	// chan 3

	// CC4 is an input, IC4 is mapped on TI4
	// CC3 is an input, IC3 is mapped on TI4
	TIM3->CCMR2 |= (uint16_t)((0b01 << 8)	// chan 4
						+ (0b10 << 0));		// chan 3

	// CC3 capture occurs on rising edge, CC3 is enabled
	// CC4 capture occurs on falling edge, CC4 is enabled
	TIM3->CCER |= (uint16_t)((0b01 << 12)	// chan 4
						+ (0b11 << 8));		// chan 3

	// Reset the flag
	TIM3->SR = 0;

	// Prescaler loaded so that input clock is
	//	divided by two, thus, the clock is at
	//	18MHz, meaning that any pulse can be
	//	measured up to a maximum pulse width
	//	of 3.64ms with a resolution of +/-27ns
	TIM3->PSC = 1;

	// Enable the counter
	TIM3->CR1 |= 0x0001;

	// Initialize rcPwm.longestPulseTime and rcPwm.shortestPulseTime
	//	to reasonable starting values (maybe 1.25ms and 1.75ms?)
	rcPwm.longestPulseTime = 31500;
	rcPwm.shortestPulseTime = 22500;
}

void
TIM3_IRQHandler(void)
{
	// Find the current pulse time.
	//	pulseWidth = risingEdgeTime - fallingEdgeTime
	uint16_t pulseWidth = TIM3->CCR4 - TIM3->CCR3;

	// Verify that the pulse is long enough that it isn't
	//	a glitch.  This isn't bulletproof, but it should
	//	help when connecting and disconnecting equipment
	if(pulseWidth > MIN_RC_PULSE_WIDTH){
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
	}

	// Reset the flag
	TIM3->SR = 0;
}
