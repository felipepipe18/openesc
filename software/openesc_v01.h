

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
#include "stm32f10x_rcc.h"
#include "misc.h"

#include <stdbool.h>

typedef struct{
	uint32_t clockFreq;
} _openEsc;

_openEsc openEsc;

// Declare any functions that are implemented
//	in "openesc_v01.c"
void initHseClock(void);
void initHsiClock(void);


#endif
