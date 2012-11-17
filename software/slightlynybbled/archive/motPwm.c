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

void
MPWM_initMotorPwm(void){
	// Clock division: tDTS = 1 * tCK_INT
	TIM1->CR1 |= (uint16_t)(0b00 << 8);

	MPWM_setMotorPwmFreq(20000);

	// Place each phase in the DORMANT state
	MPWM_setPhaseDutyCycle(MPWM_PH_A, MPWM_DORMANT, 0);
	MPWM_setPhaseDutyCycle(MPWM_PH_B, MPWM_DORMANT, 0);
	MPWM_setPhaseDutyCycle(MPWM_PH_C, MPWM_DORMANT, 0);

	// Dead-time generation 1us dead-time
	// TODO: verify dead time on scope
	TIM1->BDTR |= (uint16_t)72;

	// Master Output Enable on
	TIM1->BDTR |= (uint16_t)(1 << 15);

	// Set up channel 4 as a timer only
	//	capture/compare.  Load the CCR4 register
	//	every time the duty cycle is updated.
	//	Use the capture/compare event as the
	//	ADC trigger. *** commented out b/c these
	//	are the values at reset anyway ***
	//TIM1->CCMR2 |= (uint16_t)((0b0 << 15)	// OC4CE
	//						+ (0b000 << 12)	// OC4M
	//						+ (0b0 << 11)	// OC4PE
	//						+ (0b0 << 10)	// OC4FE
	//						+ (0b00 << 8)); // CC4S

	// Turn on event generation for the ADC
	//	TODO: Check to ensure that this doesn't
	//	need to be continually reset!  Datasheet
	//	says it is cleared by hardware.
	TIM1->EGR |= (uint16_t)(1 << 4);

	// Counter enabled
	TIM1->CR1 |= (uint16_t)(0b1 << 0);
}

/*
 * 	Function:	void MPWM_setMotorPwmFreq(uint16_t pwmFrequency);
 *
 * 	Purpose:	To easily set the pwm frequency for the motor PWM
 *
 * 	Parameters:	uint16_t pwmFrequency	Valid values are 1200 to 65535, which
 * 										determine the pwm frequency in hertz
 */
void
MPWM_setMotorPwmFreq(uint16_t pwmFrequency)
{
	// Limit PWM frequency to lower values (in Hz).
	//	An upper limit is not necessary since the
	//	value is intrinsically limited by the width
	if(pwmFrequency < 1200)
		pwmFrequency = 1200;

	uint32_t timerOneFreq = openEsc.clockFreq;
	uint16_t arrValue = (uint16_t)(timerOneFreq/(uint32_t)pwmFrequency);

	TIM1->ARR = arrValue;
}

/*
 * 	Function:	void MPWM_setPhaseDutyCycle(uint8_t phase, uint8_t state, uint16_t dutyCycle);
 *
 * 	Purpose:	To provide a clean and easy interface with which to interact with the phase
 * 					duty cycles.
 *
 * 	Parameters:	uint8_t phase 		Valid values are PH_A, PH_B, and PH_C.  This
 * 									parameter will determine which phase is being
 * 									modified when the function is called.
 * 				uint8_t state		Valid values are HI_STATE, LO_STATE, and DORMANT.
 * 									This parameter will determine the polarity of the
 * 									phase or, in the case of DORMANT, will render the
 * 									high-side and low-side FETs inactive
 * 				uint16_t dutyCycle	Valid values range from 0 to 65535, which corresponds
 * 									to 0% - 100% duty cycle
 *
 * 	Notes:		PWM is edge-aligned with a preset dead time of about 1us.  On a particular phase,
 * 				one FET is always active except during dead-time when HI_STATE or LO_STATE has been
 * 				entered as one of the parameters.  This can result in motor states which are highly
 * 				regenerative when the user is attempting to slow a motor down.
 *
 * 	Example:	The user wants to have current from phase B to phase A at an effective duty cycle
 * 				of 28.3%.  First, convert the number to the fixed-point domain: 28.3% of 65535 is 18546.
 * 				Then, call the functions to setup the appropriate outputs:
 * 				setPhaseDutyCycle(PH_C, DORMANT, 0);
 * 				setPhaseDutyCycle(PH_B, HI_STATE, 18546);
 * 				setPhaseDutyCycle(PH_A, LO_STATE, 18546);
 */

