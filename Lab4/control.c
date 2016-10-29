/*
 * control.c
 *
 *  Created on: Oct 5, 2015
 *      Author: spence13
 */




#include "clockControl.h"
#include "supportFiles/display.h"
#include <stdint.h>//This allows for use of int32 and other types in both the .h and .c files
#include <stdio.h>
#include <inttypes.h>
#include "supportFiles/utils.h"
#include "clockDisplay.h"
#include "stdbool.h"

#define CLCOKCONTROL_EXPIRED_VALUE 50

int adTimer = 0;
int autoTimer = 0;
int rateTimer = 0;
int secTimer = 0;
bool touched_yet = false;


enum CLOCKCONTROL_STATES {init_st, waiting_for_touch_st,
    ad_timer_running_st,
    auto_timer_running_st,
    rate_timer_running_st,
    rate_timer_expired_st,
    sec_increment_st} CLOCK_STATE;

void clockControl_tick(){
    switch(CLOCK_STATE){
    case init_st:
        CLOCK_STATE = waiting_for_touch_st;
       break;
    case waiting_for_touch_st:
        if(display_isTouched()){
            touched_yet = true;
            display_clearOldTouchData();
            CLOCK_STATE = ad_timer_running_st;
            break;

        }
        else if(!display_isTouched() && touched_yet){
            CLOCK_STATE = sec_increment_st;
            break;

        }
        else if(!touched_yet){
            touched_yet = false;
            CLOCK_STATE = waiting_for_touch_st;
            break;

        }
        else{
            CLOCK_STATE = waiting_for_touch_st;
            break;

        }
        break;
    case sec_increment_st:
        if(!display_isTouched() && secTimer == 10 && touched_yet){
            clockDisplay_advanceTimeOneSecond();
            secTimer = 0;
            break;

        }
        else if(display_isTouched()){
            CLOCK_STATE = waiting_for_touch_st;
            break;

        }
        else{
            CLOCK_STATE = sec_increment_st;
            break;

        }
        break;
    case ad_timer_running_st:
        if(!display_isTouched() && adTimer == 0){
            clockDisplay_performIncDec();
            CLOCK_STATE = waiting_for_touch_st;
            break;


        }
        else if(display_isTouched() && adTimer == 1){
            CLOCK_STATE = auto_timer_running_st;
            break;

        }
        else{
            CLOCK_STATE = ad_timer_running_st;
            break;


        }
        break;
    case auto_timer_running_st:
        if(!display_isTouched()){
            clockDisplay_performIncDec();
            CLOCK_STATE = waiting_for_touch_st;
            break;

        }
        else if(display_isTouched() && autoTimer == 4){
            clockDisplay_performIncDec();
            CLOCK_STATE = rate_timer_running_st;
            break;

        }
        else{
            CLOCK_STATE = auto_timer_running_st;
            break;


        }
        break;
    case rate_timer_running_st:
        if(!display_isTouched()){
            CLOCK_STATE = waiting_for_touch_st;
            break;


        }
        else if(display_isTouched() && rateTimer == 1){
            CLOCK_STATE = rate_timer_expired_st;
            break;


        }
        else{
            CLOCK_STATE = rate_timer_running_st;
            break;


        }
        break;
    case rate_timer_expired_st:
        if(display_isTouched()){
            clockDisplay_performIncDec();
            CLOCK_STATE = rate_timer_running_st;
            break;

        }
        else if(!display_isTouched()){
            CLOCK_STATE = waiting_for_touch_st;
            break;

        }
        else{
            CLOCK_STATE = rate_timer_expired_st;
            break;

        }
        break;
    default:
        CLOCK_STATE = init_st;
        break;

    }
    switch(CLOCK_STATE){
    case waiting_for_touch_st:
        adTimer = 0;
        autoTimer = 0;
        rateTimer = 0;
        break;
    case ad_timer_running_st:
//        touched_yet = 1;
        adTimer ++;
        break;
    case auto_timer_running_st:
        autoTimer ++;
        break;
    case rate_timer_running_st:
        rateTimer++;
        break;
    case rate_timer_expired_st:
        rateTimer = 0;
        break;
    case sec_increment_st:
        secTimer++;
        break;
    default:
        break;

    }



}

