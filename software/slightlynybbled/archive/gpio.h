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

#ifndef GPIO_H
#define GPIO_H

#include "stm32f10x_gpio.h"

#define GPIO_INPUT_ANALOG			0b0000
#define GPIO_FLOATING_INPUT			0b0100
#define GPIO_INPUT_PU_OR_PD			0b1000
#define GPIO_OUTPUT_PP				0b0011
#define GPIO_OUTPUT_OPEN_DRN		0b0111
#define GPIO_OUTPUT_ALT_PP			0b1011
#define GPIO_OUTPUT_ALT_OPEN_DR		0b1111

#define GPIO_PORT_A	0
#define GPIO_PORT_B 1

#define GPIO_LO	0
#define GPIO_HI	1

void GPIO_pinSetup(uint16_t port, uint16_t pin, uint8_t pinState);
void GPIO_setOutputPin(unsigned int port, unsigned int pin);
void GPIO_clearOutputPin(unsigned int port, unsigned int pin);
bool GPIO_readInput(unsigned int port, unsigned int pin);

#endif
