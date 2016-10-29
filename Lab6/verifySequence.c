/*
 * verifySequence.c
 *
 *  Created on: Nov 6, 2015
 *      Author: spence13
 */

#include "verifySequence.h"

bool verifySequenceEnabled = true;//allows the state machine to start and stop
bool inputError = false;//indicated if user touched the wrong square
bool timeError = false;//used to indicate if user was too slow to touch
int16_t verifycounter;//used to keep track of sequence length
int32_t touch_timer;//used to delay touch state

enum Verify_States
{
    init_st,// Start here, stay in this state for just one tick.
    enable_buttons_st,//enable button handler
    check_st,//check to see if you've finished
    final_st,//used to signal to other SMs that release has been detected
}
verifyState = init_st;
// Standard tick function. one tick per touch. one SM per sequence iteration length
void verifySequence_tick()
{
    switch(verifyState)// actions----------------------------------------------
    {
    case init_st:
        verifycounter = 0;//reset every time you enter SM
        touch_timer = 0;//reset every time you enter SM
        inputError = false;//reset every time you enter SM
        timeError = false;//reset every time you enter SM
        break;

    case enable_buttons_st:
        buttonHandler_enable();//enable button handler
        touch_timer++;//increment timer every time you hit this state
        if(touch_timer == VERIFYSEQUENCE_TOUCH_TIMER_EXPIRED_VALUE)//spent too long in this state waiting for touch
        {
            timeError = true;//indicates user was too slow
        }
        break;

    case check_st:
        if(buttonHandler_getRegionNumber() != globals_getSequenceValue(verifycounter))//if the user touched the wrong button
        {
            inputError = true;//indicates user was incorrect
        }
        touch_timer = 0;//reset timer to zero before restarting
        verifycounter++;//increment counter every loop(button_handler is called) within the SM
        break;

    case final_st:
        break;
    }

    switch(verifyState)// transitions----------------------------------------------
    {
    case init_st:
        if(verifySequenceEnabled == true)//if enable is set to true
        {
            verifyState = enable_buttons_st;//transition to the enable button state
        }
        break;

    case enable_buttons_st:
        if(buttonHandler_releaseDetected() == true)//this means the user has finished one touch
        {
            buttonHandler_disable();//disable button handler immediately upon exit
            verifyState = check_st;//transition to the get touch state?????????????????????????????????????????????????
        }
        else if(timeError == true)//immediately exit SM if user was too slow
        {
            verifyState = final_st;//transition to the final state
        }
        break;

    case check_st:
        if(verifycounter == globals_getSequenceIterationLength() || inputError == true)//successfully finished OR user touched wrong square
        {
            verifyState = final_st;//transition to final state
        }
        else//if not quite done
        {
            verifyState = enable_buttons_st;//go back to enable buttons state
        }
        break;

    case final_st:
        if(verifySequenceEnabled == false)//if enable is set to true
        {
            verifyState = init_st;//restart SM
        }
        break;

    default:
        verifyState = init_st;//default is to stay in init state
        break;
    }
}

// State machine will run when enabled.
void verifySequence_enable()
{
    verifySequenceEnabled = true;//set global variable to true
}

// This is part of the interlock. You disable the state-machine and then enable it again.
void verifySequence_disable()
{
    verifySequenceEnabled = false;//set global variable to false
}

// Used to detect if there has been a time-out error.
bool verifySequence_isTimeOutError()
{
    return timeError;//return global bool which has been set to true or false in SM
}

// Used to detect if the user tapped the incorrect sequence.
bool verifySequence_isUserInputError()
{
    return inputError;//return global bool which has been set to true or false in SM
}

// Used to detect if the verifySequence state machine has finished verifying.
bool verifySequence_isComplete()
{
    if (verifyState == final_st)//if SM is in the final state
    {
        return true;//it means you have touched and released the button
    }
    else
    {
        return false;//otherwise there has not been a touch and release yet
    }
}



