/*
 * ticTacToeDisplay.c
 *
 *  Created on: Oct 10, 2015
 *      Author: spence13
 */

#include "ticTacToeDisplay.h"



void ticTacToeDisplay_init()
{
    display_init();  // Must initialize all of the software and underlying hardware for LCD.
    display_fillScreen(TICTACTOEDISPLAY_BLACK);  // Blank the screen with all black
    display_setTextColor(TICTACTOEDISPLAY_GREEN);  // Make the text green.
    display_setTextSize(TICTACTOEDISPLAY_TEXT_SIZE);  // this sets the text size
    ticTacToeDisplay_drawBoardLines();//draw the board lines
}

void ticTacToeDisplay_drawX(uint8_t row, uint8_t column)
{
    uint16_t x1 = 0;
    uint16_t x2 = 0;
    uint16_t y1 = 0;
    uint16_t y2 = 0;

    //position the y coordinate correctly depending on row number
    if(row == TICTACTOEDISPLAY_ROW_TOP)//top row
    {
        y1 = TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET;//upper bound of X character
        y2 = TICTACTOEDISPLAY_ONE_THIRD_HEIGHT - TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET;//lower bound of X character
    }
    else if(row == TICTACTOEDISPLAY_ROW_MIDDLE)//middle row
    {
        y1 = TICTACTOEDISPLAY_ONE_THIRD_HEIGHT + TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET;//upper bound of X character
        y2 = TICTACTOEDISPLAY_TWO_THIRD_HEIGHT - TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET;//lower bound of X character
    }
    else if(row == TICTACTOEDISPLAY_ROW_BOTTOM)//bottom row
    {
        y1 = TICTACTOEDISPLAY_TWO_THIRD_HEIGHT + TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET;//upper bound of X character
        y2 = TICTACTOEDISPLAY_PIXEL_HEIGHT - TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET;//lower bound of X character
    }

    //position the x coordinate correctly depending on column number
    if(column == TICTACTOEDISPLAY_COLUMN_LEFT)//left column
    {
        x1 = TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET;//left bound of X character
        x2 = TICTACTOEDISPLAY_ONE_THIRD_WIDTH - TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET;//right bound of X character
    }
    else if(column == TICTACTOEDISPLAY_COLUMN_MIDDLE)//middle column
    {
        x1 = TICTACTOEDISPLAY_ONE_THIRD_WIDTH + TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET;//left bound of X character
        x2 = TICTACTOEDISPLAY_TWO_THIRD_WIDTH - TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET;//right bound of X character
    }
    else if(column == TICTACTOEDISPLAY_COLUMN_RIGHT)//right column
    {
        x1 = TICTACTOEDISPLAY_TWO_THIRD_WIDTH + TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET;//left bound of X character
        x2 = TICTACTOEDISPLAY_PIXEL_WIDTH - TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET;//right bound of X character
    }

    display_drawLine(x1, y1, x2, y2, TICTACTOEDISPLAY_GREEN);//top left to bottom right
    display_drawLine(x1, y2, x2, y1, TICTACTOEDISPLAY_GREEN);//bottom left to top right
}

void ticTacToeDisplay_drawO(uint8_t row, uint8_t column)
{
    //position the y coordinate correctly depending on row number
    if(row == TICTACTOEDISPLAY_ROW_TOP)//top row
    {
        row = TICTACTOEDISPLAY_ONE_SIXTH_HEIGHT;//middle of O is between rows
    }
    else if(row == TICTACTOEDISPLAY_ROW_MIDDLE)//middle row
    {
        row = TICTACTOEDISPLAY_HALF_HEIGHT;//middle of O is between rows
    }
    else if(row == TICTACTOEDISPLAY_ROW_BOTTOM)//bottom row
    {
        row = TICTACTOEDISPLAY_FIVE_SIXTH_HEIGHT;//middle of O is between rows
    }

    //position the x coordinate correctly depending on column number
    if(column == TICTACTOEDISPLAY_COLUMN_LEFT)//left column
    {
        column = TICTACTOEDISPLAY_ONE_SIXTH_WIDTH;//middle of O is between columns
    }
    else if(column == TICTACTOEDISPLAY_COLUMN_MIDDLE)//middle column
    {
        column = TICTACTOEDISPLAY_HALF_WIDTH;//middle of O is between columns
    }
    else if(column == TICTACTOEDISPLAY_COLUMN_RIGHT)//right column
    {
        display_drawCircle(TICTACTOEDISPLAY_FIVE_SIXTH_WIDTH, row, TICTACTOEDISPLAY_CIRCLE_RADIUS, TICTACTOEDISPLAY_GREEN);
        return;//in this case the column number was too big for uint8_t column to hold (267) so jut manually draw this one
    }

    display_drawCircle(column, row, TICTACTOEDISPLAY_CIRCLE_RADIUS, TICTACTOEDISPLAY_GREEN);//draw the O character
}

