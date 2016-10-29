/*
 * simonDisplay.c
 *
 *  Created on: Oct 31, 2015
 *      Author: spence13
 */
#include "simonDisplay.h"


int8_t simonDisplay_computeRegionNumber(int16_t x, int16_t y)
{
    //left half
    if(x > 0 && x < SIMON_DISPLAY_HALF_WIDTH)
    {
        //top half
        if(y > 0 && y < SIMON_DISPLAY_HALF_HEIGHT)
        {
            return 0;//region 0
        }
        //bottom half
        if(y > SIMON_DISPLAY_HALF_HEIGHT && y < SIMON_DISPLAY_PIXEL_HEIGHT)
        {
            return 2;//region 1
        }
    }

    //right half
    else if(x > SIMON_DISPLAY_HALF_WIDTH && x < SIMON_DISPLAY_PIXEL_WIDTH)
    {
        //top half
        if(y > 0 && y < SIMON_DISPLAY_HALF_HEIGHT)
        {
            return 1;//region 2
        }
        //bottom half
        if(y > SIMON_DISPLAY_HALF_HEIGHT && y < SIMON_DISPLAY_PIXEL_HEIGHT)
        {
            return 3;//region 3
        }
    }
}

// Draws a colored "button" that the user can touch.
// The colored button is centered in the region but does not fill the region.
void simonDisplay_drawButton(uint8_t regionNumber)
{
    if(regionNumber == 0)//top left region
    {
        //draw red button
        display_fillRect(SIMON_DISPLAY_BTN_OFFSET_X, SIMON_DISPLAY_BTN_OFFSET_Y, SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, SIMON_DISPLAY_RED);
    }
    else if(regionNumber == 1)//top right region
    {
        //draw yellow button
        display_fillRect(SIMON_DISPLAY_HALF_WIDTH + SIMON_DISPLAY_BTN_OFFSET_X, SIMON_DISPLAY_BTN_OFFSET_Y, SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, SIMON_DISPLAY_YELLOW);
    }
    else if(regionNumber == 2)//bottom left region
    {
        //draw blue button
        display_fillRect(SIMON_DISPLAY_BTN_OFFSET_X, SIMON_DISPLAY_HALF_HEIGHT + SIMON_DISPLAY_BTN_OFFSET_Y, SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, SIMON_DISPLAY_BLUE);
    }
    else if(regionNumber == 3)//bottom right region
    {
        //draw green button
        display_fillRect(SIMON_DISPLAY_HALF_WIDTH + SIMON_DISPLAY_BTN_OFFSET_X, SIMON_DISPLAY_HALF_HEIGHT + SIMON_DISPLAY_BTN_OFFSET_Y, SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, SIMON_DISPLAY_GREEN);
    }
}

// Convenience function that draws all of the buttons.
void simonDisplay_drawAllButtons()
{
    //top left red button
    display_fillRect(SIMON_DISPLAY_BTN_OFFSET_X, SIMON_DISPLAY_BTN_OFFSET_Y, SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, SIMON_DISPLAY_RED);
    //top right yellow button
    display_fillRect(SIMON_DISPLAY_HALF_WIDTH + SIMON_DISPLAY_BTN_OFFSET_X, SIMON_DISPLAY_BTN_OFFSET_Y, SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, SIMON_DISPLAY_YELLOW);
    //bottom left blue button
    display_fillRect(SIMON_DISPLAY_BTN_OFFSET_X, SIMON_DISPLAY_HALF_HEIGHT + SIMON_DISPLAY_BTN_OFFSET_Y, SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, SIMON_DISPLAY_BLUE);
    //bottom right green button
    display_fillRect(SIMON_DISPLAY_HALF_WIDTH + SIMON_DISPLAY_BTN_OFFSET_X, SIMON_DISPLAY_HALF_HEIGHT + SIMON_DISPLAY_BTN_OFFSET_Y, SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, SIMON_DISPLAY_GREEN);
}

