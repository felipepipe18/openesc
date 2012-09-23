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

	setMotorPwmFreq(20000);

	// Place each phase in the DORMANT state
	setMotorDutyCycle(PH_A, DORMANT, 0);
	setMotorDutyCycle(PH_B, DORMANT, 0);
	setMotorDutyCycle(PH_C, DORMANT, 0);

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
	// The duty cycle is in unsigned 16-bit fractional number that
	//	needs to be translated into the 16-bit CCRx registers using
	//	fixed-point math.
	uint16_t dutyCycleRegValue = ((uint32_t) dutyCycle * (uint32_t)TIM1->CCR1) >> 16;

	if(phase == PH_A){
		// If the required state is HI_STATE, then the duty cycle should
		//	be applied with reference to the high-side switches (75% dc means
		//	75%dc on high-side)
		if(state == HI_STATE){
			TIM1->CCER |= (uint16_t)(0b0101 << 0);// TIM1 CH1 and CH1N on, active high

			TIM1->CCMR1 &= 0xff00;	// clear CC1 bits to default
			TIM1->CCMR1 |= (uint16_t)(0b01100000 << 0);	// pwm mode 1

			TIM1->CCR1 = dutyCycleRegValue;
		// If the required state is LO_STATE, then the duty cycle should
		//	be applied with reference to the high-side switches (75% dc means
		//	75%dc on low-side)
		}else if(state == LO_STATE){
			TIM1->CCER |= (uint16_t)(0b0101 << 0);	// TIM1 CH1 and CH1N on, active high

			TIM1->CCMR1 &= 0xff00;	// clear CC1 bits to default
			TIM1->CCMR1 |= (uint16_t)(0b01110000 << 0);	// pwm mode 2

			TIM1->CCR1 = dutyCycleRegValue;	// Load the duty cycle register
		// If the required state is DORMANT, then turn both high phase
		//	and low phase off
		}else{
			TIM1->CCER &= 0xfff0;	// turn off pwm output, high-side and low-side
		}
	}else if(phase == PH_B){
		if(state == HI_STATE){
			TIM1->CCER |= (uint16_t)(0b0101 << 4);

			TIM1->CCMR1 &= 0x00ff;
			TIM1->CCMR1 |= (uint16_t)(0b01100000 << 8);

			TIM1->CCR2 = dutyCycleRegValue;
		}else if(state == LO_STATE){
			TIM1->CCER |= (uint16_t)(0b0101 << 4);

			TIM1->CCMR1 &= 0x00ff;
			TIM1->CCMR1 |= (uint16_t)(0b01110000 << 8);

			TIM1->CCR1 = dutyCycleRegValue;
		}else{
			TIM1->CCER &= 0xff0f;
		}
	}else if(phase == PH_C){
		if(state == HI_STATE){
			TIM1->CCER |= (uint16_t)(0b0101 << 8);

			TIM1->CCMR2 &= 0xff00;
			TIM1->CCMR2 |= (uint16_t)(0b01100000 << 0);

			TIM1->CCR3 = dutyCycleRegValue;
		}else if(state == LO_STATE){
			TIM1->CCER |= (uint16_t)(0b0101 << 8);

			TIM1->CCMR2 &= 0xff00;
			TIM1->CCMR2 |= (uint16_t)(0b01110000 << 0);

			TIM1->CCR3 = dutyCycleRegValue;
		}else{
			TIM1->CCER &= 0xf0ff;
		}
	}



}
