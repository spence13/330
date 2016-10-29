/*
 * clockControl.h
 *
 *  Created on: Sep 26, 2015
 *      Author: spence13
 */

#ifndef CLOCKCONTROL_H_
#define CLOCKCONTROL_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "supportFiles/utils.h"
#include "supportFiles/display.h"
#include "clockDisplay.h"


#define CLOCK_CONTROL_ADD_EXPIRED_VALUE 1//must yield value of 50ms to wait for ADC to settle
#define CLOCK_CONTROL_AUTO_EXPIRED_VALUE 10 //must yield time of half second to wait until rapid counting
#define CLOCK_CONTROL_RATE_EXPIRED_VALUE 2 //must yield time of .1 seconds for rapid counting of numbers
#define CLOCK_CONTROL_SEC_EXPIRED_VALUE 20 //we want this value to yield time of 1 second

//this tick function is used for state machines and their transitions
void clockControl_tick();

#endif /* CLOCKCONTROL_H_ */
