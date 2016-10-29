
// Print out "hello world" on both the console and the LCD screen.

#include <stdio.h>
#include "supportFiles/display.h"
int main() {
	display_init();  // Must init all of the software and underlying hardware for LCD.
	display_fillScreen(DISPLAY_BLACK);  // Blank the screen.
	display_setCursor(0, 0);            // The upper left of the LCD screen.
	display_setTextColor(DISPLAY_RED);  // Make the text red.
	display_setTextSize(2);             // Make the text a little larger.

	//display screen is 320 X 240 pixels
	display_drawLine(0, 240, 320, 0, DISPLAY_GREEN); //make a line bottom left to top right
	display_drawLine(0, 0, 320, 240, DISPLAY_GREEN); //make a line top left to bottom right
	display_drawCircle(80, 240/2, 25, DISPLAY_RED); //make a circle on left side of screen
	display_fillCircle(240, 240/2, 25, DISPLAY_RED); //make a circle on right side of screen
	display_fillTriangle(320/2, 90, 128, 30, 192, 30, DISPLAY_YELLOW); //make the top solid triangle
	display_drawTriangle(320/2, 150, 128, 210, 192, 210, DISPLAY_YELLOW); //make the bottom outlined triangle


	//display_println("hello world (on the LCD)!");    // This actually prints the string to the LCD.
	printf("hello world!\n\r");  // This prints on the console.
}

// This function must be defined but can be left empty for now.
// You will use this function in a later lab.
// It is called in the timer interrupt service routine (see interrupts.c in supportFiles).
void isr_function() {
    // Empty for now.
}
