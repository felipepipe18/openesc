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
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "openesc.h"
#include "rcPwm.h"
#include "motor.h"

int main(void)
{
	// Setup all of the pins and peripherals
	//	of the openESC board
	setupOpenESC();
	// setupRcPwm();
	// setupMotor();

	// Implement the simplest form of open-loop motor control
	//	using just the input RC signal and the motor interface
    while(1)
    {
    	// Get requested duty cycle from rcPwm

    	// Pass requested duty cycle to the motor
    }
}
