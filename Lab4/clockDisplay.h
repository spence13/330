/*
 * clockDisplay.h
 *
 *  Created on: Sep 26, 2015
 *      Author: spence13
 */

#ifndef CLOCKDISPLAY_H_
#define CLOCKDISPLAY_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "supportFiles/utils.h" //this is where utils/msDelay() is found for running clockDisplay_runtest()
#include "supportFiles/display.h" //this includes functions used for the display

//these #defines deals with display size and color of board and text
#define CLOCK_DISPLAY_GREEN DISPLAY_GREEN
#define CLOCK_DISPLAY_BLACK DISPLAY_BLACK
#define CLOCK_DISPLAY_BLUE DISPLAY_BLUE
#define CLOCK_DISPLAY_TEXT_SIZE 6 //most #defines are parametrically tied to this one

//these deal with the board size and how many pixels high and wide it is
#define CLOCK_DISPLAY_PIXEL_HEIGHT 240
#define CLOCK_DISPLAY_HALF_HEIGHT 120
#define CLOCK_DISPLAY_PIXEL_WIDTH 320
#define CLOCK_DISPLAY_HALF_WIDTH 160

//these deal with the width and height of the text characters displayed
#define CLOCK_DISPLAY_CHAR_WIDTH 5*CLOCK_DISPLAY_TEXT_SIZE
#define CLOCK_DISPLAY_HALF_CHAR_WIDTH 2.5*CLOCK_DISPLAY_TEXT_SIZE
#define CLOCK_DISPLAY_DOUBLE_CHAR_WIDTH 10*CLOCK_DISPLAY_TEXT_SIZE
#define CLOCK_DISPLAY_CHAR_HEIGHT 7*CLOCK_DISPLAY_TEXT_SIZE
#define CLOCK_DISPLAY_HALF_CHAR_HEIGHT 3.5*CLOCK_DISPLAY_TEXT_SIZE
#define CLOCK_DISPLAY_DOUBLE_CHAR_HEIGHT 14*CLOCK_DISPLAY_TEXT_SIZE
#define CLOCK_DISPLAY_CHAR_OFFSET 4// the equivalent width of 4 characters
#define CLOCK_DISPLAY_SPACE_OFFSET 3.5*CLOCK_DISPLAY_TEXT_SIZE // the equivalent width of the space between the characters for 4 characters

//these break down the display width of all the characters put together
#define CLOCK_DISPLAY_HALF_TOT_NUMBER_WIDTH (CLOCK_DISPLAY_CHAR_WIDTH*CLOCK_DISPLAY_CHAR_OFFSET+CLOCK_DISPLAY_SPACE_OFFSET)/2
#define CLOCK_DISPLAY_TOT_NUMBER_WIDTH (CLOCK_DISPLAY_CHAR_WIDTH*CLOCK_DISPLAY_CHAR_OFFSET+CLOCK_DISPLAY_SPACE_OFFSET)

//these deal with the positioning of the characters and colons on the board
#define CLOCK_DISPLAY_XPOS_HOUR_TENS CLOCK_DISPLAY_HALF_WIDTH-(4*CLOCK_DISPLAY_CHAR_WIDTH)-3*CLOCK_DISPLAY_TEXT_SIZE
#define CLOCK_DISPLAY_XPOS_HOUR_ONES CLOCK_DISPLAY_HALF_WIDTH-(3*CLOCK_DISPLAY_CHAR_WIDTH)-2*CLOCK_DISPLAY_TEXT_SIZE
#define CLOCK_DISPLAY_XPOS_MIN_TENS CLOCK_DISPLAY_HALF_WIDTH-(CLOCK_DISPLAY_CHAR_WIDTH)//-.5*CLOCK_DISPLAY_TEXT_SIZE
#define CLOCK_DISPLAY_XPOS_MIN_ONES CLOCK_DISPLAY_HALF_WIDTH+(CLOCK_DISPLAY_TEXT_SIZE)
#define CLOCK_DISPLAY_XPOS_SEC_TENS (CLOCK_DISPLAY_HALF_WIDTH)+(2*CLOCK_DISPLAY_CHAR_WIDTH)+(3*CLOCK_DISPLAY_TEXT_SIZE)
#define CLOCK_DISPLAY_XPOS_SEC_ONES (CLOCK_DISPLAY_HALF_WIDTH)+(3*CLOCK_DISPLAY_CHAR_WIDTH)+(3*CLOCK_DISPLAY_TEXT_SIZE)
#define CLOCK_DISPLAY_YPOS_DIGITS (CLOCK_DISPLAY_HALF_HEIGHT)-(CLOCK_DISPLAY_HALF_CHAR_HEIGHT)
#define CLOCK_DISPLAY_LEFT_COLON CLOCK_DISPLAY_HALF_WIDTH-(2*CLOCK_DISPLAY_CHAR_WIDTH)-2*CLOCK_DISPLAY_TEXT_SIZE
#define CLOCK_DISPLAY_RIGHT_COLON CLOCK_DISPLAY_HALF_WIDTH+(CLOCK_DISPLAY_CHAR_WIDTH)+CLOCK_DISPLAY_TEXT_SIZE

