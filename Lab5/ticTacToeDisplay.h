/*
 * ticTacToeDisplay.h
 *
 *  Created on: Oct 10, 2015
 *      Author: spence13
 */

#ifndef TICTACTOEDISPLAY_H_
#define TICTACTOEDISPLAY_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "src/Lab2/buttons.h"
#include "src/Lab2/switches.h"
#include "supportFiles/display.h"
#include "supportFiles/utils.h"


//these deal with resetting the display.h settings to the correct name
#define TICTACTOEDISPLAY_GREEN DISPLAY_GREEN
#define TICTACTOEDISPLAY_BLACK DISPLAY_BLACK
#define TICTACTOEDISPLAY_BLUE DISPLAY_BLUE
#define TICTACTOEDISPLAY_TEXT_SIZE 2

//these deal with the board size and how many pixels high and wide it is
#define TICTACTOEDISPLAY_PIXEL_HEIGHT 240
#define TICTACTOEDISPLAY_HALF_HEIGHT 120
#define TICTACTOEDISPLAY_TWO_THIRD_HEIGHT 160
#define TICTACTOEDISPLAY_ONE_THIRD_HEIGHT 80
#define TICTACTOEDISPLAY_ONE_SIXTH_HEIGHT 40
#define TICTACTOEDISPLAY_FIVE_SIXTH_HEIGHT 200
#define TICTACTOEDISPLAY_PIXEL_WIDTH 320
#define TICTACTOEDISPLAY_HALF_WIDTH 160
#define TICTACTOEDISPLAY_TWO_THIRD_WIDTH 214
#define TICTACTOEDISPLAY_ONE_THIRD_WIDTH 107
#define TICTACTOEDISPLAY_ONE_SIXTH_WIDTH 53
#define TICTACTOEDISPLAY_FIVE_SIXTH_WIDTH 267

//these handle the X and O characters
#define TICTACTOEDISPLAY_CIRCLE_RADIUS 30
#define TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET 10
#define TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET 10

//these handle buttons and swithces
#define TICTACTOEDISPLAY_BTN0_ON 0x1
#define TICTACTOEDISPLAY_BTN1_ON 0x2
#define TICTACTOEDISPLAY_SWITCH0_ON 0x1
#define TICTACTOEDISPLAY_SWITCH0_OFF 0x0

//these are the columns numbers
#define TICTACTOEDISPLAY_COLUMN_LEFT 0
#define TICTACTOEDISPLAY_COLUMN_MIDDLE 1
#define TICTACTOEDISPLAY_COLUMN_RIGHT 2

//these are the row numbers
#define TICTACTOEDISPLAY_ROW_TOP 0
#define TICTACTOEDISPLAY_ROW_MIDDLE 1
#define TICTACTOEDISPLAY_ROW_BOTTOM 2


// Inits the tic-tac-toe display, draws the lines that form the board.
void ticTacToeDisplay_init();

// Draws an X at the specified row and column.
void ticTacToeDisplay_drawX(uint8_t row, uint8_t column);

// Draws an O at the specified row and column.
void ticTacToeDisplay_drawO(uint8_t row, uint8_t column);

// After a touch has been detected and after the proper delay, this sets the row and column arguments
// according to where the user touched the board.
void ticTacToeDisplay_touchScreenComputeBoardRowColumn(uint8_t* row, uint8_t* column);

// Runs a test of the display. Does the following.
// Draws the board. Each time you touch one of the screen areas, the screen will paint
// an X or an O, depending on whether switch 0 (SW0) is slid up (O) or down (X).
// When BTN0 is pushed, the screen is cleared. The test terminates when BTN1 is pushed.
void ticTacToeDisplay_runTest();

// This will draw the four board lines.
void ticTacToeDisplay_drawBoardLines();

void ticTacToeDisplay_eraseO(uint8_t row, uint8_t column);
void ticTacToeDisplay_eraseX(uint8_t row, uint8_t column);
void ticTacToeDisplay_eraseBoardLines();


#endif /* TICTACTOEDISPLAY_H_ */
