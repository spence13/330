/*
 * buttons.c
 *
 *  Created on: Sep 16, 2015
 *      Author: spence13
 */


#include "buttons.h"



int buttons_init()
{
    uint32_t *ptr = (uint32_t *) XPAR_PUSH_BUTTONS_BASEADDR + GPIO_TRI_OFFSET; //create a pointer with the base address and appropriate offset of 0x4
    *ptr = LAST_FOUR_ON; //set the last four bits of the pointers value to ones. this turns the tri-state drive to a readable pin
      if(*ptr == LAST_FOUR_ON) // make sure that the last four bits of the pointers value are ones
      {
          return BUTTONS_INIT_STATUS_OK; //returns a status of one if the initialization was set so that the last four bits of the pointer are ones
      }
      else
      {
          return BUTTONS_INIT_STATUS_FAIL; //returns a fail status of zero if the initialization didnt work
      }
}


int32_t buttons_read()
{
    uint32_t *ptr = (uint32_t *) XPAR_PUSH_BUTTONS_BASEADDR + GPIO_DATA_OFFSET;  // creates a pointer called ptr and refers it to the base address with appropriate offset
    return *ptr & LAST_FOUR_ON;             //bitwise & in order to make all but last 4 bits zeros. (masking)  *ptr means refer to value stored at address NOT address
}


void buttons_runTest()
{
    buttons_init();         //initializes the tri state driver of the buttons to be read

 int32_t current = buttons_read();  // sets a variable current equal to what the button reads the value to be
    while(buttons_read() != LAST_FOUR_ON)   //while loop runs while all the buttons are not simultaneously turned on
   {
        if(current != buttons_read())   //if there is a change in the value of buttons_read from what it used to be then we enter the if statement
        {
            current = buttons_read();   //reset current variable equal to buttons_read()
            display(current);       //pass the current variable into the display function
        }
   }
    display(current);  // turn on all buttons after all the buttons are simultaneously pushed.
   //display_fillScreen(DISPLAY_BLACK);  // Blank the screen after all the buttons are simultaneously pushed.

}

void display(int32_t current)
{
    display_setTextColor(DISPLAY_BLACK);    //set the text color to black
    display_setTextSize(TEXT_SIZE);        //set text size equal to 2
    display_fillScreen(DISPLAY_BLACK);      // start with the screen as black

        if((current& HEX_EIGHT) == HEX_EIGHT)       // bitwise and the current variable with 8; then check to see if that equals 8. if it does you know the current variable had a 'one' in at least the '8' position
        {
            display_fillRect(0, 0, DISPLAY_WIDTH*QUARTER, DISPLAY_HEIGHT*HALF, DISPLAY_BLUE);  //set the location and size of the rectangle
            display_setCursor(DISPLAY_WIDTH/TWELVE, DISPLAY_HEIGHT*QUARTER); //set the starting location of the cursor for the texts
            display_println("BTN3");  //print button 3 on the first rectangle button
        }

        if((current& HEX_FOUR) == HEX_FOUR)// bitwise and the current variable with four; then check to see if that equals four
        {
            display_fillRect((DISPLAY_WIDTH*QUARTER), 0, DISPLAY_WIDTH*QUARTER, DISPLAY_HEIGHT*HALF, DISPLAY_RED);//set the location and size of the rectangle
            display_setCursor(DISPLAY_WIDTH*THREE_TENTHS, DISPLAY_HEIGHT*QUARTER); //set the starting location of the cursor for the texts
            display_println("BTN2");  //print button 2 on the second rectangle button
        }

       if((current & HEX_TWO) == HEX_TWO)// bitwise and the current variable with two; then check to see if that equals two
        {
            display_fillRect((DISPLAY_WIDTH*HALF), 0, DISPLAY_WIDTH*QUARTER, DISPLAY_HEIGHT*HALF, DISPLAY_GREEN);//set the location and size of the rectangle
            display_setCursor(DISPLAY_WIDTH*SIX_TENTHS, DISPLAY_HEIGHT*QUARTER); //set the starting location of the cursor for the texts
            display_println("BTN1");  //print button 1 on the third rectangle button
        }

        if((current & HEX_ONE) == HEX_ONE)// bitwise and the current variable with one; then check to see if that equals one
        {
            display_fillRect((DISPLAY_WIDTH*THREE_FOURTHS), 0, DISPLAY_WIDTH*QUARTER, DISPLAY_HEIGHT*HALF, DISPLAY_YELLOW);//set the location and size of the rectangle
            display_setCursor(DISPLAY_WIDTH*EIGHT_TENTHS, DISPLAY_HEIGHT*QUARTER); //set the starting location of the cursor for the texts
            display_println("BTN0");  //print button 0 on the fourth rectangle button
        }

}
