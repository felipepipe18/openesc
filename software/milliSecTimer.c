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

_timer timer;

void
initMilliSecTimer(void)
{
	/* TIM3 clock enable @36MHz */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// Interrupt enable on Capture/Compare 4
	TIM2->DIER |= (uint16_t)(0b1 << 4);

	// Reset the flag
	TIM2->SR = 0;

	// Prescaler loaded so that input clock is
	//	divided by two, thus, the clock is at
	//	18MHz, meaning that any pulse can be
	//	measured up to a maximum pulse width
	//	of 3.64ms with a resolution of +/-27ns
	TIM2->PSC = 1;

	// Load the ARR register with a value
	//	that gives an overflow at 1ms
	TIM2->ARR = 18000;

	// Enable the counter
	TIM2->CR1 |= 0x0001;

	// Reset the milliSeconds timer
	timer.milliSeconds = 0;
}

void
TIM2_IRQHandler (void)
{
	timer.milliSeconds++;
	TIM2->SR = 0;
}

uint32_t
getMilliSeconds(void)
{
	return timer.milliSeconds;
}
