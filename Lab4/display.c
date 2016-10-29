/*
 * display.c
 *
 *  Created on: Oct 5, 2015
 *      Author: spence13
 */




#include "clockDisplay.h"
#include "supportFiles/display.h"
#include <stdint.h>//This allows for use of int32 and other types in both the .h and .c files
#include <stdio.h>
#include <inttypes.h>
#include "supportFiles/utils.h"

#define CLOCKDISPLAY_TEXT_SIZE 5

//#define DISPLAY_CHAR_WIDTH 6
//#define DISPLAY_CHAR_HEIGHT 8
//#define DISPLAY_BIN 2

#define CLOCKDISPLAY_CHARX_SIZE_HALF 6/2
#define CLOCKDISPLAY_CHARY_SIZE_HALF 8/2
#define CLOCKDISPLAY_TWO 2
#define CLOCKDISPLAY_THREE 3
#define CLCOKDISPLAY_TENS_MAX_SECMIN 5
#define CLCOKDISPLAY_ONES_MAX_SECMIN 9
#define CLOCKDISPLAY_REGION_0 0
#define CLOCKDISPLAY_REGION_1 1
#define CLOCKDISPLAY_REGION_2 2
#define CLOCKDISPLAY_REGION_3 3
#define CLOCKDISPLAY_REGION_4 4
#define CLOCKDISPLAY_REGION_5 5
#define CLOCKDISPLAY_TIME_LENGTH 8
#define CLOCKDISPLAY_HOURS_MAX 12
#define CLOCKDISPLAY_MINUTESSEC_MAX 59


int  hours = CLOCKDISPLAY_HOURS_MAX;//Not a #define because it will need editing to be put onto the touch screen
int  minutes = CLOCKDISPLAY_MINUTESSEC_MAX;
int  seconds = CLOCKDISPLAY_MINUTESSEC_MAX;

int16_t x_touched;
int16_t y_touched;
uint8_t z_touched;

char time[CLOCKDISPLAY_TIME_LENGTH];


//void display_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size)

int8_t clockDisplay_computeRegion(int16_t x, int16_t y) { // This function determines which of the 6 regions on the LCD screen are touched.
  if (x < 0 || y < 0)
    return -1;
  if (y > DISPLAY_HEIGHT/2){  // Must be region 0, 1 or 2
      if (x < DISPLAY_WIDTH/3)
          return CLOCKDISPLAY_REGION_0;
      else if((x < DISPLAY_WIDTH*.666)&&(x > DISPLAY_WIDTH/3)) {
          return CLOCKDISPLAY_REGION_1;
      }
      else {
          return CLOCKDISPLAY_REGION_2;
      }
  } else {               // must be regione 3, 4, or 4
      if (x < DISPLAY_WIDTH/3)
          return CLOCKDISPLAY_REGION_3;
      else if((x < DISPLAY_WIDTH*.666)&&(x > DISPLAY_WIDTH/3)) {
          return CLOCKDISPLAY_REGION_4;
      }
      else {
          return CLOCKDISPLAY_REGION_5;
      }
  }
}




