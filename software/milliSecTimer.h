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

#ifndef MILLISECTIMER_H
#define MILLISECTIMER_H

/* Standard or provided libs */
#include "stm32f10x_tim.h"

/* User-generated libs */
#include "openesc_v01.h"

typedef struct{
	uint32_t milliSeconds;
} _timer;

extern _timer MSTMR_timer;

void MSTMR_initMilliSecTimer(void);
uint32_t MSTMR_getMilliSeconds(void);

#endif
