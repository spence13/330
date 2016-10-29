/*
 * verifySequence.h
 *
 *  Created on: Nov 6, 2015
 *      Author: spence13
 */

#ifndef VERIFYSEQUENCE_H_
#define VERIFYSEQUENCE_H_

#include "flashSequence.h"
#include "src/Lab2/buttons.h"

//value of the timer
#define VERIFYSEQUENCE_TOUCH_TIMER_EXPIRED_VALUE 40

// State machine will run when enabled.
void verifySequence_enable();

// This is part of the interlock. You disable the state-machine and then enable it again.
void verifySequence_disable();

// Used to detect if there has been a time-out error.
bool verifySequence_isTimeOutError();

// Used to detect if the user tapped the incorrect sequence.
bool verifySequence_isUserInputError();

// Used to detect if the verifySequence state machine has finished verifying.
bool verifySequence_isComplete();

// Standard tick function.
void verifySequence_tick();


#endif /* VERIFYSEQUENCE_H_ */