void clockdisplay_draw_tens_hours(char x){//Change these to accept an int and convert it to a char to put into the function so that time can be changed

    display_drawChar(DISPLAY_WIDTH/DISPLAY_BIN -4*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,
            DISPLAY_HEIGHT/DISPLAY_BIN -CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,
            x,
            DISPLAY_GREEN,
            0,
            CLOCKDISPLAY_TEXT_SIZE);

}
void clockdisplay_draw_ones_hours(char x){

    display_drawChar(DISPLAY_WIDTH/DISPLAY_BIN -3*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,
            DISPLAY_HEIGHT/DISPLAY_BIN -CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,
            x,
            DISPLAY_GREEN,
            0,
            CLOCKDISPLAY_TEXT_SIZE);

}
void clockdisplay_draw_tens_minutes(char x){

    display_drawChar(DISPLAY_WIDTH/DISPLAY_BIN -1*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,
            DISPLAY_HEIGHT/DISPLAY_BIN -CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,
            x,
            DISPLAY_GREEN,
            0,
            CLOCKDISPLAY_TEXT_SIZE);

}
void clockdisplay_draw_ones_minutes(char x){

    display_drawChar(DISPLAY_WIDTH/DISPLAY_BIN +0*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,
            DISPLAY_HEIGHT/DISPLAY_BIN -CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,
            x,
            DISPLAY_GREEN,
            0,
            CLOCKDISPLAY_TEXT_SIZE);

}
void clockdisplay_draw_tens_seconds(char x){

    display_drawChar(DISPLAY_WIDTH/DISPLAY_BIN +2*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,
            DISPLAY_HEIGHT/DISPLAY_BIN -CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,
            x,
            DISPLAY_GREEN,
            0,
            CLOCKDISPLAY_TEXT_SIZE);

}
void clockdisplay_draw_ones_seconds(char x){

    display_drawChar(DISPLAY_WIDTH/DISPLAY_BIN +3*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,
            DISPLAY_HEIGHT/DISPLAY_BIN -CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,
            x,
            DISPLAY_GREEN,
            0,
            CLOCKDISPLAY_TEXT_SIZE);

}
void clockdisplay_draw_left_colon(char x){
    display_drawChar(DISPLAY_WIDTH/DISPLAY_BIN -2*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,
                DISPLAY_HEIGHT/DISPLAY_BIN -CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,
                x,
                DISPLAY_GREEN,
                0,
                CLOCKDISPLAY_TEXT_SIZE);

}
void clockdisplay_draw_right_colon(char x){
    display_drawChar(DISPLAY_WIDTH/DISPLAY_BIN +1*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,
                DISPLAY_HEIGHT/DISPLAY_BIN -CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,
                x,
                DISPLAY_GREEN,
                0,
                CLOCKDISPLAY_TEXT_SIZE);

}
void clockdisplay_draw_traingles(){//I created this function so that changing by triangles requires that I only change a #define instead of the entire set of verticies

    //*****leftmost top triangle

    display_fillTriangle(DISPLAY_WIDTH/DISPLAY_BIN -4*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH ,//Left x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN -1.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF, //left y vertex
            DISPLAY_WIDTH/DISPLAY_BIN - 2*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,             //Right x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN -1.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF, //right y vertex
            DISPLAY_WIDTH/DISPLAY_BIN - 3*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,             //top x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN -3.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF, //top y vertex
            DISPLAY_GREEN);

    //*****middle top triangle
    display_fillTriangle(DISPLAY_WIDTH/DISPLAY_BIN -1*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH ,//Left x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN -1.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,                //left y vertex
            DISPLAY_WIDTH/DISPLAY_BIN + 1*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,             //Right x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN -1.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,            //right y vertex
            DISPLAY_WIDTH/DISPLAY_BIN - 0*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,    //top x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN -3.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,           //top y vertex
            DISPLAY_GREEN);


    //****** rightmost top triangle
    display_fillTriangle(DISPLAY_WIDTH/DISPLAY_BIN +4*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH ,//Left x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN -1.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,                //left y vertex
            DISPLAY_WIDTH/DISPLAY_BIN + 2*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,             //Right x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN -1.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,            //right y vertex
            DISPLAY_WIDTH/DISPLAY_BIN + 3*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,    //top x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN -3.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,           //top y vertex
            DISPLAY_GREEN);


//*********** leftmost bottom triangle
    display_fillTriangle(DISPLAY_WIDTH/DISPLAY_BIN -4*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH ,//Left x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN +1.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,                //left y vertex
            DISPLAY_WIDTH/DISPLAY_BIN - 2*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,             //Right x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN +1.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,            //right y vertex
            DISPLAY_WIDTH/DISPLAY_BIN - 3*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,    //top x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN +3.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,           //top y vertex
            DISPLAY_GREEN);

    //******** middle bottom triangle
    display_fillTriangle(DISPLAY_WIDTH/DISPLAY_BIN -1*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH ,//Left x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN +1.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,                //left y vertex
            DISPLAY_WIDTH/DISPLAY_BIN + 1*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,             //Right x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN +1.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,            //right y vertex
            DISPLAY_WIDTH/DISPLAY_BIN - 0*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,    //top x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN +3.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,           //top y vertex
            DISPLAY_GREEN);

    //******** rightmost bottom triangle
    display_fillTriangle(DISPLAY_WIDTH/DISPLAY_BIN +4*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH ,//Left x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN +1.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,                //left y vertex
            DISPLAY_WIDTH/DISPLAY_BIN + 2*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,             //Right x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN +1.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,            //right y vertex
            DISPLAY_WIDTH/DISPLAY_BIN + 3*CLOCKDISPLAY_TEXT_SIZE*DISPLAY_CHAR_WIDTH,    //top x vertex
            DISPLAY_HEIGHT/DISPLAY_BIN +3.5*CLOCKDISPLAY_TEXT_SIZE*CLOCKDISPLAY_CHARY_SIZE_HALF,           //top y vertex
            DISPLAY_GREEN);
}
void clockdisplay_check_lines(){//This function just checks the
    display_drawLine((320/3), 0, (320/3), 240, DISPLAY_YELLOW);
    display_drawLine(2*(320/3), 0, 2*(320/3), 240, DISPLAY_YELLOW);
    display_drawLine(0, DISPLAY_HEIGHT/DISPLAY_BIN, 320, DISPLAY_HEIGHT/DISPLAY_BIN, DISPLAY_YELLOW);

}
void clock_display_draw_chars(){
    clockdisplay_draw_tens_hours(time[0]);
    clockdisplay_draw_ones_hours(time[1]);
    clockdisplay_draw_tens_minutes(time[3]);
    clockdisplay_draw_ones_minutes(time[4]);
    clockdisplay_draw_tens_seconds(time[6]);
    clockdisplay_draw_ones_seconds(time[7]);
    clockdisplay_draw_left_colon(time[2]);
    clockdisplay_draw_right_colon(time[5]);
}
void clockDisplay_init()
{  // Called only once - performs any necessary inits.
    display_init();  // Must init all of the software and underlying hardware for LCD.
    display_fillScreen(DISPLAY_BLACK);  // Blank the screen.
    clockdisplay_draw_traingles();
    clockdisplay_check_lines();
    sprintf(time, "%2hd:%02hd:%02hd", hours, minutes, seconds);
    clock_display_draw_chars();

}
void clockDisplay_updateTimeDisplay(bool forceUpdateAll)
{  // Updates the time display with latest time.


    sprintf(time, "%2hd:%02hd:%02hd", hours, minutes, seconds);
    clock_display_draw_chars();

}
void clockDisplay_performIncDec(){         // Performs the increment or decrement, depending upon the touched region.


//    if (display_isTouched()){
        display_clearOldTouchData();
        utils_msDelay(45);
        display_getTouchedPoint(&x_touched, &y_touched, &z_touched);

        int8_t region = clockDisplay_computeRegion(x_touched, y_touched);

        if(region == CLOCKDISPLAY_REGION_3){//means we are in the top left region
            if(hours < CLOCKDISPLAY_HOURS_MAX){
                hours++;
            }
            else{
                hours = 1;
            }
            clockDisplay_updateTimeDisplay(0);
        }
        else if(region == CLOCKDISPLAY_REGION_4){
            if(minutes < CLOCKDISPLAY_MINUTESSEC_MAX){
                minutes ++;
            }
            else{
                minutes = 0;
            }
            clockDisplay_updateTimeDisplay(0);
        }
        else if(region == CLOCKDISPLAY_REGION_5){
            if(seconds < CLOCKDISPLAY_MINUTESSEC_MAX){
                seconds ++;
            }
            else{
                seconds = 0;
            }
            clockDisplay_updateTimeDisplay(0);

        }
        else if (region == CLOCKDISPLAY_REGION_0){
            if(hours > 1){
                hours--;
            }
            else{
                hours = CLOCKDISPLAY_HOURS_MAX;
            }
            clockDisplay_updateTimeDisplay(0);

        }
        else if (region == CLOCKDISPLAY_REGION_1){
            if(minutes > 0){
                minutes--;
            }
            else{
                minutes = CLOCKDISPLAY_MINUTESSEC_MAX;
            }
            clockDisplay_updateTimeDisplay(0);

        }
        else if (region == CLOCKDISPLAY_REGION_2){
            if(seconds > 0){
                seconds--;
            }
            else{
                seconds = CLOCKDISPLAY_MINUTESSEC_MAX;
            }
            clockDisplay_updateTimeDisplay(0);

        }

//    }

}
void clockDisplay_advanceTimeOneSecond(){  // Advances the time forward by 1 second.

    if(seconds < CLOCKDISPLAY_MINUTESSEC_MAX){
        seconds++;
    }
    else {
        if(minutes < CLOCKDISPLAY_MINUTESSEC_MAX){
            minutes++;
        }
        else {
            if (hours < CLOCKDISPLAY_HOURS_MAX) {
                hours++;
            }
            else {
                hours = 1;
            }
            minutes = 0;
        }
        seconds = 0;
    }
    clockDisplay_updateTimeDisplay(0);


}
void clockDisplay_runTest(){// Run a test of clock-display functions.

    int j =0;
    clockDisplay_init();
    utils_msDelay(1000);
    while(j < 300){
        if (display_isTouched()){
            utils_msDelay(100);
//            clockDisplay_performIncDec();
            clockDisplay_advanceTimeOneSecond();
            j++;
        }
    }
//    utils_msDelay(5000);
//    for (int i = 0; i < 20; i++) {
//    utils_msDelay(100);
//    clockDisplay_advanceTimeOneSecond();
//    }
//    utils_msDelay(3000);
//    for (int i = 0; i < 20; i++) {
//    utils_msDelay(100);
//    }



}


