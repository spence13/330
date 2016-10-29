/*
 * clockControl.c
 *
 *  Created on: Sep 26, 2015
 *      Author: spence13
 */

#include "clockControl.h"
#include "src/lab3/intervalTimer.h"


uint32_t adTimer = 0;//deals with waiting for ADC to settle
uint32_t autoTimer = 0;//deals with waiting .5 seconds before going to fast mode
uint32_t rateTimer = 0;//deals with waiting .1 seconds before incrementing display
uint32_t secTimer = 0;//deals with waiting 1 second before incrementing display
bool display_wasTouched;//sets a flag if the display was ever touched


// States for the controller state machine.
enum Timer_States
{
    init_st,// Start here, stay in this state for just one tick.
    waiting_for_touch_st, // waiting for touch, clock is enabled and running.
    ad_timer_running_st,// waiting for the touch-controller ADC to settle.
    auto_timer_running_st,// waiting for the auto-update delay to expire
    rate_timer_running_st, // waiting for the rate-timer to expire to know when to perform the auto inc/dec.
    rate_timer_expired_st,// when the rate-timer expires, perform the inc/dec function.
    keep_time_st // keep time like normal timer
}
currentState=init_st;

//this function will hold the state machines with their associated transitions and actions
void clockControl_tick()
{
     switch(currentState)// actions
    {
       case init_st:  // Initial transition
       break;

       case waiting_for_touch_st:
       //reset all timers;
       adTimer = 0;
       autoTimer = 0;
       rateTimer = 0;
       secTimer = 0;
       break;

       case ad_timer_running_st:
       adTimer++; //increase the adTimer by one
       break;

       case auto_timer_running_st:
       autoTimer++;//increase the autoTimer by one
       break;

       case rate_timer_running_st:
       rateTimer++;//increase the rateTimer by one
       break;

       case rate_timer_expired_st:
       rateTimer = 0;//reset the rateTimer so you can start recounting
       break;

       case keep_time_st:
       secTimer++;//increase the secTimer by one
       break;

       default:
       currentState = init_st; //default state is init
       break;
    }// actions


    switch(currentState)// Transitions
    {
        case init_st:  // Initial transition
        currentState = waiting_for_touch_st;    //automatically go to waiting state
        break;

        case waiting_for_touch_st:
        if (display_isTouched()) //checks to see if display was touched at all
        {
            display_wasTouched = true; //set a flag that the display was touched
            display_clearOldTouchData(); //clear the old data from lcd so it doesnt mess up new date
            currentState = ad_timer_running_st;  //go to ad timer state
            break;
        }
        else if(!display_isTouched() && display_wasTouched) //if the the dispaly was touched but not held
        {
            currentState = keep_time_st;  //go to keep time state
            break;
        }
        else if(!display_wasTouched) //if the display was never touched
        {
            display_wasTouched = false; //dont set the flag that the display was touched
            currentState = waiting_for_touch_st; //just stay in the waiting state
            break;
        }
        else
        {
            currentState = waiting_for_touch_st; //default stay in waiting state
            break;
        }

        case keep_time_st:
        if(!display_isTouched() && secTimer == CLOCK_CONTROL_SEC_EXPIRED_VALUE && display_wasTouched) //if display is no longer being held but was touched at some point and its been a second
        {
            clockDisplay_advanceTimeOneSecond(); //advance the second by one
            secTimer = 0; //reset secTimer which sees if a second has passed
            break;
        }
        else if(display_isTouched()) //if the display is touched again
        {
             currentState = waiting_for_touch_st;  //return to waiting state
             break;
        }
        else
        {
            currentState = keep_time_st; //default is to remain in keep time state
            break;
        }
        break;

        case ad_timer_running_st:
        if (display_isTouched() && adTimer == CLOCK_CONTROL_ADD_EXPIRED_VALUE) //if display is being held and 50ms has passed
        {
            currentState = auto_timer_running_st; //go to auto timer state
            break;
        }
        else if (!display_isTouched() && adTimer == CLOCK_CONTROL_ADD_EXPIRED_VALUE) //if display is no longer being held and 50ms has passed
        {
            clockDisplay_performIncDec(); //increment time by one
            currentState = waiting_for_touch_st;  //return to waiting state
            break;
        }
        else
        {
            currentState = ad_timer_running_st;//default state is to stay in ad timer state
            break;
        }
        break;

        case auto_timer_running_st:
        if (display_isTouched() && autoTimer == CLOCK_CONTROL_AUTO_EXPIRED_VALUE)//if display is being held and a half second has passed
        {
            clockDisplay_performIncDec();//increment to display by one
            currentState = rate_timer_running_st; //go to rate timer running state
            break;
        }
        else if (!display_isTouched())//if display is no longer being held
        {
            clockDisplay_performIncDec();//increment display by one
            currentState = waiting_for_touch_st;   //return to waiting state
            break;
        }
        else
        {
            currentState = auto_timer_running_st;//default is to remain in auto timer state
            break;
        }
        break;

        case rate_timer_running_st:
        if (!display_isTouched())//if display is no longer being held
        {
            currentState = waiting_for_touch_st; //return to waiting state
            break;
        }
        else if (display_isTouched() && rateTimer == CLOCK_CONTROL_RATE_EXPIRED_VALUE)//if display is being held and .1 seconds has passed
        {
            currentState = rate_timer_expired_st;   //go to rate timer expired state where display is increased
            break;
        }
        else
        {
            currentState = rate_timer_running_st;//default stay in rate timer running state
            break;
        }
        break;

        case rate_timer_expired_st:
        if (!display_isTouched())//if display is no longer being held
        {
            currentState = waiting_for_touch_st;   //go back to waiting state
            break;
        }
        else if (display_isTouched())//if display is still being held
        {
            clockDisplay_performIncDec();// increment display by one
            currentState = rate_timer_running_st;  //go back to rate time running state
            break;
        }
        else
        {
            currentState = rate_timer_expired_st;//default is to stay in rate timer expired state
            break;
        }
        break;

        default:
        currentState = init_st;//set the default state to init
        break;
    }// Transitions
}
