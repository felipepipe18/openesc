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
#ifndef MOTPWM_H
#define MOTPWM_H

/* Standard or provided libs */
#include "stm32f10x_tim.h"

/* User-generated libs */
#include "openesc_v01.h"

#define MPWM_PH_A	0
#define MPWM_PH_B	1
#define MPWM_PH_C	2

#define MPWM_DORMANT	0
#define MPWM_HI_STATE	1
#define MPWM_LO_STATE	2

typedef struct{
	uint8_t stateA, stateB, stateC;
} _phase;

_phase MPWM_motorPhase;

void MPWM_initMotorPwm(void);
void MPWM_setMotorPwmFreq(uint16_t pwmFrequency);
void MPWM_setPhaseDutyCycle(uint8_t phase, uint8_t state, uint16_t dutyCycle);

#endif
