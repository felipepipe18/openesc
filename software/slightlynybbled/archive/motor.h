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

/* Standard or provided libs */
#include "stm32f10x_adc.h"
#include "misc.h"
#include <stdbool.h>

/* User-generated libs */
#include "motPwm.h"
#include "milliSecTimer.h"

#define DEFAULT_PWM_FREQ		16000
#define MIN_DUTY_CYCLE			10000

// Use these to keep track of the
//	current state of the motor
//	(this is a state machine)
#define MOTOR_LOCKED	0
#define MOTOR_STOPPED	1
#define MOTOR_STARTING	2
#define MOTOR_RUNNING	3

#define BLDC_NEG	0
#define BLDC_POS	1

typedef struct{
	uint8_t state;
	uint8_t sector;
	uint16_t dutyCycle;
	bool direction;
} _motor;

extern _motor BLDC_motor;

// These are the motor interface functions,
//	or the "public" functions
void BLDC_initMotor(void);
void BLDC_startMotor(void);
void BLDC_stopMotor(void);
void BLDC_commandDutyCycle(uint16_t dutyCycle);
void BLDC_commandDirection(bool direction);

uint8_t BLDC_getMotorState(void);

// Used internally to motor.c, "private"
void BLDC_commutate(void);
void BLDC_initAdc(void);

#endif
