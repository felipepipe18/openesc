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

#include "milliSecTimer.h"

_timer MSTMR_timer;

void
MSTMR_initMilliSecTimer(void)
{
	uint32_t timerTwoFreq;
	uint16_t arrValue;

	/* TIM3 clock enable @36MHz */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// Interrupt enable on Capture/Compare 4
	TIM2->DIER |= (uint16_t)(0b1 << 4);

	// Reset the flag
	TIM2->SR = 0;

	// Prescaler loaded so that input clock is divided by two.
	TIM2->PSC = 1;

	// Calculate the timer 2 input clock frequency based on the prescalers
	timerTwoFreq = openEsc.clockFreq >> 2;

	// Calculate the ARR value for timer 2 in order to create an overflow at 1ms
	arrValue = (uint16_t)(timerTwoFreq/1000);
	TIM2->ARR = arrValue;

	// Enable the counter
	TIM2->CR1 |= 0x0001;

	// Reset the milliSeconds timer
	MSTMR_timer.milliSeconds = 0;
}

void
TIM2_IRQHandler (void)
{
	MSTMR_timer.milliSeconds++;
	TIM2->SR = 0;
}

uint32_t
MSTMR_getMilliSeconds(void)
{
	return MSTMR_timer.milliSeconds;
}
