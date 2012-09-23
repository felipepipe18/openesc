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

#include "motPwm.h"

// Declare any globals here
struct phase;

void
setupMotorPwm(void){
	// Clock division: tDTS = 1 * tCK_INT
	TIM1->CR1 |= (uint16_t)(0b00 << 8);

	// OC1M, OC2M, OC3M output compare mode PWM mode 1
	TIM1->CCMR1 |= ((uint16_t)(0b110 << 12)		// set OC2M
					+ (uint16_t)(0b110 << 4));	// set OC1M
	TIM1->CCMR2 |= (uint16_t)(0b110 << 4);		// set OC3M

	setMotorPwmFreq(20000);

	// TIM1 CH1 and CH1N on, active high
	TIM1->CCER |= (uint16_t)(0b0101 << 0);

	// TIM1 CH2 and CH2N on, active high
	TIM1->CCER |= (uint16_t)(0b0101 << 4);

	// TIM1 CH3 and CH3N on, active high
	TIM1->CCER |= (uint16_t)(0b0101 << 8);

	// Load CCRx registers with 0 (this turns off pwm)
	TIM1->CCR1 |= (uint16_t)(0);
	TIM1->CCR2 |= (uint16_t)(0);
	TIM1->CCR3 |= (uint16_t)(0);

	// Dead-time generation 1us dead-time
	// TODO: verify dead time on scope
	TIM1->BDTR |= 72;

	// Counter enabled
	TIM1->CR1 |= (uint16_t)(0b1 << 0);
}

void
setMotorPwmFreq(uint32_t pwmFrequency)
{
	// Limit PWM frequency to upper and lower values
	if(pwmFrequency < 1200)
		pwmFrequency = 1200;

	if(pwmFrequency > 65535)
		pwmFrequency = 65535;

	uint32_t timerOneFreq = 72000000;
	uint16_t arrValue = (uint16_t)(timerOneFreq/pwmFrequency);

	TIM1->ARR = arrValue;
}

void
setMotorDutyCycle(uint8_t phase, uint8_t state, uint16_t dutyCycle)
{

}
