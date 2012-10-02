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
 * Purpose: To define all of the pins in an easily
 *	human-readable format.
 *
 * Usage: This file should be included in "openesc.h"
*************************************************/

#ifndef OPENESC_V01
#define OPENESC_V01

#include "stm32f10x.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

#include <stdbool.h>

#include "rcPwm.h"
#include "motor.h"

#define PORT_CNF_INPUT_ANALOG			0b0000
#define PORT_CNF_FLOATING_INPUT			0b0100
#define PORT_CNF_INPUT_PU_OR_PD			0b1000
#define PORT_CNF_OUTPUT_PP				0b0000
#define PORT_CNF_OUTPUT_OPEN_DRN		0b0100
#define PORT_CNF_OUTPUT_ALT_PP			0b1000
#define PORT_CNF_OUTPUT_ALT_OPEN_DR		0b1100

#define PORT_MODE_INPUT		0b00
#define PORT_MODE_OUTPUT	0b11

// Define ADC pins
#define ANALOG_PHA_FBK_PIN		0
#define ANALOG_PHB_FBK_PIN		0
#define ANALOG_PHC_FBK_PIN		GPIO_Pin_2
#define ANALOG_BUS_VOLT_PIN		GPIO_Pin_3
#define ANALOG_CURR_SENSE_PIN	GPIO_Pin_0



// Define RC PWM pins
#define RC_PWM_IN_PIN	GPIO_Pin_1


// Define motor control PWM pins
#define MCPWM_AH_PIN	GPIO_Pin_10
#define MCPWM_BH_PIN	GPIO_Pin_9
#define MCPWM_CH_PIN	GPIO_Pin_8
#define MCPWM_AL_PIN	GPIO_Pin_15
#define MCPWM_BL_PIN	GPIO_Pin_14
#define MCPWM_CL_PIN	GPIO_Pin_13


// Define USART pins



// Define Fault pin
#define FAULT_INPUT_PIN	GPIO_Pin_7



// Define LED pins
#define ERROR_LED_PIN	GPIO_Pin_4
#define STATUS_LED_PIN	GPIO_Pin_5

typedef struct{
	uint32_t clockFreq;
} _openEsc;

_openEsc openEsc;

// Declare any functions that are implemented
//	in "openesc_v01.c"
void setupOpenESC(void);
void initHseClock(void);
void initHsiClock(void);
void initDio(void);

#endif
