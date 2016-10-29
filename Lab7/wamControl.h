/*
 * wamControl.h
 *
 *  Created on: Nov 23, 2015
 *      Author: spence13
 */

#ifndef WAMCONTROL_H_
#define WAMCONTROL_H_

#include "wamDisplay.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WAMCONTROL_TIMER_EXPIREDVALUE 2//max value of the adc timer
#define WAMCONTROL_RAND_NUM_TWENTYONE 21//center of the random number generator
#define WAMCONTROL_RAND_NUM_LIMIT 10//creates an upper bound for random numbers
#define WAMCONTROL_MAXMISS 5//max number of misses
#define WAMCONTROL_MAX_MOLE 1 //if you want the max moles to be one

// Call this before using any wamControl_ functions.
void wamControl_init();

// Call this to set how much time is consumed by each tick of the controlling state machine.
// This information makes it possible to set the awake and sleep time of moles in ms, not ticks.
void wamControl_setMsPerTick(uint16_t msPerTick);

// This returns the time consumed by each tick of the controlling state machine.
uint16_t wamControl_getMsPerTick();

// Standard tick function.
void wamControl_tick();

// Returns a random value that indicates how long the mole should sleep before awaking.
wamDisplay_moleTickCount_t wamControl_getRandomMoleAsleepInterval();

// Returns a random value that indicates how long the mole should stay awake before going dormant.
wamDisplay_moleTickCount_t wamControl_getRandomMoleAwakeInterval();

// Set the maximum number of active moles.
void wamControl_setMaxActiveMoles(uint16_t count);

// Get the current allowable count of active moles.
uint16_t wamControl_getMaxActiveMoles();

// Set the seed for the random-number generator.
void wamControl_setRandomSeed(uint32_t seed);

// Set the maximum number of misses until the game is over.
void wamControl_setMaxMissCount(uint16_t missCount);

// Use this predicate to see if the game is finished.
bool wamControl_isGameOver();

// Set the upper limit of the random number generator for intervals
void wamControl_decrementRandNumLimit();

#endif /* WAMCONTROL_H_ */


