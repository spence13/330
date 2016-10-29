/*
 * buttonHandler.h
 *
 *  Created on: Oct 31, 2015
 *      Author: spence13
 */

#ifndef BUTTONHANDLER_H_
#define BUTTONHANDLER_H_

#include "simonDisplay.h"

#define BUTTONHANDLER_ADC_EXPIRED_VALUE 2//used to set an appropriate wait time for ADC settle

// Get the simon region numbers. See the source code for the region numbering scheme.
uint8_t buttonHandler_getRegionNumber();

// Turn on the state machine. Part of the interlock.
void buttonHandler_enable();

// Turn off the state machine. Part of the interlock.
void buttonHandler_disable();

// Other state machines can call this function to see if the user has stopped touching the pad.
bool buttonHandler_releaseDetected();

// Standard tick function.
void buttonHandler_tick();


#endif /* BUTTONHANDLER_H_ */
