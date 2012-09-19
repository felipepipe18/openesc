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

#ifndef RCPWM_H
#define RCPWM_H

#include "stm32f10x_tim.h"

typedef struct rcpwm
{
  uint16_t longestPulseTime;	// Corresponds to 100% speed demand
  uint16_t shortestPulseTime;	// Corresponds to 0% speed demand

  uint16_t demandQ15;			// This is the Q15 (S16) speed demand
} rcpwm;

extern struct rcpwm rcPwm;

void initRcPwm(void);
uint16_t getRisingEdgeTime(void);
uint16_t getFallingEdgeTime(void);

#endif
