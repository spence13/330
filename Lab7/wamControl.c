/*
 * wamControl.c
 *
 *  Created on: Nov 23, 2015
 *      Author: spence13
 */

#include "wamControl.h"
#include "wamDisplay.h"

uint32_t ADC_timer = 0;//initialize acd timer to zero
uint32_t rand_num_limit = WAMCONTROL_RAND_NUM_LIMIT;//create variable that tracks upper limit of random numbers
uint16_t max_misses = 0;//initialize max number of misses to zero
uint16_t max_activeMoles = 1;//initialize max number of active moles to zero
uint32_t ms_PerTick = 0;//initialize variable to zero

//create the control states for the SM
enum Control_States
{
    waiting_for_touch_st,//waiting for touch
    ADC_settle_time_st,//wait for adc to settle
    send_coordinates_st,//used to call whack mole function
}
currentState = waiting_for_touch_st;

// Call this before using any wamControl_ functions.
void wamControl_init()
{
    max_activeMoles = WAMCONTROL_MAX_MOLE;//reset the max active moles to 1
    rand_num_limit = WAMCONTROL_RAND_NUM_LIMIT;//reset the random number limit to 10
    ADC_timer = 0;//reset the adc timer to zero
}

// Call this to set how much time is consumed by each tick of the controlling state machine.
// This information makes it possible to set the awake and sleep time of moles in ms, not ticks.
void wamControl_setMsPerTick(uint16_t msPerTick)
{
    ms_PerTick = msPerTick;//set the milliseconds per tick to whatever value to pass in
}

// This returns the time consumed by each tick of the controlling state machine.
uint16_t wamControl_getMsPerTick()
{
    return ms_PerTick;// access the milliseconds per tick from other files
}

// Standard tick function.
void wamControl_tick()
{
    switch(currentState)//actions-----------------------------------------
    {
    case waiting_for_touch_st:
        ADC_timer = 0;//reset the adc timer to zero every time you loop
        wamDisplay_updateAllMoleTickCounts();//update all the tick counts
        if(wamDisplay_getActiveMoleCount() < wamControl_getMaxActiveMoles())//check to see if you can activate one more mole
        {
            wamDisplay_activateRandomMole();//call activate mole function to get another mole
        }
        break;

    case ADC_settle_time_st:
        display_clearOldTouchData();//clear old touch data immediately after touch
        ADC_timer++;//increment adc timer by one
        break;

    case send_coordinates_st:
        int16_t x, y; //two variables used in getting location of touch
        uint8_t z; //returns pressure of touch
        display_getTouchedPoint(&x, &y, &z); // Returns the x-y coordinate point and the pressure (z).
        wamDisplay_point_t coordinate;//create a variable of this type to hold touch coordinates
        coordinate.x = x;//set variable equal to touch coordinate x
        coordinate.y = y;//set variable equal to touch coordinate y
        wamDisplay_whackMole(&coordinate);//send the touch coordinates to the wack mole function
        break;

    default:
        currentState = waiting_for_touch_st;//set the default state to waiting_for_touch_st
        break;
    }

    switch(currentState)//transitions---------------------------------------------------
    {
    case waiting_for_touch_st:
        if(display_isTouched() == true)//check to see if display was touched
        {
            currentState = ADC_settle_time_st;//go to the waiting for adc to settle state
        }
        break;

    case ADC_settle_time_st:
        if(ADC_timer == WAMCONTROL_TIMER_EXPIREDVALUE)//if you have waited for one tick for adc to settle
        {
            currentState =  send_coordinates_st;//transition to send coordinates state
        }
        break;

    case send_coordinates_st:
        currentState = waiting_for_touch_st;//transition to waiting for touch state
        break;

    default:
        currentState = waiting_for_touch_st;//set the default state to waiting_for_touch_st
        break;
    }
}

// Returns a random value that indicates how long the mole should sleep before awaking.
wamDisplay_moleTickCount_t wamControl_getRandomMoleAsleepInterval()
{
    return (rand() % WAMCONTROL_RAND_NUM_TWENTYONE) + rand_num_limit;//.5 to 1.5 assuming a tick period of 50ms
}

// Returns a random value that indicates how long the mole should stay awake before going dormant.
wamDisplay_moleTickCount_t wamControl_getRandomMoleAwakeInterval()
{
    return (rand() % WAMCONTROL_RAND_NUM_TWENTYONE) + rand_num_limit;//.5 to 1.5 assuming a tick period of 50ms
}

// Set the maximum number of active moles.
void wamControl_setMaxActiveMoles(uint16_t count)
{
    max_activeMoles = count;//set the max number of active moles equal to what you pass in
}

// Get the current allowable count of active moles.
uint16_t wamControl_getMaxActiveMoles()
{
    return max_activeMoles;//access the max number of active moles
}

// Set the seed for the random-number generator.
void wamControl_setRandomSeed(uint32_t seed)
{
    srand(seed);//generate a random seed to initialize srand function
}

// Set the maximum number of misses until the game is over.
void wamControl_setMaxMissCount(uint16_t missCount)
{
    max_misses = missCount;//set the max number of misses to what you pass in
}

//decrement the amount of time moles can be awake
void wamControl_decrementRandNumLimit()
{
    rand_num_limit--;//decrement random number limit to make game harder
}

// Use this predicate to see if the game is finished.
bool wamControl_isGameOver()
{
    if(wamDisplay_getMissScore() >= max_misses)//if the number of misses equals the max number of allows misses
    {
        return true;//identifies the game is over
    }
    else
    {
        return false;//identifies the game is not over
    }
}
