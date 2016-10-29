/*
 * simonControl.c
 *
 *  Created on: Nov 16, 2015
 *      Author: spence13
 */


#include "simonControl.h"
#include <stdlib.h>

uint32_t verify_timer = 0;//create verify timer used to delay state transitions
uint32_t srandTimer = 0;//used to seed to srand() function
uint16_t iteration_Length = SIMONCONTROL_MIN_ITERATION_LENGTH;//create local iteration length to be passed to globals
uint16_t sequence_Length = SIMONCONTROL_MIN_SEQUENCE_LENGTH;//create local length to be passed to globals
uint8_t sequence[SIMONCONTROL_MAX_ARRAY];//create an local array to be passed to globals
uint8_t levelTimer = 0;//this keeps you in the state for a bit before restarting the game
char seq[SIMONCONTROL_MAX_ARRAY];//this is used to convert a number to a string so it can print

enum Control_States
{
    init_st,// Start here, stay in this state for just one tick.
    waiting_for_touch_st,//waiting for touch
    level_up_st,//in between next level and waiting states
    create_array_st,//after the waiting state, this one creates the array
    flash_sequence_st,//enable button handler
    verify_sequence_st,//see if touch matches
    next_level_st,//used to signal to other SMs that release has been detected
}
controlState = init_st;

