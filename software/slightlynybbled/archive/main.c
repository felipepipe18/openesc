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
#include "openesc.h"
#include "gpio.h"

void initDio(void);

int main(void)
{
	// Initialize oscillator
	initHseClock();			// Initialize 16MHz in to 72MHz clock freq
	//initHsiClock();		// Initialize 8MHz internal Osc to 64MHz clock freq

	// Initialize GPIO

	// Initialize ADC

	// Initialize RC PWM module

	// Initialize bldc motor

	// Initialize CLI

	// Initialize bootloader


	// Implement the simplest form of open-loop motor control
	//	using just the input RC signal and the motor interface
    while(1)
    {
    	// Get requested duty cycle from rcPwm

    	// Pass requested duty cycle to the motor
    }
}

void
initDio(void)
{
	// Setup LED pins
	GPIO_pinSetup(GPIO_PORT_B, 4, GPIO_OUTPUT_PP);	// Error LED
	GPIO_pinSetup(GPIO_PORT_B, 5, GPIO_OUTPUT_PP);	// Status LED

	// Setup analog input pins
	// Analog input pins are not remapped
	GPIO_pinSetup(GPIO_PORT_A, 0, GPIO_INPUT_ANALOG);	// PHA FBK
	GPIO_pinSetup(GPIO_PORT_A, 1, GPIO_INPUT_ANALOG);	// PHB FBK
	GPIO_pinSetup(GPIO_PORT_A, 2, GPIO_INPUT_ANALOG);	// PHC FBK
	GPIO_pinSetup(GPIO_PORT_A, 3, GPIO_INPUT_ANALOG);	// Bus Voltage
	GPIO_pinSetup(GPIO_PORT_B, 0, GPIO_INPUT_ANALOG);

	// Setup current fault as a pull-up to eliminate external pull-ups
	// Overcurrent sensing pin is not remapped
	GPIO_pinSetup(GPIO_PORT_A, 7, GPIO_INPUT_PU_OR_PD);	// Overcurrent

	// Setup RC PWM input pin
	// RC PWM input pin is not remapped
	GPIO_pinSetup(GPIO_PORT_B, 1, GPIO_FLOATING_INPUT);

    // Setup TIM1 outputs
	// TIM1 pins are not remapped
	GPIO_pinSetup(GPIO_PORT_B, 13, GPIO_OUTPUT_ALT_PP);
	GPIO_pinSetup(GPIO_PORT_B, 14, GPIO_OUTPUT_ALT_PP);
	GPIO_pinSetup(GPIO_PORT_B, 15, GPIO_OUTPUT_ALT_PP);
	GPIO_pinSetup(GPIO_PORT_A, 8, GPIO_OUTPUT_ALT_PP);
	GPIO_pinSetup(GPIO_PORT_A, 9, GPIO_OUTPUT_ALT_PP);
	GPIO_pinSetup(GPIO_PORT_A, 10, GPIO_OUTPUT_ALT_PP);
}
