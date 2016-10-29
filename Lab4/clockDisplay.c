/*
 * clockDisplay.c
 *
 *  Created on: Sep 26, 2015
 *      Author: spence13
 */

#include <stdbool.h>
#include "clockDisplay.h"
#include <math.h>

//global variables must change to track the time
uint32_t hour = CLOCK_DISPLAY_HOUR_MAX_TIME; //the tracks the value of hours
uint32_t min = CLOCK_DISPLAY_MIN_MAX_TIME; //this tracks the value of minutes
uint32_t sec = CLOCK_DISPLAY_SEC_MAX_TIME;//this tracks the value of seconds
char time[CLOCK_DISPLAY_TIME_CHAR_LENGTH];//this set an array of certain length called time


//this will initialize the screen before using it
void clockDisplay_init()
{
    display_init();  // Must initialize all of the software and underlying hardware for LCD.
    display_fillScreen(CLOCK_DISPLAY_BLACK);  // Blank the screen with all black
    display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
    display_setTextSize(CLOCK_DISPLAY_TEXT_SIZE);  // this sets the text size

    //these 3 'fill triangles' correctly position the upper 3 triangle from left to right
    //top left
    display_fillTriangle(CLOCK_DISPLAY_HOUR_TRI_X1,CLOCK_DISPLAY_UPPER_TRI_BASE_YPOS, //bottom left point
    CLOCK_DISPLAY_HOUR_TRI_X2, CLOCK_DISPLAY_UPPER_TRI_BASE_YPOS, //bottom right point
    CLOCK_DISPLAY_HOUR_TRI_X3,CLOCK_DISPLAY_UPPER_TRI_TIP_YPOS, CLOCK_DISPLAY_GREEN);//top point and set the color to green
    //top middle
    display_fillTriangle(CLOCK_DISPLAY_MIN_TRI_X1, CLOCK_DISPLAY_UPPER_TRI_BASE_YPOS, //bottom left point
    CLOCK_DISPLAY_MIN_TRI_X2, CLOCK_DISPLAY_UPPER_TRI_BASE_YPOS, //bottom right point
    CLOCK_DISPLAY_MIN_TRI_X3, CLOCK_DISPLAY_UPPER_TRI_TIP_YPOS, CLOCK_DISPLAY_GREEN);//top point and set the color to green
    //top right
    display_fillTriangle(CLOCK_DISPLAY_SEC_TRI_X1, CLOCK_DISPLAY_UPPER_TRI_BASE_YPOS,//bottom left point
    CLOCK_DISPLAY_SEC_TRI_X2, CLOCK_DISPLAY_UPPER_TRI_BASE_YPOS, //bottom right point
    CLOCK_DISPLAY_SEC_TRI_X3, CLOCK_DISPLAY_UPPER_TRI_TIP_YPOS, CLOCK_DISPLAY_GREEN);//top point and set the color to green

    //these 3 'fill triangles' correctly position the lower 3 triangle from left to right
    //bottom left
    display_fillTriangle(CLOCK_DISPLAY_HOUR_TRI_X1,CLOCK_DISPLAY_LOWER_TRI_BASE_YPOS,//top left point
    CLOCK_DISPLAY_HOUR_TRI_X2,CLOCK_DISPLAY_LOWER_TRI_BASE_YPOS,//top right point
    CLOCK_DISPLAY_HOUR_TRI_X3,CLOCK_DISPLAY_LOWER_TRI_TIP_YPOS,CLOCK_DISPLAY_GREEN);//bottom point and set color to green
    //bottom middle
    display_fillTriangle(CLOCK_DISPLAY_MIN_TRI_X1,CLOCK_DISPLAY_LOWER_TRI_BASE_YPOS,//top left point
    CLOCK_DISPLAY_MIN_TRI_X2,CLOCK_DISPLAY_LOWER_TRI_BASE_YPOS,//top right point
    CLOCK_DISPLAY_MIN_TRI_X3,CLOCK_DISPLAY_LOWER_TRI_TIP_YPOS,CLOCK_DISPLAY_GREEN);//bottom point and set color to green
    //bottom right
    display_fillTriangle(CLOCK_DISPLAY_SEC_TRI_X1,CLOCK_DISPLAY_LOWER_TRI_BASE_YPOS,//top left point
    CLOCK_DISPLAY_SEC_TRI_X2,CLOCK_DISPLAY_LOWER_TRI_BASE_YPOS,//top right point
    CLOCK_DISPLAY_SEC_TRI_X3,CLOCK_DISPLAY_LOWER_TRI_TIP_YPOS,CLOCK_DISPLAY_GREEN);//bottom point and set color to green

    display_setCursor(CLOCK_DISPLAY_XPOS_HOUR_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
    display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
    sprintf(time, "%2hd:%02hd:%02hd",hour, min, sec); //print the display numbers to an array
    display_print(time);//print the char array called time to the lcd display
}

// this will update the display to show the correct time
void clockDisplay_updateTimeDisplay(bool forceUpdateAll)// Updates the time display with latest time.
{
    display_setCursor(CLOCK_DISPLAY_XPOS_HOUR_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
    display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
    sprintf(time, "%2hd:%02hd:%02hd", hour,min,sec);//print the display numbers to an array
    display_print(time);//print the char array called time to the lcd display
}

//this function can either increment or decrement hour, min, or sec
void clockDisplay_performIncDec()
{
    display_clearOldTouchData(); // Throws away all previous touch data.
    int16_t x, y; //two variables used in getting location of touch
    uint8_t z; //returns pressure of touch
    display_getTouchedPoint(&x, &y, &z); // Returns the x-y coordinate point and the pressure (z).

    //upper 3 rectangles -- these function will increment time
    if (x>CLOCK_DISPLAY_HOUR_TRI_X1  && x<CLOCK_DISPLAY_HOUR_TRI_X2 && y >CLOCK_DISPLAY_UPPER_TRI_TIP_YPOS && y <CLOCK_DISPLAY_UPPER_TRI_BASE_YPOS ) //hour
    {
        display_setCursor(CLOCK_DISPLAY_XPOS_HOUR_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
        display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text BLACK to blank previous number
        sprintf(time, "%2hd", hour);//print the display numbers to an array
        display_print(time);//print the char array called time to the lcd display

        if(hour < CLOCK_DISPLAY_HOUR_MAX_TIME)//if hours is less than 12
        {
            hour++;//increment hours
        }
        else
        {
            hour = 0;//reset it to zero since it was 12
        }
        clockDisplay_updateTimeDisplay(1); // used to update all time displays
    }

    if (x>CLOCK_DISPLAY_MIN_TRI_X1 && x<CLOCK_DISPLAY_MIN_TRI_X2 && y >CLOCK_DISPLAY_UPPER_TRI_TIP_YPOS && y <CLOCK_DISPLAY_UPPER_TRI_BASE_YPOS )//minutes
    {
        display_setCursor(CLOCK_DISPLAY_XPOS_MIN_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
        display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text BLACK to blank previous number
        sprintf(time, "%02hd", min);//print the display numbers to an array
        display_print(time);//print the char array called time to the lcd display

        if(min < CLOCK_DISPLAY_MIN_MAX_TIME)//if minutes is less than 59
        {
            min++;//increment minutes
        }
        else
        {
            min = 0;//reset it to zero since it was 59
        }
        clockDisplay_updateTimeDisplay(1);// used to update all time displays
    }

    if (x>CLOCK_DISPLAY_SEC_TRI_X1 && x<CLOCK_DISPLAY_SEC_TRI_X2 && y >CLOCK_DISPLAY_UPPER_TRI_TIP_YPOS && y <CLOCK_DISPLAY_UPPER_TRI_BASE_YPOS )//second
    {
        display_setCursor(CLOCK_DISPLAY_XPOS_SEC_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
        display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text BLACK to blank previous number
        sprintf(time, "%02hd",sec);//print the display numbers to an array
        display_print(time);//print the char array called time to the lcd display

        if(sec < CLOCK_DISPLAY_SEC_MAX_TIME) //if seconds is less than 59
        {
            sec++;//increment seconds
        }
        else
        {
            sec = 0;//reset it to zero since it was 59
        }
        clockDisplay_updateTimeDisplay(1);// used to update all time displays
    }

    //lower 3 rectangles -- these function will decrement time
    if (x>CLOCK_DISPLAY_HOUR_TRI_X1 && x<CLOCK_DISPLAY_HOUR_TRI_X2 && y >CLOCK_DISPLAY_LOWER_TRI_BASE_YPOS && y <CLOCK_DISPLAY_LOWER_TRI_TIP_YPOS )//hour
    {
        display_setCursor(CLOCK_DISPLAY_XPOS_HOUR_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
        display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text BLACK to blank previous number
        sprintf(time, "%2hd",hour);//print the display numbers to an array
        display_print(time);//print the char array called time to the lcd display

        if(hour == 0)
        {
            hour = CLOCK_DISPLAY_HOUR_MAX_TIME;//reset hours to 12
        }
        else
        {
            hour--;//decrement hours
        }
        clockDisplay_updateTimeDisplay(1);// used to update all time displays
    }

    if (x>CLOCK_DISPLAY_MIN_TRI_X1 && x<CLOCK_DISPLAY_MIN_TRI_X2 && y >CLOCK_DISPLAY_LOWER_TRI_BASE_YPOS && y <CLOCK_DISPLAY_LOWER_TRI_TIP_YPOS )//minutes
    {
        display_setCursor(CLOCK_DISPLAY_XPOS_MIN_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
        display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text BLACK to blank previous number
        sprintf(time, "%02hd",min);//print the display numbers to an array
        display_print(time);//print the char array called time to the lcd display

        if(min == 0)
        {
            min = CLOCK_DISPLAY_MIN_MAX_TIME;//set minutes equal to 59
        }
        else
        {
            min--;//decrement minutes
        }
        clockDisplay_updateTimeDisplay(1);// used to update all time displays
    }

    if (x>CLOCK_DISPLAY_SEC_TRI_X1 && x<CLOCK_DISPLAY_SEC_TRI_X2 && y >CLOCK_DISPLAY_LOWER_TRI_BASE_YPOS && y <CLOCK_DISPLAY_LOWER_TRI_TIP_YPOS )//seconds
    {
        display_setCursor(CLOCK_DISPLAY_XPOS_SEC_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
        display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text BLACK to blank previous number
        sprintf(time, "%02hd",sec);//print the display numbers to an array
        display_print(time);//print the char array called time to the lcd display

        if(sec == 0)
        {
            sec = CLOCK_DISPLAY_SEC_MAX_TIME;//set seconds equal to 59
        }
        else
        {
            sec--; //decrement seconds
        }
        clockDisplay_updateTimeDisplay(1);// used to update all time displays
    }
}

//advances the time by one second with proper roll overs for minutes and hours
void clockDisplay_advanceTimeOneSecond()
{
    if(sec < CLOCK_DISPLAY_SEC_MAX_TIME)
    {
        display_setCursor(CLOCK_DISPLAY_XPOS_SEC_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
        display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text BLACK to blank previous number
        sprintf(time, "%02hd",sec);//print the display numbers to an array
        display_print(time);//print the char array called time to the lcd display
        sec++;
    }
    else
    {
        display_setCursor(CLOCK_DISPLAY_XPOS_SEC_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
        display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text BLACK to blank previous number
        sprintf(time, "%02hd",sec);//print the display numbers to an array
        display_print(time);//print the char array called time to the lcd display
        sec = 0;//roll it back over to zero since it was equal to its max value

        if(min < CLOCK_DISPLAY_MIN_MAX_TIME)
        {
            display_setCursor(CLOCK_DISPLAY_XPOS_MIN_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
            display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text BLACK to blank previous number
            sprintf(time, "%02hd",min);//print the display numbers to an array
            display_print(time);//print the char array called time to the lcd display
            min++;
        }
        else
        {
            display_setCursor(CLOCK_DISPLAY_XPOS_MIN_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
            display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text BLACK to blank previous number
            sprintf(time, "%02hd",min);//print the display numbers to an array
            display_print(time);//print the char array called time to the lcd display
            min = 0;//roll it back over to zero since it was equal to its max value

            if (hour < CLOCK_DISPLAY_HOUR_MAX_TIME)
            {
                display_setCursor(CLOCK_DISPLAY_XPOS_HOUR_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text BLACK to blank previous number
                sprintf(time, "%2hd",hour);//print the display numbers to an array
                display_print(time);//print the char array called time to the lcd display
                hour++;
            }
            else
            {
                display_setCursor(CLOCK_DISPLAY_XPOS_HOUR_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text BLACK to blank previous number
                sprintf(time, "%2hd",hour);//print the display numbers to an array
                display_print(time);//print the char array called time to the lcd display
                hour = 0;//roll it back over to zero since it was equal to its max value
            }

        }
    }
    clockDisplay_updateTimeDisplay(0);// used to update all time displays
}

//runs a test to see if the display can count and update the digits to match a simulated timer
void clockDisplay_runTest()
{
    display_setCursor(CLOCK_DISPLAY_LEFT_COLON, CLOCK_DISPLAY_YPOS_DIGITS);//set the positioning of the colon before printing
    display_print(":");// this is the left most colon
    display_setCursor(CLOCK_DISPLAY_RIGHT_COLON, CLOCK_DISPLAY_YPOS_DIGITS);//set the positioning of the colon before printing
    display_print(":");// this is the right most colon


    for(int hourten=0; hourten<= 24; hourten++) //counts the tenths place of hours
    {
        display_setCursor(CLOCK_DISPLAY_XPOS_HOUR_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
        display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text black.
        display_print(hourten-1);// print the last digit in black to erase it

        display_setCursor(CLOCK_DISPLAY_XPOS_HOUR_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
        display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
        display_print(hourten);//This prints the digit to the LCD

        for(int hourone=0; hourone<10; hourone++)//counts the ones place of hours
        {
            display_setCursor(CLOCK_DISPLAY_XPOS_HOUR_ONES, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
            display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text black.
            display_print(hourone-1);// print the last digit in black to erase it

            display_setCursor(CLOCK_DISPLAY_XPOS_HOUR_ONES, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
            display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
            display_print(hourone);// This  prints the digit to the LCD

            for(int minten=0; minten<6; minten++)//counts the tenths place of minutes
            {
                display_setCursor(CLOCK_DISPLAY_XPOS_MIN_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text black.
                display_print(minten-1);// print the last digit in black to erase it

                display_setCursor(CLOCK_DISPLAY_XPOS_MIN_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
                display_print(minten);//This prints the digit to the LCD

                for(int minone=0; minone<10; minone++) //counts the ones place of minutes
                {
                    display_setCursor(CLOCK_DISPLAY_XPOS_MIN_ONES, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                    display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text black.
                    display_print(minone-1);// print the last digit in black to erase it

                    display_setCursor(CLOCK_DISPLAY_XPOS_MIN_ONES, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                    display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
                    display_print(minone);// This prints the digit to the LCD

                    for(int secten=0; secten<6; secten++) //counts the tenths place of second
                    {
                        display_setCursor(CLOCK_DISPLAY_XPOS_SEC_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                        display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text black.
                        display_print(secten-1);// print the last digit in black to erase it

                        display_setCursor(CLOCK_DISPLAY_XPOS_SEC_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                        display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
                        display_print(secten);//  This prints the digit to the LCD

                        for(int secone=0; secone<10; secone++)//counts the ones place seconds
                        {
                            display_setCursor(CLOCK_DISPLAY_XPOS_SEC_ONES, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                            display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text black.
                            display_print(secone-1);// print the last digit in black to erase it

                            display_setCursor(CLOCK_DISPLAY_XPOS_SEC_ONES, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                            display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
                            display_print(secone);// This actually prints the string to the LCD
                            utils_msDelay(10); //this is a delay function that allows a rate of 10x time keeping
                        }
                        display_setCursor(CLOCK_DISPLAY_XPOS_SEC_ONES, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                        display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text black.
                        display_print("9");// print the last digit in black to erase it

                        display_setCursor(CLOCK_DISPLAY_XPOS_SEC_ONES, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                        display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
                        display_print("0");// reset it by printing a zero
                    }
                    display_setCursor(CLOCK_DISPLAY_XPOS_SEC_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                    display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text black.
                    display_print("5");// print the last digit in black to erase it

                    display_setCursor(CLOCK_DISPLAY_XPOS_SEC_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                    display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
                    display_print("0");// reset it by printing a zero
                }
                display_setCursor(CLOCK_DISPLAY_XPOS_MIN_ONES, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text black.
                display_print("9");// print the last digit in black to erase it

                display_setCursor(CLOCK_DISPLAY_XPOS_MIN_ONES, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
                display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
                display_print("0");// reset it by printing a zero
            }
            display_setCursor(CLOCK_DISPLAY_XPOS_MIN_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
            display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text black.
            display_print("5");// print the last digit in black to erase it

            display_setCursor(CLOCK_DISPLAY_XPOS_MIN_TENS, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
            display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
            display_print("0");/// reset it by printing a zero
        }
        display_setCursor(CLOCK_DISPLAY_XPOS_HOUR_ONES, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
        display_setTextColor(CLOCK_DISPLAY_BLACK);  // Make the text black.
        display_print("9");// print the last digit in black to erase it

        display_setCursor(CLOCK_DISPLAY_XPOS_HOUR_ONES, CLOCK_DISPLAY_YPOS_DIGITS);//position the cursor before printing digit
        display_setTextColor(CLOCK_DISPLAY_GREEN);  // Make the text green.
        display_print("0");// reset it by printing a zero
    }
}
