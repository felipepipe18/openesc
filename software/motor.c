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

/*
 * Call this function to start the motor
 */
void
startMotor(void)
{
	// Only allow this routine to execute if
	//	the motor is in the STOPPED state
	if(motor.state == MOTOR_STOPPED){
		motor.sector = 0;
		motor.state = MOTOR_STARTING;
	}
}


/*
 * Call this function to stop the motor
 */
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

/*
 * Call this function to commutate the motor by one step
 */
void
commutate(void)
{
	// Move to the next step in the 6-step scheme
	if(++motor.sector > 5)
		motor.sector = 0;

	// Use lookup tables to determine which phase should be high,
	//	low, and dormant based on the current sector.
	//
	//		sector	hiPhase	loPhase	dormantPhase
	//		0		PH_A	PH_B	PH_C
	//		1		PH_A	PH_C	PH_B
	//		2		PH_B	PH_C	PH_A
	//		3		PH_B	PH_A	PH_C
	//		4		PH_C	PH_A	PH_B
	//		5		PH_C	PH_B	PH_A
	const uint8_t hiPhaseTable[] = {PH_A, PH_A, PH_B, PH_B, PH_C, PH_C};
	const uint8_t loPhaseTable[] = {PH_B, PH_C, PH_C, PH_A, PH_A, PH_B};
	const uint8_t dormantPhaseTable[] = {PH_C, PH_B, PH_A, PH_C, PH_B, PH_A};

	// Load each phase with the appropriate duty cycle based on the sector
	setPhaseDutyCycle(hiPhaseTable[motor.sector], HI_STATE, motor.dutyCycle);
	setPhaseDutyCycle(loPhaseTable[motor.sector], LO_STATE, motor.dutyCycle);
	setPhaseDutyCycle(dormantPhaseTable[motor.sector], DORMANT, motor.dutyCycle);
}

uint8_t
getMotorState(void){
	return motor.state;
}

/*
 * TODO: Flesh out the interrupt so that it commutates the
 * 			motor when the phase voltage reaches the correct
 * 			threshold.
 */
void
ADC1_2_IRQHandler(void)
{
	// Check to see which flag is set
	bool adc1Flag = ADC1->SR & ~(0b1 << 2);

	// Execute everything in this if statement when
	//	the adc1Flag is set.  An ADC1 flag means that
	//	one of the phases was just measured along with
	//	the bus voltage.
	if(adc1Flag){



		ADC1->SR &= ~((uint32_t)(0b1 << 2));	// Clear the interrupt flag

	// Otherwise, the adc2Flag must be set, so everything
	//	in the else statement should be executed.  An ADC2
	//	flag means that two current measurements were taken.
	}else{


		ADC2->SR &= ~((uint32_t)(0b1 << 2));	// Clear the interrupt flag
	}


}

/*
 * Use this function to initialize the motor required modules and variables
 */
void
initMotor(void)
{
	initMotorPwm();
	setMotorPwmFreq(16000);

	initAdc();

	stopMotor();
}

/************************************************
 * TODO: check for proper operation on hardware
 ************************************************/
void
initAdc(void)
{
	// Clear the injected scan interrupt flag
	ADC1->SR &= ~((uint32_t)(0b1 << 2));
	ADC2->SR &= ~((uint32_t)(0b1 << 2));

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


	// Initialize interrupt vector location for ADC1 and ADC2
	NVIC_InitTypeDef nvicInitStruct;
	nvicInitStruct.NVIC_IRQChannel = ADC1_2_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInitStruct);

	ADC1->CR2 |= (uint32_t)(0b1 << 0);		// turn on A/D peripheral
	ADC2->CR2 |= (uint32_t)(0b1 << 0);		// turn on A/D peripheral
}
