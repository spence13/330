/*
 * switches.c
 *
 *  Created on: Sep 16, 2015
 *      Author: spence13
 */


#include "switches.h"




int switches_init()//switches function as input cuz we want to read the switch values
{
    //initializes the led the zero disables the error print out
    Xil_Out32(XPAR_SLIDE_SWITCHES_BASEADDR + GPIO_TRI_OFFSET, LAST_FOUR_ON);// Low assertion.  turn the tri-state driver off by writing ones to the last 4 digits of the GPIO_TRI register.

    if(Xil_In32(XPAR_SLIDE_SWITCHES_BASEADDR + GPIO_TRI_OFFSET) ==  LAST_FOUR_ON) //this is a check to see if the tri initialized correctly (turned off) so we can read
    {
        return SWITCHES_INIT_STATUS_OK;  //if tri state driver was initialized correctly return a 1
    }
    else
    {
        return SWITCHES_INIT_STATUS_FAIL; // if for some reason tri state driver was not initialized correctly return a zero
    }
}

int32_t switches_read()
{
    uint32_t read = Xil_In32(XPAR_SLIDE_SWITCHES_BASEADDR + GPIO_DATA_OFFSET); //reads the value at the given address with the appropriate offset (data)
    return (read & LAST_FOUR_ON); //bitwise & in order to make all but last 4 bits zeros. (masking)
}


void switches_runTest()
{
    switches_init();  // initializes both the switches and the leds before running them
    leds_init(0);
    while(switches_read() != LAST_FOUR_ON)     //loops runs as long as all the leds are not simultaneoulsy turned on
    {
        leds_write(switches_read()); //writes the values we read to the led to turn them on or off
    }
    leds_write(LAST_FOUR_ON); //turn all the leds on once they have all been simultaneously turned on
    //leds_write(LAST_FOUR_OFF); //turn all the leds off once they have all been simultaneously turned on
}
