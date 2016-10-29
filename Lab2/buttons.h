/*
 * buttons.h
 *
 *  Created on: Sep 16, 2015
 *      Author: spence13
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "supportFiles/display.h"
#include "xil_io.h"

#define BUTTONS_INIT_STATUS_OK 1
#define BUTTONS_INIT_STATUS_FAIL 0
#define XPAR_PUSH_BUTTONS_BASEADDR 0x41200000
#define GPIO_DATA_OFFSET 0x0
#define GPIO_TRI_OFFSET 0x4
#define LAST_FOUR_ON 0xF
#define HEX_EIGHT 0x8
#define HEX_FOUR 0x4
#define HEX_TWO 0x2
#define HEX_ONE 0x1
#define HEX_ZERO 0x0

#define DISPLAY_HEIGHT 240
#define DISPLAY_WIDTH 320
#define TEXT_SIZE 2
#define QUARTER .25
#define HALF .5
#define THREE_FOURTHS 0.75
#define TWELVE 12
#define THREE_TENTHS 0.3
#define SIX_TENTHS 0.6
#define EIGHT_TENTHS 0.8



// Helper function to read GPIO registers.
uint32_t buttons_readGpioRegister(uint32_t offest);



// Initializes the button driver software and hardware. Returns one of the defined status values (above).
int buttons_init();

// Returns the current value of all 4 buttons as the lower 4 bits of the returned value.
// bit3 = BTN3, bit2 = BTN2, bit1 = BTN1, bit0 = BTN0.
int32_t buttons_read();

// Runs a test of the buttons. As you push the buttons, graphics and messages will be written to the LCD
// panel. The test will until all 4 pushbuttons are simultaneously pressed.
void buttons_runTest();


void display(int32_t);





#endif /* BUTTONS_H_ */
