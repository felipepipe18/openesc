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
initMotor(void)
{
	initMotorPwm();
	setMotorPwmFreq(16000);

	initAdc();

	stopMotor();
}

void
startMotor(void)
{
	if(getMilliSeconds() > 100){
		motor.sector = 0;
		motor.state = MOTOR_RUNNING;
	}
}

void
stopMotor(void)
{
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

void
ADC1_2_IRQHandler(void)
{

	ADC1->SR &= !((uint32_t)(0b1 << 2));
	ADC2->SR &= !((uint32_t)(0b1 << 2));
}

/************************************************
 * TODO: write interrupt routine
 * TODO: check for proper operation on hardware
 ************************************************/
void
initAdc(void)
{
	// Clear the injected scan interrupt flag
	ADC1->SR &= !((uint32_t)(0b1 << 2));
	ADC2->SR &= !((uint32_t)(0b1 << 2));

	ADC1->CR1 |= (uint32_t)((0b001 << 13)	// discontinuous mode, 2 channels
						+ (0b1 << 12)		// discontinuous mode on injected channels enabled
						+ (0b1 << 8)		// scan mode enabled
						+ (0b1 << 7));		// interrupt at the end of conversion of the last injected channel in the scan sequence

	ADC2->CR1 |= ADC1->CR1;					// ADC2 is identical

	ADC1->CR2 |= (uint32_t)((0b1 << 15)		// enable external trigger for injected channels
						+ (0b001 << 12));	// external trigger: Timer 1 CC4 event

	ADC2->CR2 |= ADC1->CR2;					// ADC2 is identical

	ADC1->SMPR1 &= 0xff000000;				// all samples set to 1.5 adc cycles
	ADC1->SMPR2 &= 0xc0000000;

	ADC2->SMPR1 &= 0xff000000;				// all samples set to 1.5 adc cycles
	ADC2->SMPR2 &= 0xc0000000;

	// Phases are on 0, 1, and 2
	//	Vbus is on 3
	ADC1->JSQR |= (uint32_t)((0b01 << 20)	// 2 conversions per sequence
						+ (3 << 15)			// 2nd channel in sequence
						+ (0 << 10)			// 1st channel in sequence
						+ (3 << 5)			// 2nd channel in sequence
						+ (0 << 0));		// 1st channel in sequence

	// Analog Isense on 8
	ADC1->JSQR |= (uint32_t)((0b01 << 20)	// 2 conversions per sequence
						+ (8 << 15)			// 2nd channel in sequence
						+ (8 << 10)			// 1st channel in sequence
						+ (8 << 5)			// 2nd channel in sequence
						+ (8 << 0));		// 1st channel in sequence


	ADC1->CR2 |= (uint32_t)(0b1 << 0);		// turn on A/D peripheral
	ADC2->CR2 |= (uint32_t)(0b1 << 0);		// turn on A/D peripheral
}
