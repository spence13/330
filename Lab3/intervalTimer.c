/*
 * intervalTimer.c

 *
 *  Created on: Sep 22, 2015
 *      Author: spence13
 */

#include "intervalTimer.h"

//used to initialize the timer before operating it
uint32_t intervalTimer_init(uint32_t timerNumber)
{
    if(timerNumber == 0)
    {
        Xil_Out32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, 0x0000);// write a 0 to the TCSR0 register..
        Xil_Out32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCSR1_OFFSET, 0x0000);// write a 0 to the TCSR1 register.

        uint32_t read = Xil_In32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCSR0_OFFSET); //get the number stored in TCSR0
        uint32_t newread = read | INTERVALTIMER_ELEVENTH_ON;// make the eleventh bit a 1
        uint32_t twonew = newread & INTERVALTIMER_SECOND_OFF; //make the second bit a 0 using masking
        Xil_Out32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, twonew);// SET THE CASC BIT AS 1 WHICH MAKES IT CASCADING; set the UDT0 bit as 0 which makes it an up counter
    }
    if(timerNumber == 1)
    {
        Xil_Out32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, 0x0000);// write a 0 to the TCSR0 register..
        Xil_Out32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCSR1_OFFSET, 0x0000);// write a 0 to the TCSR1 register.

        uint32_t read = Xil_In32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCSR0_OFFSET); //get the number stored in TCSR0
        uint32_t newread = read | INTERVALTIMER_ELEVENTH_ON;// make the eleventh bit a 1
        uint32_t twonew = newread & INTERVALTIMER_SECOND_OFF; //make the second bit a 0 using masking
        Xil_Out32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, twonew);// SET THE CASC BIT AS 1 WHICH MAKES IT CASCADING; set the UDT0 bit as 0 which makes it an up counter
    }
    if(timerNumber == 2)
    {
        Xil_Out32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, 0x0000);// write a 0 to the TCSR0 register..
        Xil_Out32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCSR1_OFFSET, 0x0000);// write a 0 to the TCSR1 register.

        uint32_t read = Xil_In32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCSR0_OFFSET); //get the number stored in TCSR0
        uint32_t newread = read | INTERVALTIMER_ELEVENTH_ON;// make the eleventh bit a 1
        uint32_t twonew = newread & INTERVALTIMER_SECOND_OFF; //make the second bit a 0 using masking
        Xil_Out32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, twonew);// SET THE CASC BIT AS 1 WHICH MAKES IT CASCADING; set the UDT0 bit as 0 which makes it an up counter
    }
}

//used to start a chosen timer
uint32_t intervalTimer_start(uint32_t timerNumber)
{
    if(timerNumber == 0)
    {
        uint32_t read = Xil_In32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCSR0_OFFSET); //get the number stored in TCSR0
        uint32_t newread = read | INTERVALTIMER_SEVENTH_ON;// make the seventh bit a 1
        Xil_Out32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, newread);// SET THE ENT BIT AS 1 WHICH enables the counter
    }
    if(timerNumber == 1)
    {
        uint32_t read = Xil_In32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCSR0_OFFSET); //get the number stored in TCSR0
        uint32_t newread = read | INTERVALTIMER_SEVENTH_ON;// make the seventh bit a 1
        Xil_Out32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, newread);// SET THE ENT BIT AS 1 WHICH enables the counter
    }
    if(timerNumber == 2)
    {
        uint32_t read = Xil_In32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCSR0_OFFSET); //get the number stored in TCSR0
        uint32_t newread = read | INTERVALTIMER_SEVENTH_ON;// make the seventh bit a 1
        Xil_Out32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, newread);// SET THE ENT BIT AS 1 WHICH enables the counter
    }
}

//used to stop a chosen timer
uint32_t intervalTimer_stop(uint32_t timerNumber)
{
    if(timerNumber == 0)
    {
        uint32_t read = Xil_In32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCSR0_OFFSET); //get the number stored in TCSR0
        uint32_t newread = read & INTERVALTIMER_SEVENTH_OFF;// make the seventh bit a 0
        Xil_Out32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, newread);// SET THE ENT BIT AS 0 WHICH disables the counter
    }
    if(timerNumber == 1)
    {
        uint32_t read = Xil_In32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCSR0_OFFSET); //get the number stored in TCSR0
        uint32_t newread = read & INTERVALTIMER_SEVENTH_OFF;// make the seventh bit a 0
        Xil_Out32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, newread);// SET THE ENT BIT AS 0 WHICH disables the counter
    }
    if(timerNumber == 2)
    {
        uint32_t read = Xil_In32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCSR0_OFFSET); //get the number stored in TCSR0
        uint32_t newread = read & INTERVALTIMER_SEVENTH_OFF;// make the seventh bit a 0
        Xil_Out32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, newread);// SET THE ENT BIT AS 0 WHICH disables the counter
    }
}