// Draws a bigger square that completely fills the region.
// If the erase argument is true, it draws the square as black background to "erase" it.
void simonDisplay_drawSquare(uint8_t regionNo, bool erase)
{
    //drawing the square
    if(erase == false)
    {
        if(regionNo == 0)
        {//draw top left red square
            display_fillRect(0, 0, SIMON_DISPLAY_HALF_WIDTH, SIMON_DISPLAY_HALF_HEIGHT, SIMON_DISPLAY_RED);
        }
        else if(regionNo == 1)
        {//draw top right yellow square
            display_fillRect(SIMON_DISPLAY_HALF_WIDTH, 0, SIMON_DISPLAY_HALF_WIDTH, SIMON_DISPLAY_HALF_HEIGHT, SIMON_DISPLAY_YELLOW);
        }
        else if(regionNo == 2)
        {//draw bottom left blue square
            display_fillRect(0, SIMON_DISPLAY_HALF_HEIGHT, SIMON_DISPLAY_HALF_WIDTH, SIMON_DISPLAY_HALF_HEIGHT, SIMON_DISPLAY_BLUE);
        }
        else if(regionNo == 3)
        {//draw bottom right green square
            display_fillRect(SIMON_DISPLAY_HALF_WIDTH, SIMON_DISPLAY_HALF_HEIGHT, SIMON_DISPLAY_HALF_WIDTH, SIMON_DISPLAY_HALF_HEIGHT, SIMON_DISPLAY_GREEN);
        }
    }

    //erasing the square
    if(erase == true)
    {
        if(regionNo == 0)
        {//black out the top left square
            display_fillRect(0, 0, SIMON_DISPLAY_HALF_WIDTH, SIMON_DISPLAY_HALF_HEIGHT, SIMON_DISPLAY_BLACK);
        }
        else if(regionNo == 1)
        {//black out the top right square
            display_fillRect(SIMON_DISPLAY_HALF_WIDTH, 0, SIMON_DISPLAY_HALF_WIDTH, SIMON_DISPLAY_HALF_HEIGHT, SIMON_DISPLAY_BLACK);
        }
        else if(regionNo == 2)
        {//black out the bottom left square
            display_fillRect(0, SIMON_DISPLAY_HALF_HEIGHT, SIMON_DISPLAY_HALF_WIDTH, SIMON_DISPLAY_HALF_HEIGHT, SIMON_DISPLAY_BLACK);
        }
        else if(regionNo == 3)
        {//black out the bottom right square
            display_fillRect(SIMON_DISPLAY_HALF_WIDTH, SIMON_DISPLAY_HALF_HEIGHT, SIMON_DISPLAY_HALF_WIDTH, SIMON_DISPLAY_HALF_HEIGHT, SIMON_DISPLAY_BLACK);
        }
    }
}

void simonDisplay_eraseAllButtons()
{
    //top left red button
    display_fillRect(SIMON_DISPLAY_BTN_OFFSET_X, SIMON_DISPLAY_BTN_OFFSET_Y, SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, SIMON_DISPLAY_BLACK);
    //top right yellow button
    display_fillRect(SIMON_DISPLAY_HALF_WIDTH + SIMON_DISPLAY_BTN_OFFSET_X, SIMON_DISPLAY_BTN_OFFSET_Y, SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, SIMON_DISPLAY_BLACK);
    //bottom left blue button
    display_fillRect(SIMON_DISPLAY_BTN_OFFSET_X, SIMON_DISPLAY_HALF_HEIGHT + SIMON_DISPLAY_BTN_OFFSET_Y, SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, SIMON_DISPLAY_BLACK);
    //bottom right green button
    display_fillRect(SIMON_DISPLAY_HALF_WIDTH + SIMON_DISPLAY_BTN_OFFSET_X, SIMON_DISPLAY_HALF_HEIGHT + SIMON_DISPLAY_BTN_OFFSET_Y, SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, SIMON_DISPLAY_BLACK);
}