void ticTacToeDisplay_touchScreenComputeBoardRowColumn(uint8_t *row, uint8_t* column)
{
    int16_t x, y; //two variables used in getting location of touch
    uint8_t z; //returns pressure of touch
    display_getTouchedPoint(&x, &y, &z); // Returns the x-y coordinate point and the pressure (z).

    //Column 0
    if(x < TICTACTOEDISPLAY_ONE_THIRD_WIDTH)
    {
        *column = TICTACTOEDISPLAY_COLUMN_LEFT;//assign column pointer to 0
        if(y < TICTACTOEDISPLAY_ONE_THIRD_HEIGHT) //Row 0
        {
            *row = TICTACTOEDISPLAY_ROW_TOP;//assign row pointer to 0
        }
        else if(y < TICTACTOEDISPLAY_TWO_THIRD_HEIGHT && y >  TICTACTOEDISPLAY_ONE_THIRD_HEIGHT)//Row 1
        {
            *row = TICTACTOEDISPLAY_ROW_MIDDLE;//assign row pointer to 1
        }
        else if(y < TICTACTOEDISPLAY_PIXEL_HEIGHT && y >  TICTACTOEDISPLAY_TWO_THIRD_HEIGHT)//Row 2
        {
            *row = TICTACTOEDISPLAY_ROW_BOTTOM;//assign row pointer to 2
        }
    }

    //Column 1
    else if(x < TICTACTOEDISPLAY_TWO_THIRD_WIDTH && x > TICTACTOEDISPLAY_ONE_THIRD_WIDTH)
    {
        *column = TICTACTOEDISPLAY_COLUMN_MIDDLE;//assign column pointer to 1
        if(y < TICTACTOEDISPLAY_ONE_THIRD_HEIGHT)//Row 0
        {
            *row = TICTACTOEDISPLAY_ROW_TOP;//assign row pointer to 0
        }
        else if(y < TICTACTOEDISPLAY_TWO_THIRD_HEIGHT && y >  TICTACTOEDISPLAY_ONE_THIRD_HEIGHT)//Row 1
        {
            *row = TICTACTOEDISPLAY_ROW_MIDDLE;//assign row pointer to 1
        }
        else if(y < TICTACTOEDISPLAY_PIXEL_HEIGHT && y >  TICTACTOEDISPLAY_TWO_THIRD_HEIGHT)//Row 2
        {
            *row = TICTACTOEDISPLAY_ROW_BOTTOM;//assign row pointer to 2
        }
    }

    //Column 2
    else if(x < TICTACTOEDISPLAY_PIXEL_WIDTH && x > TICTACTOEDISPLAY_TWO_THIRD_WIDTH)
    {
        *column = TICTACTOEDISPLAY_COLUMN_RIGHT;//assign column pointer to 2
        if(y < TICTACTOEDISPLAY_ONE_THIRD_HEIGHT)//Row 0
        {
            *row = TICTACTOEDISPLAY_ROW_TOP;//assign row pointer to 0
        }
        else if(y < TICTACTOEDISPLAY_TWO_THIRD_HEIGHT && y >  TICTACTOEDISPLAY_ONE_THIRD_HEIGHT)//Row 1
        {
            *row = TICTACTOEDISPLAY_ROW_MIDDLE;//assign row pointer to 1
        }
        else if(y < TICTACTOEDISPLAY_PIXEL_HEIGHT && y >  TICTACTOEDISPLAY_TWO_THIRD_HEIGHT)//Row 2
        {
            *row = TICTACTOEDISPLAY_ROW_BOTTOM;//assign row pointer to 2
        }
    }
}

