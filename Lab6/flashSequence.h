/*
 * flashSequence.h
 *
 *  Created on: Nov 4, 2015
 *      Author: spence13
 */


#ifndef FLASHSEQUENCE_H_
#define FLASHSEQUENCE_H_

#include "buttonHandler.h"
#include "globals.h"

//value of the timer
#define FLASHSEQUENCE_DELAY_EXPIRED_VALUE 6

// Turns on the state machine. Part of the interlock.
void flashSequence_enable();

// Turns off the state machine. Part of the interlock.
void flashSequence_disable();

// Other state machines can call this to determine if this state machine is finished.
bool flashSequence_completed();

// Standard tick function.
void flashSequence_tick();


#endif /* FLASHSEQUENCE_H_ */
