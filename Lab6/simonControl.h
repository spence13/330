/*
 * simonControl.h
 *
 *  Created on: Nov 16, 2015
 *      Author: spence13
 */

#ifndef SIMONCONTROL_H_
#define SIMONCONTROL_H_

#include "simonDisplay.h"
#include "flashSequence.h"
#include "verifySequence.h"
#include "globals.h"

//controlling the display text variables
#define SIMONCONTROL_BLACK DISPLAY_BLACK
#define SIMONCONTROL_GREEN DISPLAY_GREEN
#define SIMONCONTROL_TEXT_SIZE 2

//display width and height
#define SIMONCONTROL_HALF_PIXEL_HEIGHT 240/2
#define SIMONCONTROL_HALF_PIXEL_WIDTH 320/5

//timer value
#define SIMONCONTROL_VERIFY_TIMER_EXPIREDVALUE 50
#define SIMONCONTROL_LEVELTIMER_EXPIREDVALUE 50
#define SIMONCONTROL_MAX_ARRAY 100

//these deal with lengths of sequence and their min values
#define SIMONCONTROL_MIN_ITERATION_LENGTH 1
#define SIMONCONTROL_MIN_SEQUENCE_LENGTH 3

//implements the state machine
void simonControl_tick();

//creates an array with random numbers
void randomizeArray();


#endif /* SIMONCONTROL_H_ */