void simonControl_tick()
{
    switch(controlState)//actions--------------------------------------------------------------
    {
    case init_st:
        display_setCursor(SIMONCONTROL_HALF_PIXEL_WIDTH, SIMONCONTROL_HALF_PIXEL_HEIGHT);//set cursor position
        display_setTextColor(SIMONCONTROL_GREEN);//Make the text green.
        display_println("touch to start");//print touch to start to the screen
        flashSequence_disable();//make sure you start everytime with flash SM disabled
        verifySequence_disable();//make sure you start every time with verify SM disabled
        buttonHandler_disable();//make sure you start everytime with buttonhandler SM disabled
        iteration_Length = SIMONCONTROL_MIN_ITERATION_LENGTH;//initialize iteration length every time you restart
        sequence_Length = SIMONCONTROL_MIN_SEQUENCE_LENGTH;//initialize length every time you restart
        verify_timer = 0;//initialize verify timer to zero
        break;

    case waiting_for_touch_st:
        srandTimer++;//increment this timer by one; to be used as seed for srand()
        globals_setSequenceIterationLength(SIMONCONTROL_MIN_ITERATION_LENGTH);//start the iteration length over again each time you start a new level
        break;

    case level_up_st:
        levelTimer++;//increment timer by one every time you hit this state
        break;

    case create_array_st:
        randomizeArray();//create a random array to be used with this function
        globals_setSequence(sequence, sequence_Length);//set sequence length and create global array
        break;

    case flash_sequence_st:
        flashSequence_enable();//enable the flash sequence SM
        break;

    case verify_sequence_st:
        verifySequence_enable();//enable the verify sequence SM
        break;

    case next_level_st:
        simonDisplay_eraseAllButtons();//erase all the buttons so you can show the text
        display_setCursor(SIMONCONTROL_HALF_PIXEL_WIDTH, SIMONCONTROL_HALF_PIXEL_HEIGHT);//set cursor position
        display_setTextColor(SIMONCONTROL_GREEN);//Make the text green.
        display_println("yay!");//print yay to the screen
        display_println("touch for a new level");//print this to the screen
        sequence_Length++;//reinitialize variable
        iteration_Length = SIMONCONTROL_MIN_ITERATION_LENGTH;//reinitialize variable
        break;
    }

    switch(controlState)//transitions--------------------------------------------
    {
    case init_st:
        controlState = waiting_for_touch_st;//automatically go to waiting state
        break;

    case waiting_for_touch_st:
        if(display_isTouched() == true)//wait until screen is touched
        {
            srand(srandTimer);//start srand() with random seed
            display_setCursor(SIMONCONTROL_HALF_PIXEL_WIDTH, SIMONCONTROL_HALF_PIXEL_HEIGHT);//set cursor position
            display_setTextColor(SIMONCONTROL_BLACK);//Make the text green.
            display_println("touch to start");//erase touch to start from the screen
            controlState = create_array_st;//go to flash state machine after touched
        }
        break;

    case level_up_st:
        if(display_isTouched() == true)//if user touches the screen it levels up
        {
            globals_setSequenceIterationLength(SIMONCONTROL_MIN_ITERATION_LENGTH);//start the iteration length over again each time you start a new level
            display_setCursor(SIMONCONTROL_HALF_PIXEL_WIDTH, SIMONCONTROL_HALF_PIXEL_HEIGHT);//set cursor position
            display_setTextColor(SIMONCONTROL_BLACK);//Make the text green.
            display_println("yay!");//erase yay if you just leveled up
            display_println("touch for a new level");//erase touch for new level if you just leveled up
            controlState = create_array_st;//go to the create array state
        }
        else if(levelTimer == SIMONCONTROL_LEVELTIMER_EXPIREDVALUE)//if user doesnt touch the screen the game restarts
        {
            globals_setSequenceIterationLength(SIMONCONTROL_MIN_ITERATION_LENGTH);//start the iteration length over again each time you start a new level
            display_setCursor(SIMONCONTROL_HALF_PIXEL_WIDTH, SIMONCONTROL_HALF_PIXEL_HEIGHT);//set cursor position
            display_setTextColor(SIMONCONTROL_BLACK);//Make the text green.
            display_println("yay!");//erase yay if you just leveled up
            display_println("touch for a new level");//erase touch for new level if you just leveled up
            controlState = init_st;//go to the init state
        }
        break;

    case create_array_st:
        controlState = flash_sequence_st;//go to flash state machine after touched
        break;

    case flash_sequence_st:
        if(flashSequence_completed() == true)//if youve completed the flashing sequence
        {
            flashSequence_disable();//disable the flash sequence SM as you leave
            simonDisplay_drawAllButtons();//draw all the buttons to the screen after youve flashed the sequence
            controlState = verify_sequence_st;//go to verify state once youre done flashing
        }
        else
        {
            controlState = flash_sequence_st;//default is to stay in flash state
        }
        break;

    case verify_sequence_st:
        if(verifySequence_isComplete() == true)//if youve completed the verify sequence
        {
            if(verifySequence_isTimeOutError() == true || verifySequence_isUserInputError() == true)//if there was an error in matching the sequence
            {
                verify_timer++;//increment verify timer by one to keep track of how long youre here
                simonDisplay_eraseAllButtons();//erase all the buttons from the screen to display oops retry
                display_setCursor(SIMONCONTROL_HALF_PIXEL_WIDTH, SIMONCONTROL_HALF_PIXEL_HEIGHT);//set cursor position
                display_setTextColor(SIMONCONTROL_GREEN);//Make the text green.
                display_print("Longest Sequence:");//print these words to the screen
                sprintf(seq, "%d",iteration_Length - 1);//print the display numbers to an array
                display_print(seq);//print the char array called time to the lcd display
                if(verify_timer == SIMONCONTROL_VERIFY_TIMER_EXPIREDVALUE)//wait here for a little bit so oops retry stays on the screen
                {
                    verify_timer = 0;//reset verify timer to zero
                    display_setCursor(SIMONCONTROL_HALF_PIXEL_WIDTH, SIMONCONTROL_HALF_PIXEL_HEIGHT);//set cursor position
                    display_setTextColor(SIMONCONTROL_BLACK);//Make the text black to erase it.
                    display_print("Longest Sequence:");//print these words to the screen
                    display_print(seq);//print the char array called time to the lcd display
                    verifySequence_disable();//disable the verify sequence SM as you leave
                    controlState = init_st;//don't increment iteration length
                }
                else
                {
                    controlState = verify_sequence_st;//default is to stay in verify state
                }
            }
            else if(globals_getSequenceIterationLength() == globals_getSequenceLength())//if youve completed the level and iteration length equals total sequence length
            {
                verifySequence_disable();//disable the verify sequence SM as you leave
                controlState = next_level_st;//go to level up state
            }
            else
            {
                verifySequence_disable();//disable the verify sequence SM as you leave
                iteration_Length++;//increase iteration length by one as you go back to flash sequence
                globals_setSequenceIterationLength(iteration_Length);//increment iteration length
                simonDisplay_eraseAllButtons();//erase all the buttons before you flash again
                controlState = flash_sequence_st;//go to flash state
            }
        }
        else
        {
            controlState = verify_sequence_st;//default is stay in verify state
        }
        break;

    case next_level_st:
        controlState = level_up_st;//go to waiting state if you completed the level
        break;

    default:
        controlState = init_st;//default is to stay in init state
        break;
    }
}

//creates an array with random numbers between 0-3
void randomizeArray()
{
    for(int i = 0; i < sequence_Length; i++)//go from 0 to however long the sequence length is
    {
        sequence[i] = rand()%4;//random number
    }
}



