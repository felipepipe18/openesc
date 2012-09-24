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
 * Purpose: To run the motor and to provide a motor
 * 	interface to higher-level code.  ADC interrupt code
 * 	that reads the phases should be located here as
 *  well as higher-level motor-control pwm (mcpwm)
 *  controlling code.
*************************************************/

#include "motor.h"
#include "milliSecTimer.h"

_motor motor;

void
initMotor(void){
	initMotorPwm();
	setMotorPwmFreq(16000);

	initMilliSecTimer();

	stopMotor();
}

void
startMotor(void){
	motor.sector = 0;
	motor.state = MOTOR_RUNNING;
}

void
stopMotor(void){
	// Place each phase in the DORMANT state
	setPhaseDutyCycle(PH_A, DORMANT, 0);
	setPhaseDutyCycle(PH_B, DORMANT, 0);
	setPhaseDutyCycle(PH_C, DORMANT, 0);

	// Place the motor in the STOPPED state
	motor.state = MOTOR_STOPPED;
	motor.sector = 0;
}

uint8_t
getMotorState(void){
	return motor.state;
}