//these deal with the X positioning of the triangles displayed on the board
#define CLOCK_DISPLAY_HOUR_TRI_X1 CLOCK_DISPLAY_HALF_WIDTH-CLOCK_DISPLAY_TOT_NUMBER_WIDTH
#define CLOCK_DISPLAY_HOUR_TRI_X2 (CLOCK_DISPLAY_HALF_WIDTH)-(CLOCK_DISPLAY_HALF_TOT_NUMBER_WIDTH)
#define CLOCK_DISPLAY_HOUR_TRI_X3 (CLOCK_DISPLAY_HALF_WIDTH)-(3*CLOCK_DISPLAY_CHAR_WIDTH+(2.5*CLOCK_DISPLAY_TEXT_SIZE))
#define CLOCK_DISPLAY_MIN_TRI_X1 (CLOCK_DISPLAY_HALF_WIDTH)-CLOCK_DISPLAY_CHAR_WIDTH-.5*CLOCK_DISPLAY_TEXT_SIZE
#define CLOCK_DISPLAY_MIN_TRI_X2 (CLOCK_DISPLAY_HALF_WIDTH)+CLOCK_DISPLAY_CHAR_WIDTH+.5*CLOCK_DISPLAY_TEXT_SIZE
#define CLOCK_DISPLAY_MIN_TRI_X3 CLOCK_DISPLAY_HALF_WIDTH
#define CLOCK_DISPLAY_SEC_TRI_X1 (CLOCK_DISPLAY_HALF_WIDTH)+(CLOCK_DISPLAY_HALF_TOT_NUMBER_WIDTH)
#define CLOCK_DISPLAY_SEC_TRI_X2 (CLOCK_DISPLAY_HALF_WIDTH)+CLOCK_DISPLAY_TOT_NUMBER_WIDTH
#define CLOCK_DISPLAY_SEC_TRI_X3 (CLOCK_DISPLAY_HALF_WIDTH)+(3*CLOCK_DISPLAY_CHAR_WIDTH+(2.5*CLOCK_DISPLAY_TEXT_SIZE))

//these deal with the Y positioning of the triangles on the display
#define CLOCK_DISPLAY_UPPER_TRI_BASE_YPOS CLOCK_DISPLAY_HALF_HEIGHT-CLOCK_DISPLAY_CHAR_HEIGHT
#define CLOCK_DISPLAY_UPPER_TRI_TIP_YPOS CLOCK_DISPLAY_HALF_HEIGHT-(CLOCK_DISPLAY_DOUBLE_CHAR_HEIGHT)
#define CLOCK_DISPLAY_LOWER_TRI_BASE_YPOS CLOCK_DISPLAY_HALF_HEIGHT+CLOCK_DISPLAY_CHAR_HEIGHT
#define CLOCK_DISPLAY_LOWER_TRI_TIP_YPOS CLOCK_DISPLAY_HALF_HEIGHT+(CLOCK_DISPLAY_DOUBLE_CHAR_HEIGHT)

//these deal with the max length the hour, min, sec can be
#define CLOCK_DISPLAY_TIME_CHAR_LENGTH 80
#define CLOCK_DISPLAY_HOUR_MAX_TIME 12 //max time that we want hours to be before resetting
#define CLOCK_DISPLAY_MIN_MAX_TIME 59 //max time that we want minutes to be before resetting
#define CLOCK_DISPLAY_SEC_MAX_TIME 59 //max time that we want seconds to be before resetting

#define CLOCK_DISPLAY_TOTAL_SECONDS 60
// Assuming that the prescaler = 0, the formula for computing the load value based upon the desired period is:
// load-value = (period * timer-clock) - 1
#define CLOCK_DISPLAY_TIMER_PERIOD .05 //longest time is around 35ms for one tick cycle so give it 50ms
#define CLOCK_DISPLAY_TIMER_CLOCK_FREQUENCY (XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / 2)
#define CLOCK_DISPLAY_TIMER_LOAD_VALUE ((CLOCK_DISPLAY_TIMER_PERIOD * CLOCK_DISPLAY_TIMER_CLOCK_FREQUENCY) - 1.0)


void clockDisplay_init();  // Called only once - performs any necessary inits.
void clockDisplay_updateTimeDisplay(bool forceUpdateAll);  // Updates the time display with latest time.
void clockDisplay_performIncDec();         // Performs the increment or decrement, depending upon the touched region.
void clockDisplay_advanceTimeOneSecond();  // Advances the time forward by 1 second.
void clockDisplay_runTest();               // Run a test of clock-display functions.


#endif /* CLOCKDISPLAY_H_ */
