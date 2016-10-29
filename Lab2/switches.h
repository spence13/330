/*
 * switches.h
 *
 *  Created on: Sep 16, 2015
 *      Author: spence13
 */

#ifndef SWITCHES_H_
#define SWITCHES_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "supportFiles/leds.h"
#include "xil_io.h"



#define SWITCHES_INIT_STATUS_OK 1
#define SWITCHES_INIT_STATUS_FAIL 0
#define XPAR_SLIDE_SWITCHES_BASEADDR 0x41220000
#define GPIO_DATA_OFFSET 0x0
#define GPIO_TRI_OFFSET 0x4
#define LAST_FOUR_ON 0xF
#define LAST_FOUR_OFF 0x0
#define HEX_FOUR 0x4

// Initializes the SWITCHES driver software and hardware. Returns one of the STATUS values defined above.
int switches_init();

// Returns the current value of all 4 SWITCHESs as the lower 4 bits of the returned value.
// bit3 = SW3, bit2 = SW2, bit1 = SW1, bit0 = SW0.
int32_t switches_read();

// Runs a test of the switches. As you slide the switches, LEDs directly above the switches will illuminate.
// The test will run until all switches are slid upwards. When all 4 slide switches are slid upward,
// this function will return.
void switches_runTest();






#endif /* SWITCHES_H_ */