void ticTacToeDisplay_runTest()
{
    while(1) //until button 1 is pressed
    {
        while(buttons_read() != (TICTACTOEDISPLAY_BTN0_ON))//until button 0 is pressed
        {
            if(buttons_read() == (TICTACTOEDISPLAY_BTN1_ON))//button has been pressed
            {
                display_setTextSize(TICTACTOEDISPLAY_TEXT_SIZE);  // this sets the text size
                display_setCursor(TICTACTOEDISPLAY_HALF_WIDTH-TICTACTOEDISPLAY_ONE_THIRD_WIDTH, //position x coordinate of cursor
                        TICTACTOEDISPLAY_HALF_HEIGHT - TICTACTOEDISPLAY_ONE_SIXTH_HEIGHT);//position y coordinate of cursor
                display_println("Game Over!");//print to the lcd
                return;//return out of both loops immediately
            }

            if(display_isTouched())
            {
                display_clearOldTouchData(); // Throws away all previous touch data.
                uint8_t row, column;
                ticTacToeDisplay_touchScreenComputeBoardRowColumn(&row, &column);//compute location of square
                if(switches_read() == TICTACTOEDISPLAY_SWITCH0_ON)//SW0 is up
                {
                    ticTacToeDisplay_drawO(row, column);//draw O character
                }
                if(switches_read() == TICTACTOEDISPLAY_SWITCH0_OFF)//SW0 is down
                {
                    ticTacToeDisplay_drawX(row, column);//draw X character
                }
            }
        }
        ticTacToeDisplay_init();//clear the screen
    }
}

void ticTacToeDisplay_drawBoardLines()
{
    //these draw the two vertical lines
    display_drawLine(TICTACTOEDISPLAY_ONE_THIRD_WIDTH, 0, TICTACTOEDISPLAY_ONE_THIRD_WIDTH, TICTACTOEDISPLAY_PIXEL_HEIGHT, TICTACTOEDISPLAY_GREEN);//leftmost
    display_drawLine(TICTACTOEDISPLAY_TWO_THIRD_WIDTH, 0, TICTACTOEDISPLAY_TWO_THIRD_WIDTH, TICTACTOEDISPLAY_PIXEL_HEIGHT, TICTACTOEDISPLAY_GREEN);//rightmost

    //these draw the two horizontal lines
    display_drawLine(0, TICTACTOEDISPLAY_ONE_THIRD_HEIGHT, TICTACTOEDISPLAY_PIXEL_WIDTH, TICTACTOEDISPLAY_ONE_THIRD_HEIGHT, TICTACTOEDISPLAY_GREEN);//topmost
    display_drawLine(0, TICTACTOEDISPLAY_TWO_THIRD_HEIGHT, TICTACTOEDISPLAY_PIXEL_WIDTH, TICTACTOEDISPLAY_TWO_THIRD_HEIGHT, TICTACTOEDISPLAY_GREEN);//bottommost
}

void ticTacToeDisplay_eraseBoardLines()
{
    //these draw the two vertical lines
    display_drawLine(TICTACTOEDISPLAY_ONE_THIRD_WIDTH, 0, TICTACTOEDISPLAY_ONE_THIRD_WIDTH, TICTACTOEDISPLAY_PIXEL_HEIGHT, TICTACTOEDISPLAY_BLACK);//leftmost
    display_drawLine(TICTACTOEDISPLAY_TWO_THIRD_WIDTH, 0, TICTACTOEDISPLAY_TWO_THIRD_WIDTH, TICTACTOEDISPLAY_PIXEL_HEIGHT, TICTACTOEDISPLAY_BLACK);//rightmost

    //these draw the two horizontal lines
    display_drawLine(0, TICTACTOEDISPLAY_ONE_THIRD_HEIGHT, TICTACTOEDISPLAY_PIXEL_WIDTH, TICTACTOEDISPLAY_ONE_THIRD_HEIGHT, TICTACTOEDISPLAY_BLACK);//topmost
    display_drawLine(0, TICTACTOEDISPLAY_TWO_THIRD_HEIGHT, TICTACTOEDISPLAY_PIXEL_WIDTH, TICTACTOEDISPLAY_TWO_THIRD_HEIGHT, TICTACTOEDISPLAY_BLACK);//bottommost
}