//used to reset a chosen timer
uint32_t intervalTimer_reset(uint32_t timerNumber)
{
    if(timerNumber == 0)
    {
        // to store a 0 into counter 0 (TCSR0), do the following:
        Xil_Out32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TLR0_OFFSET, 0x0000);//write a 0 into the TLR0 register.
        uint32_t read0 = Xil_In32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCSR0_OFFSET);//read value stored at TCSR0
        uint32_t newread0 = read0 | INTERVALTIMER_FIFTH_ON;// make the fifth bit (LOAD0) a 1
        Xil_Out32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, newread0);//write a 1 into the LOAD0 bit in the TCSR0.

        //To store a 0 into counter 1 (TCSR1), do the following:
        Xil_Out32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TLR1_OFFSET, 0x0000);//write a 0 into the TLR1 register.
        uint32_t read1 = Xil_In32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCSR1_OFFSET);//read value stored at TCSR1
        uint32_t newread1 = read1 | INTERVALTIMER_FIFTH_ON;// make the fifth bit (LOAD1) a 1
        Xil_Out32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCSR1_OFFSET, newread1);//write a 1 into the LOAD1 bit in the TCSR1
    }
    if(timerNumber == 1)
    {
        // to store a 0 into counter 0 (TCSR0), do the following:
        Xil_Out32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TLR0_OFFSET, 0x0000);//write a 0 into the TLR0 register.
        uint32_t read0 = Xil_In32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCSR0_OFFSET);//read value stored at TCSR0
        uint32_t newread0 = read0 | INTERVALTIMER_FIFTH_ON;// make the fifth bit (LOAD0) a 1
        Xil_Out32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, newread0);//write a 1 into the LOAD0 bit in the TCSR0.

        //To store a 0 into counter 1 (TCSR1), do the following:
        Xil_Out32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TLR1_OFFSET, 0x0000);//write a 0 into the TLR1 register.
        uint32_t read1 = Xil_In32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCSR1_OFFSET);//read value stored at TCSR1
        uint32_t newread1 = read1 | INTERVALTIMER_FIFTH_ON;// make the fifth bit (LOAD1) a 1
        Xil_Out32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCSR1_OFFSET, newread1);//write a 1 into the LOAD1 bit in the TCSR1
    }
    if(timerNumber == 2)
    {
        // to store a 0 into counter 0 (TCSR0), do the following:
        Xil_Out32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TLR0_OFFSET, 0x0000);//write a 0 into the TLR0 register.
        uint32_t read0 = Xil_In32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCSR0_OFFSET);//read value stored at TCSR0
        uint32_t newread0 = read0 | INTERVALTIMER_FIFTH_ON;// make the fifth bit (LOAD0) a 1
        Xil_Out32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCSR0_OFFSET, newread0);//write a 1 into the LOAD0 bit in the TCSR0.

        //To store a 0 into counter 1 (TCSR1), do the following:
        Xil_Out32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TLR1_OFFSET, 0x0000);//write a 0 into the TLR1 register.
        uint32_t read1 = Xil_In32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCSR1_OFFSET);//read value stored at TCSR1
        uint32_t newread1 = read1 | INTERVALTIMER_FIFTH_ON;// make the fifth bit (LOAD1) a 1
        Xil_Out32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCSR1_OFFSET, newread1);//write a 1 into the LOAD1 bit in the TCSR1
    }

    intervalTimer_init(timerNumber); // call the initialize function which clears TCSR0 and TCSR1 (especially to clear LOAD0 and LOAD1 bits)
}

//used to initialize all of the timer at once
uint32_t intervalTimer_initAll()
{
    for (int i=0; i<=2; i++)
    {
        intervalTimer_init(i);// calls each of the timers
    }
}

//used to reset all of the timers at the same time
uint32_t intervalTimer_resetAll()
{
    for (int i=0; i<=2; i++)
    {
        intervalTimer_reset(i);//calls each of the timers
    }
}

// runs a test to see if timers are operating correctly
uint32_t intervalTimer_runTest(uint32_t timerNumber)
{
    intervalTimer_init(timerNumber); //initialize the timer
    intervalTimer_reset(timerNumber); //reset the timer
    printf("timer_0 TCR0 should be 0 at this point:%ld\n\r", readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET)); // Show that the timer is reset.
    printf("timer_0 TCR1 should be 0 at this point:%ld\n\r", readTimerRegister(timerNumber, INTERVALTIMER_TCR1_OFFSET)); //reset the TCR1 as well as TCR0
    intervalTimer_start(timerNumber); // Show that the timer is running.
    printf("The following register values should be changing while reading them.\n\r"); //print statement to the screen
    printf("timer_0 TCR0 should be changing at this point:%ld\n\r", readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET)); //these print the current values of the timer
    printf("timer_0 TCR0 should be changing at this point:%ld\n\r", readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET)); //repeat multiple times to show that change is continuous as time passes
    printf("timer_0 TCR0 should be changing at this point:%ld\n\r", readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET));
    printf("timer_0 TCR0 should be changing at this point:%ld\n\r", readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET));
    printf("timer_0 TCR0 should be changing at this point:%ld\n\r", readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET));
    waitALongTime(); // Wait about 2 minutes so that you roll over to TCR1.
    printf("timer_0 TCR0 value after wait:%lx\n\r", readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET));// If you don't see a '1' in TCR1 after this long wait you probably haven't programmed the timer correctly.
    printf("timer_0 TCR1 should have changed at this point:%ld\n\r", readTimerRegister(timerNumber, INTERVALTIMER_TCR1_OFFSET));//this shows the time that has passed
}

