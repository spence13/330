/*
 * simonDisplay.h
 *
 *  Created on: Oct 31, 2015
 *      Author: spence13
 */

#ifndef SIMONDISPLAY_H_
#define SIMONDISPLAY_H_


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "supportFiles/utils.h" //this is where utils/msDelay() is found for running clockDisplay_runtest()
#include "supportFiles/display.h"


// Width, height of the simon "buttons"
#define SIMON_DISPLAY_BUTTON_WIDTH 60
#define SIMON_DISPLAY_BUTTON_HEIGHT 60

// Given coordinates from the touch pad, computes the region number.

// The entire touch-screen is divided into 4 rectangular regions, numbered 0 - 3.
// Each region will be drawn with a different color. Colored buttons remind
// the user which square is associated with each color. When you press
// a region, computeRegionNumber returns the region number that is used
// by the other routines.
/*
|----------|----------|
|          |          |
|    0     |     1    |
|  (RED)   | (YELLOW) |
-----------------------
|          |          |
|     2    |    3     |
|  (BLUE)  |  (GREEN) |
-----------------------
*/

// These are the definitions for the regions.
#define SIMON_DISPLAY_REGION_0 0
#define SIMON_DISPLAY_REGION_1 1
#define SIMON_DISPLAY_REGION_2 2
#define SIMON_DISPLAY_REGION_3 3

//used for setting the display colors
#define SIMON_DISPLAY_GREEN DISPLAY_GREEN
#define SIMON_DISPLAY_BLACK DISPLAY_BLACK
#define SIMON_DISPLAY_BLUE DISPLAY_BLUE
#define SIMON_DISPLAY_RED DISPLAY_RED
#define SIMON_DISPLAY_YELLOW DISPLAY_YELLOW
#define SIMON_DISPLAY_TEXT_SIZE 2

//these deal with the board size and how many pixels high and wide it is
#define SIMON_DISPLAY_PIXEL_HEIGHT 240
#define SIMON_DISPLAY_HALF_HEIGHT 120
#define SIMON_DISPLAY_PIXEL_WIDTH 320
#define SIMON_DISPLAY_HALF_WIDTH 160

//these correctly position the buttons
#define SIMON_DISPLAY_BTN_OFFSET_X 50
#define SIMON_DISPLAY_BTN_OFFSET_Y 30



int8_t simonDisplay_computeRegionNumber(int16_t x, int16_t y);

// Draws a colored "button" that the user can touch.
// The colored button is centered in the region but does not fill the region.
void simonDisplay_drawButton(uint8_t regionNumber);

// Convenience function that draws all of the buttons.
void simonDisplay_drawAllButtons();

// Draws a bigger square that completely fills the region.
// If the erase argument is true, it draws the square as black background to "erase" it.
void simonDisplay_drawSquare(uint8_t regionNo, bool erase);

// Runs a brief demonstration of how buttons can be pressed and squares lit up to implement the user
// interface of the Simon game. The routine will continue to run until the touchCount has been reached, e.g.,
// the user has touched the pad touchCount times.

// Convenience function that erases all of the buttons.
void simonDisplay_eraseAllButtons();



#endif /* SIMONDISPLAY_H_ */
