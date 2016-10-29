/*
 * intervalTimer.h
 *
 *  Created on: Sep 22, 2015
 *      Author: spence13
 */

#ifndef INTERVALTIMER_H_
#define INTERVALTIMER_H_

#include "xparameters.h"
#include "supportFiles/display.h"
#include "xil_io.h"
#include <stdio.h>
#include <stdint.h>
#include "src/Lab2/buttons.h"


//these #defines deal with addresses and offset of register for the timers and counters
#define INTERVALTIMER_TIMER_0_BASEADDR XPAR_AXI_TIMER_0_BASEADDR //use the definitions found in parameters and rename them
#define INTERVALTIMER_TIMER_1_BASEADDR XPAR_AXI_TIMER_1_BASEADDR
#define INTERVALTIMER_TIMER_2_BASEADDR XPAR_AXI_TIMER_2_BASEADDR
#define INTERVALTIMER_TCSR0_OFFSET 0x00
#define INTERVALTIMER_TCSR1_OFFSET 0x10
#define INTERVALTIMER_TLR0_OFFSET 0x04
#define INTERVALTIMER_TLR1_OFFSET 0x14
#define INTERVALTIMER_TCR0_OFFSET 0x08
#define INTERVALTIMER_TCR1_OFFSET 0x18

//these #defines are the frequencies at which the 3 timers operate
#define INTERVALTIMER_TIMER_0_CLOCK_FREQ_HZ XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ //use the definitions found in parameters and rename them
#define INTERVALTIMER_TIMER_1_CLOCK_FREQ_HZ XPAR_AXI_TIMER_1_CLOCK_FREQ_HZ
#define INTERVALTIMER_TIMER_2_CLOCK_FREQ_HZ XPAR_AXI_TIMER_2_CLOCK_FREQ_HZ


//these 3defines deal with assignment of bit values
#define INTERVALTIMER_LAST_FOUR_ON 0xF
#define INTERVALTIMER_LAST_FOUR_OFF 0x0
#define INTERVALTIMER_ELEVENTH_ON 0X0800
#define INTERVALTIMER_SECOND_OFF 0xFFFD
#define INTERVALTIMER_SEVENTH_ON 0x0080
#define INTERVALTIMER_SEVENTH_OFF 0xFF7F
#define INTERVALTIMER_FIFTH_ON 0x0020
#define INTERVALTIMER_SHIFT32 32
#define INTERVALTIMER_DELAY_COUNT 3


uint32_t intervalTimer_start(uint32_t timerNumber);// this function will start the timers
uint32_t intervalTimer_stop(uint32_t timerNumber);//this is used to stop the timers
uint32_t intervalTimer_reset(uint32_t timerNumber);//this function will reset the timers
uint32_t intervalTimer_init(uint32_t timerNumber);//used to initialize the timers before using them
uint32_t intervalTimer_initAll();//initalize all of the timers
uint32_t intervalTimer_resetAll();//reset all of the timers
uint32_t intervalTimer_testAll();//test all of the timers to see proper functioning
uint32_t intervalTimer_runTest(uint32_t timerNumber);//run a test of the timers in which we can see if they are counting correctly
uint32_t intervalTimer_getTotalDurationInSeconds(uint32_t timerNumber, double *seconds);//this will return the time interval for which you let the timers run
u32 readTimerRegister(uint32_t timerNumber, uint32_t registerOffset);//called in other functions to read the timer registers
void waitALongTime();//used in test functions to wait a certain interval for the timers to operate

#endif /* INTERVALTIMER_H_ */