void
MPWM_setPhaseDutyCycle(uint8_t phase, uint8_t state, uint16_t dutyCycle)
{
	// The duty cycle is in unsigned 16-bit fractional number that
	//	needs to be translated into the 16-bit CCRx registers using
	//	fixed-point math.  Also, calculate the adc sample time as a
	//	percentage of the duty cycle.  The CCR4 will be used to
	//	specify the ADC sample time within the waveform.
	uint16_t dutyCycleRegValue = ((uint32_t)dutyCycle * (uint32_t)TIM1->ARR) >> 16;
	uint16_t adcSampleTime = ((uint32_t)dutyCycle * 30000) >> 16;

	if(phase == MPWM_PH_A){
		// If the required state is HI_STATE, then the duty cycle should
		//	be applied with reference to the high-side switches (75% dc means
		//	75%dc on high-side)
		if(state == MPWM_HI_STATE){
			// A check to ensure that the phase is not already in a high state
			//	will keep the software from re-clearing and re-loading registers
			//	that won't actually change
			if(MPWM_motorPhase.stateA != MPWM_HI_STATE){
				TIM1->CCER |= (uint16_t)(0b0101 << 0);// TIM1 CH1 and CH1N on, active high

				TIM1->CCMR1 &= 0xff00;	// clear CC1 bits to default
				TIM1->CCMR1 |= (uint16_t)(0b01100000 << 0);	// pwm mode 1
				MPWM_motorPhase.stateA = MPWM_HI_STATE;
			}

			TIM1->CCR1 = dutyCycleRegValue;	// Load the duty cycle register
			TIM1->CCR4 = adcSampleTime;		// Load the adc trigger register

		// If the required state is LO_STATE, then the duty cycle should
		//	be applied with reference to the high-side switches (75% dc means
		//	75%dc on low-side)
		}else if(state == MPWM_LO_STATE){
			// A check to ensure that the phase is not already in a low state
			//	will keep the software from re-clearing and re-loading registers
			//	that won't actually change
			if(MPWM_motorPhase.stateA != MPWM_LO_STATE){
				TIM1->CCER |= (uint16_t)(0b0101 << 0);	// TIM1 CH1 and CH1N on, active high

				TIM1->CCMR1 &= 0xff00;	// clear CC1 bits to default
				TIM1->CCMR1 |= (uint16_t)(0b01110000 << 0);	// pwm mode 2

				MPWM_motorPhase.stateA = MPWM_LO_STATE;
			}

			TIM1->CCR1 = dutyCycleRegValue;	// Load the duty cycle register
			TIM1->CCR4 = adcSampleTime;		// Load the adc trigger register

		// If the required state is DORMANT, then turn both high phase
		//	and low phase off
		}else{
			TIM1->CCER &= 0xfff0;	// turn off pwm output, high-side and low-side
			MPWM_motorPhase.stateA = MPWM_DORMANT;
		}

	// Loads PH_C variables and registers.
	//	Same idea as PH_A logic above, just without comments
	}else if(phase == MPWM_PH_B){
		if(state == MPWM_HI_STATE){
			if(MPWM_motorPhase.stateB != MPWM_HI_STATE){
				TIM1->CCER |= (uint16_t)(0b0101 << 4);

				TIM1->CCMR1 &= 0x00ff;
				TIM1->CCMR1 |= (uint16_t)(0b01100000 << 8);
				MPWM_motorPhase.stateB = MPWM_HI_STATE;
			}

			TIM1->CCR2 = dutyCycleRegValue;
			TIM1->CCR4 = adcSampleTime;
		}else if(state == MPWM_LO_STATE){
			if(MPWM_motorPhase.stateB != MPWM_LO_STATE){
				TIM1->CCER |= (uint16_t)(0b0101 << 4);

				TIM1->CCMR1 &= 0x00ff;
				TIM1->CCMR1 |= (uint16_t)(0b01110000 << 8);

				MPWM_motorPhase.stateB = MPWM_LO_STATE;
			}

			TIM1->CCR2 = dutyCycleRegValue;
			TIM1->CCR4 = adcSampleTime;
		}else{
			TIM1->CCER &= 0xff0f;
			MPWM_motorPhase.stateB = MPWM_DORMANT;
		}

	// Loads PH_C variables and registers.
	//	Same idea as PH_A logic above, just without comments
	}else if(phase == MPWM_PH_C){
		if(state == MPWM_HI_STATE){
			if(MPWM_motorPhase.stateC != MPWM_HI_STATE){
				TIM1->CCER |= (uint16_t)(0b0101 << 8);

				TIM1->CCMR2 &= 0xff00;
				TIM1->CCMR2 |= (uint16_t)(0b01100000 << 0);

				MPWM_motorPhase.stateC = MPWM_HI_STATE;
			}

			TIM1->CCR3 = dutyCycleRegValue;
			TIM1->CCR4 = adcSampleTime;
		}else if(state == MPWM_LO_STATE){
			if(MPWM_motorPhase.stateC != MPWM_LO_STATE){
				TIM1->CCER |= (uint16_t)(0b0101 << 8);

				TIM1->CCMR2 &= 0xff00;
				TIM1->CCMR2 |= (uint16_t)(0b01110000 << 0);

				MPWM_motorPhase.stateC = MPWM_LO_STATE;
			}

			TIM1->CCR3 = dutyCycleRegValue;
			TIM1->CCR4 = adcSampleTime;
		}else{
			TIM1->CCER &= 0xf0ff;
			MPWM_motorPhase.stateC = MPWM_DORMANT;
		}
	}
}