//called by other functions to read the timer registers
u32 readTimerRegister(uint32_t timerNumber, uint32_t registerOffset)//passes in timer to be read and register offset
{
    if(timerNumber == 0)//timer 0
    {
        uint32_t address = INTERVALTIMER_TIMER_0_BASEADDR + registerOffset;// assign address to equal the base address plus the offset
        return Xil_In32(address); //return the  address
    }
    if(timerNumber == 1)//timer 1
    {
        uint32_t address = INTERVALTIMER_TIMER_1_BASEADDR + registerOffset;//// assign address to equal the base address plus the offset
        return Xil_In32(address); //return the  address
    }
    if(timerNumber == 2) //timer 2
    {
        uint32_t address = INTERVALTIMER_TIMER_2_BASEADDR + registerOffset;// assign address to equal the base address plus the offset
        return Xil_In32(address); //return the  address
    }
}

//called by test functions to allow time to pass for the timers to operate
void waitALongTime()//this is called in the runTest() and allows time to pass
{
    volatile int32_t a = 0;
    int32_t i, j;
    for (i=0; i<INTERVALTIMER_DELAY_COUNT; i++) //delay for loop to allow time to pass to show functioning timers
        for (j=0; j<INT32_MAX; j++)
            a++;
}

//tests all of the timers
uint32_t intervalTimer_testAll()//used to test all of the timers
{
    for (int i=0; i<=2; i++)
    {
        intervalTimer_runTest(i);//tests each timer using a for loop
    }
}

//used to obtain the duration for which the timers have run and returns that in seconds
uint32_t intervalTimer_getTotalDurationInSeconds(uint32_t timerNumber, double *seconds)//tests the timer functionality
{
    if (timerNumber == 0)
    {
        uint64_t read0 = Xil_In32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCR0_OFFSET);//read the value at the TCSR0 counter and put into 64 bits
        uint64_t read1 = Xil_In32(INTERVALTIMER_TIMER_0_BASEADDR + INTERVALTIMER_TCR1_OFFSET);// read the value at the TCSR1 counter and put into 64 bits
        uint64_t shiftread1 = read1 << INTERVALTIMER_SHIFT32;//bit shift TCR1 into upper 32 bits
        uint64_t sixtyfour = read0 | shiftread1 ;//put TCR0 and TCR1 together into a 64 bit number
        *seconds = ((double)sixtyfour/INTERVALTIMER_TIMER_0_CLOCK_FREQ_HZ);// divide 64 bit number by frequency //each tick represent 1/100 million seconds
    }

    if (timerNumber == 1)
    {
        uint64_t read0 = Xil_In32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCR0_OFFSET);//bit shift TCR1 into upper 32 bits
        uint32_t read1 = Xil_In32(INTERVALTIMER_TIMER_1_BASEADDR + INTERVALTIMER_TCR1_OFFSET);// read the value at the TCSR1 counter and put into 64 bits
        uint64_t shiftread1 = read1 << INTERVALTIMER_SHIFT32;//bit shift TCR1 into upper 32 bits
        uint64_t sixtyfour = read0 | shiftread1 ;//put TCR0 and TCR1 together into a 64 bit number
        *seconds = ((double)sixtyfour/INTERVALTIMER_TIMER_1_CLOCK_FREQ_HZ);// divide 64 bit number by frequency //each tick represent 1/100 million seconds
    }

    if (timerNumber == 2)
    {
        uint64_t read0 = Xil_In32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCR0_OFFSET);//bit shift TCR1 into upper 32 bits
        uint32_t read1 = Xil_In32(INTERVALTIMER_TIMER_2_BASEADDR + INTERVALTIMER_TCR1_OFFSET);// read the value at the TCSR1 counter and put into 64 bits
        uint64_t shiftread1 = read1 << INTERVALTIMER_SHIFT32;//bit shift TCR1 into upper 32 bits
        uint64_t sixtyfour = read0 | shiftread1 ;//put TCR0 and TCR1 together into a 64 bit number
        *seconds = ((double)sixtyfour/INTERVALTIMER_TIMER_2_CLOCK_FREQ_HZ);// divide 64 bit number by frequency //each tick represent 1/100 million seconds
    }
}





