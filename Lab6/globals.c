/*
 * globals.c
 *
 *  Created on: Oct 31, 2015
 *      Author: spence13
 */

#include "globals.h"

uint8_t mysequence[GLOBALS_MAX_FLASH_SEQUENCE];//create array to be manipulated manually
uint16_t iterationLength;//create iteration length to be manipulated locally
uint16_t sequenceLength;//create length to be manipulated locally

// This is the length of the complete sequence at maximum length.
// You must copy the contents of the sequence[] array into the global variable that you maintain.
// Do not just grab the pointer as this will fail.
void globals_setSequence(const uint8_t sequence[], uint16_t length)
{
    sequenceLength = length;//set your local sequence length to the value you passed in
    for(int i = 0; i < length; i++)//start at zero and go as long as the length is
    {
        mysequence[i] = sequence[i];//set your local array to the same values in the array you passed in
    }
}

// Retrieve the sequence length.
uint16_t globals_getSequenceLength()
{
    return sequenceLength;//this is how you access sequence length from other state machines
}

// This is the length of the sequence that you are currently working on.
void globals_setSequenceIterationLength(uint16_t length)
{
    iterationLength = length;//this is how you manipulate local iteration length variable from other SMs
}

// This is the length of the sequence that you are currently working on (not the maximum length but the interim length as
// the use works through the pattern one color at a time.
uint16_t globals_getSequenceIterationLength()
{
    return iterationLength;//this is how you access iteration length value from other SMs
}

// This returns the value of the sequence at the index.
uint8_t globals_getSequenceValue(uint16_t index)
{
    return mysequence[index];// this is how you access the values in the array from other SMs
}