void ticTacToeDisplay_eraseX(uint8_t row, uint8_t column)
{
    uint16_t x1 = 0;
    uint16_t x2 = 0;
    uint16_t y1 = 0;
    uint16_t y2 = 0;

    //position the y coordinate correctly depending on row number
    if(row == TICTACTOEDISPLAY_ROW_TOP)//top row
    {
        y1 = TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET;//upper bound of X character
        y2 = TICTACTOEDISPLAY_ONE_THIRD_HEIGHT - TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET;//lower bound of X character
    }
    else if(row == TICTACTOEDISPLAY_ROW_MIDDLE)//middle row
    {
        y1 = TICTACTOEDISPLAY_ONE_THIRD_HEIGHT + TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET;//upper bound of X character
        y2 = TICTACTOEDISPLAY_TWO_THIRD_HEIGHT - TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET;//lower bound of X character
    }
    else if(row == TICTACTOEDISPLAY_ROW_BOTTOM)//bottom row
    {
        y1 = TICTACTOEDISPLAY_TWO_THIRD_HEIGHT + TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET;//upper bound of X character
        y2 = TICTACTOEDISPLAY_PIXEL_HEIGHT - TICTACTOEDISPLAY_X_CHAR_TOP_OFFSET;//lower bound of X character
    }

    //position the x coordinate correctly depending on column number
    if(column == TICTACTOEDISPLAY_COLUMN_LEFT)//left column
    {
        x1 = TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET;//left bound of X character
        x2 = TICTACTOEDISPLAY_ONE_THIRD_WIDTH - TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET;//right bound of X character
    }
    else if(column == TICTACTOEDISPLAY_COLUMN_MIDDLE)//middle column
    {
        x1 = TICTACTOEDISPLAY_ONE_THIRD_WIDTH + TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET;//left bound of X character
        x2 = TICTACTOEDISPLAY_TWO_THIRD_WIDTH - TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET;//right bound of X character
    }
    else if(column == TICTACTOEDISPLAY_COLUMN_RIGHT)//right column
    {
        x1 = TICTACTOEDISPLAY_TWO_THIRD_WIDTH + TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET;//left bound of X character
        x2 = TICTACTOEDISPLAY_PIXEL_WIDTH - TICTACTOEDISPLAY_X_CHAR_SIDE_OFFSET;//right bound of X character
    }

    display_drawLine(x1, y1, x2, y2, TICTACTOEDISPLAY_BLACK);//top left to bottom right
    display_drawLine(x1, y2, x2, y1, TICTACTOEDISPLAY_BLACK);//bottom left to top right
}

void ticTacToeDisplay_eraseO(uint8_t row, uint8_t column)
{
    //position the y coordinate correctly depending on row number
    if(row == TICTACTOEDISPLAY_ROW_TOP)//top row
    {
        row = TICTACTOEDISPLAY_ONE_SIXTH_HEIGHT;//middle of O is between rows
    }
    else if(row == TICTACTOEDISPLAY_ROW_MIDDLE)//middle row
    {
        row = TICTACTOEDISPLAY_HALF_HEIGHT;//middle of O is between rows
    }
    else if(row == TICTACTOEDISPLAY_ROW_BOTTOM)//bottom row
    {
        row = TICTACTOEDISPLAY_FIVE_SIXTH_HEIGHT;//middle of O is between rows
    }

    //position the x coordinate correctly depending on column number
    if(column == TICTACTOEDISPLAY_COLUMN_LEFT)//left column
    {
        column = TICTACTOEDISPLAY_ONE_SIXTH_WIDTH;//middle of O is between columns
    }
    else if(column == TICTACTOEDISPLAY_COLUMN_MIDDLE)//middle column
    {
        column = TICTACTOEDISPLAY_HALF_WIDTH;//middle of O is between columns
    }
    else if(column == TICTACTOEDISPLAY_COLUMN_RIGHT)//right column
    {
        display_drawCircle(TICTACTOEDISPLAY_FIVE_SIXTH_WIDTH, row, TICTACTOEDISPLAY_CIRCLE_RADIUS, TICTACTOEDISPLAY_BLACK);
        return;//in this case the column number was too big for uint8_t column to hold (267) so jut manually draw this one
    }

    display_drawCircle(column, row, TICTACTOEDISPLAY_CIRCLE_RADIUS, TICTACTOEDISPLAY_BLACK);//draw the O character
}


