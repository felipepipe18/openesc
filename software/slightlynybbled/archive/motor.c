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

_motor BLDC_motor;

/*
 * Function:	void initMotor(void)
 *
 * Purpose:		This function is called by higher-level software in order
 * 					to initialize the motor in preparation for operation.
 *
 * Parameters:	none
 *
 * Returns:		none
 *
 * Globals affected:	none
 */
void
BLDC_initMotor(void)
{
	MPWM_initMotorPwm();
	MPWM_setMotorPwmFreq(16000);

	BLDC_initAdc();

	BLDC_stopMotor();

	BLDC_commandDirection(BLDC_POS);
}

/*
 * Function:	void startMotor(void)
 *
 * Purpose:		This function is called by higher-level software
 * 					when motor rotation should begin
 *
 * Parameters:	none
 *
 * Returns:		none
 *
 * Globals affected:	BLDC_motor.sector, BLDC_motor.state
 */
void
BLDC_startMotor(void)
{
	// Only allow this routine to execute if
	//	the motor is in the STOPPED state
	if(BLDC_motor.state == MOTOR_STOPPED){
		BLDC_motor.sector = 0;
		BLDC_motor.state = MOTOR_STARTING;
	}
}

/*
 * Function:	void stopMotor(void)
 *
 * Purpose:		This function is called by higher-level software
 * 					when motor rotation should cease
 *
 * Parameters:	none
 *
 * Returns:		none
 *
 * Globals affected:	BLDC_motor.sector, BLDC_motor.state
 */
void
BLDC_stopMotor(void)
{
	// Place each phase in the DORMANT state
	MPWM_setPhaseDutyCycle(MPWM_PH_A, MPWM_DORMANT, 0);
	MPWM_setPhaseDutyCycle(MPWM_PH_B, MPWM_DORMANT, 0);
	MPWM_setPhaseDutyCycle(MPWM_PH_C, MPWM_DORMANT, 0);

	// Place the motor in the STOPPED state
	BLDC_motor.state = MOTOR_STOPPED;
	BLDC_motor.sector = 0;
}

/*
 * Function:	void BLDC_commandDutyCycle(unsigned int dutyCycle);
 *
 * Purpose:		This function is called by higher-level software
 * 					to modify the duty cycle.
 *
 * Parameters:	uint16_t dutyCycle		This is the fixed-point representation
 * 										of the motor duty cycle.  0%-100% is scaled
 * 										to 0-65535
 *
 * Returns:		none
 *
 * Globals affected:	BLDC_motor.dutyCycle
 */
void
BLDC_commandDutyCycle(uint16_t dutyCycle)
{
	BLDC_motor.dutyCycle = dutyCycle;
}

/*
 * Function:	void BLDC_commandDirection(uint8_t direction);
 *
 * Purpose:		This function is called by higher-level software
 * 					to modify the motor direction.
 *
 * Parameters:	bool direction	This determines the direction of the motor.  Valid
 * 								values are BLDC_POS and BLDC_NEG.
 *
 * Returns:		none
 *
 * Globals affected:	BLDC_motor.direction
 */
void
BLDC_commandDirection(bool direction)
{
	BLDC_motor.direction = direction;
}

/*
 * Function:	void commutate(void)
 *
 * Purpose:		This function is called when the motor phase state
 * 					should be stepped to the next phase state based
 * 					on the current rotor location (sector)
 *
 * Parameters:	none
 *
 * Returns:		none
 *
 * Globals affected:	BLDC_motor.sector
 */
void
BLDC_commutate(void)
{
	// Move to the next step in the 6-step scheme
	if(++BLDC_motor.sector > 5)
		BLDC_motor.sector = 0;

	// Use lookup tables to determine which phase should be high,
	//	low, and dormant based on the current sector (as defined by
	//	the positive direction).
	//
	//		sector	hiPhase	loPhase	dormantPhase
	//		0		PH_A	PH_B	PH_C
	//		1		PH_A	PH_C	PH_B
	//		2		PH_B	PH_C	PH_A
	//		3		PH_B	PH_A	PH_C
	//		4		PH_C	PH_A	PH_B
	//		5		PH_C	PH_B	PH_A
	const uint8_t hiPhaseTable[] = {MPWM_PH_A, MPWM_PH_A, MPWM_PH_B, MPWM_PH_B, MPWM_PH_C, MPWM_PH_C};
	const uint8_t loPhaseTable[] = {MPWM_PH_B, MPWM_PH_C, MPWM_PH_C, MPWM_PH_A, MPWM_PH_A, MPWM_PH_B};
	const uint8_t dormantPhaseTable[] = {MPWM_PH_C, MPWM_PH_B, MPWM_PH_A, MPWM_PH_C, MPWM_PH_B, MPWM_PH_A};

	// Load each phase with the appropriate duty cycle based on the sector and direction of the motor
	if(BLDC_motor.direction){
		MPWM_setPhaseDutyCycle(hiPhaseTable[BLDC_motor.sector], MPWM_HI_STATE, BLDC_motor.dutyCycle);
		MPWM_setPhaseDutyCycle(loPhaseTable[BLDC_motor.sector], MPWM_LO_STATE, BLDC_motor.dutyCycle);
		MPWM_setPhaseDutyCycle(dormantPhaseTable[BLDC_motor.sector], MPWM_DORMANT, BLDC_motor.dutyCycle);
	}else{
		MPWM_setPhaseDutyCycle(hiPhaseTable[BLDC_motor.sector], MPWM_LO_STATE, BLDC_motor.dutyCycle);
		MPWM_setPhaseDutyCycle(loPhaseTable[BLDC_motor.sector], MPWM_HI_STATE, BLDC_motor.dutyCycle);
		MPWM_setPhaseDutyCycle(dormantPhaseTable[BLDC_motor.sector], MPWM_DORMANT, BLDC_motor.dutyCycle);
	}
}

/*
 * Function:	uint8_t getMotorState(void)
 *
 * Purpose:		This function is called by higher-level software
 * 					to retrieve the current motor state.
 *
 * Parameters:	none
 *
 * Returns:		uint8_t BLDC_motor.state
 *
 * Globals affected:	none
 */
uint8_t
BLDC_getMotorState(void){
	return BLDC_motor.state;
}

/*
 * Function:	void ADC1_2_IRQHandler(void)
 *
 * Purpose:		This function is called when an ADC conversion sequence
 * 					has been completed and action is required.  The primary
 * 					duty of the function is to look at the current phase
 * 					voltages and decide when to commutate the motor.
 *
 * Parameters:	none
 *
 * Returns:		none
 *
 * Globals affected:	ADC1->SR, ADC2->SR
 */
void
ADC1_2_IRQHandler(void)
{
	/*
	 * TODO: Flesh out the interrupt so that it commutates the
	 * 			motor when the phase voltage reaches the correct
	 * 			threshold.
	 */

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
 * Function:	void initAdc(void)
 *
 * Purpose:		This function is called to initialize the ADC for operation
 *
 * Parameters:	none
 *
 * Returns:		none
 *
 * Globals affected:	All ADC1, ADC2 registers, NVIC interrupt vector
 */
void
BLDC_initAdc(void)
{
	/************************************************
	 * TODO: check for proper operation on hardware
	 ************************************************/

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
