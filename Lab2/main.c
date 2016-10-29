/*
 * main.c
 *
 *  Created on: Sep 16, 2015
 *      Author: spence13
 */


#include "switches.h"
#include "buttons.h"

int main()
{
    display_init();  // Must initialize all of the software and underlying hardware for LCD.
    display_fillScreen(DISPLAY_BLACK);  // Blank the screen at the very beginning

    switches_runTest();  // call the switches test
    buttons_runTest();      // call the buttons test
}





// This function must be defined but can be left empty for now.
// You will use this function in a later lab.
// It is called in the timer interrupt service routine (see interrupts.c in supportFiles).
void isr_function() {
    // Empty for now.
}
