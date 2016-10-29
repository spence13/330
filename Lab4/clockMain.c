/*
 * clockMain.c
 *
 *  Created on: Sep 26, 2015
 *      Author: spence13
 */

#include "clockDisplay.h"
#include "clockControl.h"
#include "src/lab3/intervalTimer.h"
#include <stdio.h>
#include "supportFiles/leds.h"
#include "supportFiles/globalTimer.h"
#include "supportFiles/interrupts.h"
#include <stdbool.h>
#include <stdint.h>
#include "supportFiles/display.h"
#include "xparameters.h"



/*int main()
{
    clockDisplay_init();

    while (1)
    {
        clockControl_tick();
    }
}*/


int main()
{
    // Initialize the GPIO LED driver and print out an error message if it fails (argument = true).
       // You need to init the LEDs so that LD4 can function as a heartbeat.
    leds_init(true);
    // Init all interrupts (but does not enable the interrupts at the devices).
    // Prints an error message if an internal failure occurs because the argument = true.
    interrupts_initAll(true);
    interrupts_setPrivateTimerLoadValue(CLOCK_DISPLAY_TIMER_LOAD_VALUE);
    u32 privateTimerTicksPerSecond = interrupts_getPrivateTimerTicksPerSecond();
    printf("private timer ticks per second: %ld\n\r", privateTimerTicksPerSecond);
    // Allow the timer to generate interrupts.
    interrupts_enableTimerGlobalInts();
    // Initialization of the clock display is not time-dependent, do it outside of the state machine.
    clockDisplay_init();
    // Keep track of your personal interrupt count. Want to make sure that you don't miss any interrupts.
     int32_t personalInterruptCount = 0;
    // Start the private ARM timer running.
    interrupts_startArmPrivateTimer();
    // Enable interrupts at the ARM.
    interrupts_enableArmInts();
    // interrupts_isrInvocationCount() returns the number of times that the timer ISR was invoked.
    // This value is maintained by the timer ISR. Compare this number with your own local
    // interrupt count to determine if you have missed any interrupts.
     while (interrupts_isrInvocationCount() < (CLOCK_DISPLAY_TOTAL_SECONDS * privateTimerTicksPerSecond)) {
      if (interrupts_isrFlagGlobal) {  // This is a global flag that is set by the timer interrupt handler.
          // Count ticks.
        personalInterruptCount++;
        clockControl_tick();
          interrupts_isrFlagGlobal = 0;
      }
   }
   interrupts_disableArmInts();
   printf("isr invocation count: %ld\n\r", interrupts_isrInvocationCount());
   printf("internal interrupt count: %ld\n\r", personalInterruptCount);
   return 0;
}
/*
static uint32_t isr_functionCallCount = 0;

int main()
{
    // Initialize the GPIO LED driver and print out an error message if it fails (argument = true).
    // You need to init the LEDs so that LD4 can function as a heartbeat.
    leds_init(true);
    // Init all interrupts (but does not enable the interrupts at the devices).
    // Prints an error message if an internal failure occurs because the argument = true.
    interrupts_initAll(true);
    interrupts_setPrivateTimerLoadValue(TIMER_LOAD_VALUE);
    printf("timer load value:%ld\n\r", (int32_t) TIMER_LOAD_VALUE);
    u32 privateTimerTicksPerSecond = interrupts_getPrivateTimerTicksPerSecond();
    printf("private timer ticks per second: %ld\n\r", privateTimerTicksPerSecond);
    interrupts_enableTimerGlobalInts();
    // Initialization of the clock display is not time-dependent, do it outside of the state machine.
    clockDisplay_init();
    // Start the private ARM timer running.
    interrupts_startArmPrivateTimer();
    // Enable interrupts at the ARM.
    interrupts_enableArmInts();
    // The while-loop just waits until the total number of timer ticks have occurred before proceeding.
    while (interrupts_isrInvocationCount() < (TOTAL_SECONDS * privateTimerTicksPerSecond));
    // All done, now disable interrupts and print out the interrupt counts.
    interrupts_disableArmInts();
    printf("isr invocation count: %ld\n\r", interrupts_isrInvocationCount());
    printf("internal interrupt count: %ld\n\r", isr_functionCallCount);
    return 0;
}*/



// It is called in the timer interrupt service routine (see interrupts.c in supportFiles).
void isr_function()
{
    //clockControl_tick();
   // isr_functionCallCount++;
}
