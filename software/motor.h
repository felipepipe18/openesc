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
#ifndef MOTOR_H
#define MOTOR_H

#include "motPwm.h"
#include "milliSecTimer.h"
#include "stm32f10x_adc.h"

#define DEFAULT_PWM_FREQ		16000
#define MIN_DUTY_CYCLE			10000

#define MOTOR_RUNNING	0
#define MOTOR_STOPPED	1
#define MOTOR_LOCKED	2

typedef struct{
	uint8_t state;
	uint8_t sector;
} _motor;

extern _motor motor;

// These are the motor interface functions,
//	or the "public" functions
void initMotor(void);
void startMotor(void);
void stopMotor(void);
uint8_t getMotorState(void);

// Used internally to motor.c, "private"
void initAdc(void);

#endif
