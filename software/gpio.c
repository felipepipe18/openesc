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

#include "gpio.h"

void
GPIO_pinSetup(uint16_t port, uint16_t pin, uint8_t pinState)
{
	switch(port)
	{
		case GPIO_PORT_A:
		{
			if((pin >= 0) && (pin <= 7)){
				// clear the appropriate bits, then set the appropriate bits
				GPIOA->CRL &= (uint32_t)~(0b1111 << (pin * 4));
				GPIOA->CRL |= (uint32_t)(pinState << (pin * 4));
			}else if((pin >= 8) && (pin <= 15)){
				// clear the appropriate bits, then set the appropriate bits
				GPIOA->CRH &= (uint32_t)~(0b1111 << ((pin - 8) * 4));
				GPIOA->CRH |= (uint32_t)(pinState << ((pin - 8) * 4));
			}else{
				/*
				 * This is a programmer's trap.  If the code gets to this while loop,
				 * then an invalid pin within this port has been specified.
				 */
				while(1);
			}
			break;
		}
		case GPIO_PORT_B:
		{
			if((pin >= 0) && (pin <= 7)){
				// clear the appropriate bits, then set the appropriate bits
				GPIOB->CRL &= (uint32_t)~(0b1111 << (pin * 4));
				GPIOB->CRL |= (uint32_t)(pinState << (pin * 4));
			}else if((pin >= 8) && (pin <= 15)){
				// clear the appropriate bits, then set the appropriate bits
				GPIOB->CRH &= (uint32_t)~(0b1111 << ((pin - 8) * 4));
				GPIOB->CRH |= (uint32_t)(pinState << ((pin - 8) * 4));
			}else{
				/*
				 * This is a programmer's trap.  If the code gets to this while loop,
				 * then an invalid pin within this port has been specified.
				 */
				while(1);
			}

			break;
		}
		default:
		{
			/*
			 * This is a programmer's trap.  If the code gets to this while loop,
			 * then an invalid port has been specified.
			 */
			while(1);
			break;
		}
	}
}

