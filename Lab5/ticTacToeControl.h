/*
 * ticTacToeControl.h
 *
 *  Created on: Oct 19, 2015
 *      Author: spence13
 */

#ifndef TICTACTOECONTROL_H_
#define TICTACTOECONTROL_H_


#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "supportFiles/utils.h"
#include "supportFiles/display.h"
#include "minimax.h"
#include "ticTacToeDisplay.h"

//controls the duration of certain states
#define TICTACTOECONTROL_DECIDE_GAME_EXPIRED_VALUE 50
#define TICTACTOECONTROL_GAME_OVER_EXPIRED_VALUE 50

#define TICTACTOECONTROL_CENTER_SQUARE 1
#define TICTACTOECONTROL_FIRST_MOVE 1
#define TICTACTOECONTROL_SECOND_MOVE 2

//this tick function is used for state machines and their transitions
void ticTacToeControl_tick();

#endif /* TICTACTOECONTROL_H_ */
