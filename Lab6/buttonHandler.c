/*
 * buttonHandler.c
 *
 *  Created on: Oct 31, 2015
 *      Author: spence13
 */


#include "buttonHandler.h"

bool buttonHandlerEnabled = true;//used to start and stop this SM, but set by functions called in other SMs
int16_t x;//used for compute touch coordinates
int16_t y;//used for compute touch coordinates
uint8_t z;//used for compute touch pressure
int8_t regionNo;//used to denote region of LCD that was touched
uint32_t adc_timer = 0;//used to set an appropriate wait time for ADC settle


// States for the controller state machine.
enum Button_States
{
    init_st,// Start here, stay in this state for just one tick.
    waiting_for_touch_st, // waiting for touch, clock is enabled and running.
    debounce_st,//used as a delay state to wait for ADC to settle
    hold_square_st,//keep the square drawn as long as button is touched
    final_st,//used to signal to other SMs that release has been detected
}
currentState = init_st;

void buttonHandler_tick()
{
    switch(currentState)// actions----------------------------------------------
    {
    case init_st:
        adc_timer = 0;//reset the timer to zero
        break;
    case waiting_for_touch_st:
        break;
    case debounce_st:
        adc_timer++;//increment debounce timer by one
        break;
    case hold_square_st:
        break;
    case final_st:
        break;
    }

    switch(currentState)// transitions-----------------------------------------------
    {
    case init_st:
        if(buttonHandlerEnabled == true)//if enable is set to true
        {
            currentState = waiting_for_touch_st;//wait for a touch
        }
        break;
    case waiting_for_touch_st:
        if(display_isTouched() == true)//if display is touched
        {
            currentState = debounce_st;//go to debounce state
        }
        break;

    case debounce_st:
        if(adc_timer == BUTTONHANDLER_ADC_EXPIRED_VALUE)//wait for the adc to settle
        {
            display_clearOldTouchData();//clears old touch data
            display_getTouchedPoint(&x, &y, &z);//get the touched coordinates
            regionNo = simonDisplay_computeRegionNumber(x, y);//compute the regionNo
            simonDisplay_drawSquare(regionNo, false);//draw the square in regionNo
            currentState = hold_square_st;//go to hold square state
        }
        break;

    case hold_square_st:
        if(display_isTouched() != true)//button is no longer being pressed
        {
            simonDisplay_drawSquare(regionNo, true);//erase the square
            simonDisplay_drawButton(regionNo);//keep the button
            currentState = final_st;// go to final state
        }
        break;

    case final_st:
        if(buttonHandlerEnabled == false)//if enable is set to false
        {
            currentState = init_st;//go back to init state
        }
        break;

    default:
        currentState = init_st;//default is to stay in init state
        break;
    }
}

uint8_t buttonHandler_getRegionNumber()
{
    return regionNo;//return the region number that was computed in the state machine
}

void buttonHandler_enable()
{
    buttonHandlerEnabled = true;//set the variable to true, variable used in SM
}

void buttonHandler_disable()
{
    buttonHandlerEnabled = false;//set the variable to false, variable used in SM
}

bool buttonHandler_releaseDetected()
{
    if (currentState == final_st)//if SM is in the final state
    {
        return true;//it means you have touched and released the button
    }
    else
    {
        return false;//otherwise there has not been a touch and release yet
    }
}




