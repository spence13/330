/*
 * flashSequence.c
 *
 *  Created on: Nov 4, 2015
 *      Author: spence13
 */

#include "flashSequence.h"

bool flashSequenceEnabled = true;//used to enable the SM
uint32_t delay_timer;//used in delay state
int16_t flashcounter;//used for compute touch coordinates

// States for the controller state machine.
enum Flash_States
{
    init_st,// Start here, stay in this state for just one tick.
    draw_square_st,//used to flash the squares
    delay_st,//to make sure the square is flashed for a reasonable time
    evalutate_st,//evaluate state
    final_st,//used to signal to other SMs that release has been detected
}
flashState = init_st;

// Standard tick function. One tick is one square flashed. One SM is entire sequence iteration length
void flashSequence_tick()
{
    switch(flashState)// actions----------------------------------------------
    {
    case init_st:
        delay_timer = 0;//reset delay timer
        flashcounter = 0;//reset counter at beginning of SM
        break;
    case draw_square_st:
        simonDisplay_drawSquare(globals_getSequenceValue(flashcounter), false);//draw square use array at index of counter to get regionNo
        break;
    case delay_st:
        delay_timer++;//increment timer within delay state
        break;
    case evalutate_st:
        delay_timer = 0;//reset the timer to zero every time you leave delay state
        flashcounter++;////increment counter every time you have drawn a square but wait until after draw AND erase so they have the same value
        break;
    case final_st:
        break;
    }

    switch(flashState)// transitions-----------------------------------------------
    {
    case init_st:
        if(flashSequenceEnabled == true)//if enable is set to true
        {
            flashState = draw_square_st;//wait for a touch
        }
        break;

    case draw_square_st:
        flashState = delay_st;//automatically go to the delay state from drawing squares
        break;

    case delay_st:
        if(delay_timer == FLASHSEQUENCE_DELAY_EXPIRED_VALUE)//to make sure the square is flashed for a reasonable time
        {
            simonDisplay_drawSquare(globals_getSequenceValue(flashcounter), true);//erase square use array at index of counter to get regionNo
            flashState = evalutate_st;//go to the evaluate state
        }
        else
        {
            flashState = delay_st;//go to the delay state
        }
        break;

    case evalutate_st:
        if(flashcounter == globals_getSequenceIterationLength())//finished flashing the sequence
        {
            flashState = final_st;//transition to the final state
        }
        else
        {
            flashState = draw_square_st;//if sequence not finished, draw one more square
        }
        break;

    case final_st:
        if(flashSequenceEnabled == false)//if enable is set to false
        {
            flashState = init_st;//go back to init state
        }
        break;

    default:
        flashState = init_st;//default is to stay in init state
        break;
    }
}

// Turns on the state machine. Part of the interlock.
void flashSequence_enable()
{
    flashSequenceEnabled = true;//enable the flash SM
}

// Turns off the state machine. Part of the interlock.
void flashSequence_disable()
{
    flashSequenceEnabled = false;//disable the flash SM
}

// Other state machines can call this to determine if this state machine is finished.
bool flashSequence_completed()
{
    if (flashState == final_st)//if SM is in the final state
    {
        return true;//it means you have touched and released the button
    }
    else
    {
        return false;//otherwise there has not been a touch and release yet
    }
}



