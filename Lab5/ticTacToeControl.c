/*
 * ticTacToeControl.c
 *
 *  Created on: Oct 19, 2015
 *      Author: spence13
 */

#include "ticTacToeControl.h"
#include "src/lab3/intervalTimer.h"


uint32_t gameOverTimer = 0;//deals with waiting for ADC to settle
uint32_t decideGameTimer = 0;//deals with waiting .5 seconds before going to fast mode
bool you_are_X = true;//used to set if you are X or O
minimax_board_t board;//keeps track of moves in which squares
uint8_t row, column; //row and columns used in board
uint8_t moveNumber = 0; //keeps track of how many moves have been made

// States for the controller state machine.
enum Timer_States
{
    init_st,// Start here, stay in this state for just one tick.
    waiting_for_touch_st, // waiting for touch, clock is enabled and running.
    decide_game_st,// waiting for the touch-controller ADC to settle.
    display_my_move_st,// waiting for the auto-update delay to expire
    compute_computer_move_st, // waiting for the rate-timer to expire to know when to perform the auto inc/dec.
    display_computer_move_st,// when the rate-timer expires, perform the inc/dec function.
    game_over_st // keep time like normal timer
}
currentState = init_st;

//this function will hold the state machines with their associated transitions and actions
void ticTacToeControl_tick()
{
    switch(currentState)// actions
    {
    case init_st:  // Initial transition
        moveNumber = 0; //reset the number of moves to zero
        ticTacToeDisplay_eraseBoardLines(); //erase the lines on the board
        for(int i = 0; i<3 ; i++)//erase O and X in every square
        {
            for(int j = 0; j < 3; j++)
            {
                ticTacToeDisplay_eraseO(i, j);//draw black O
                ticTacToeDisplay_eraseX(i, j);//draw black X
            }
        }
        break;

    case decide_game_st:
        decideGameTimer++; //increase the adTimer by one
        break;

    case waiting_for_touch_st:
        //reset all timers;
        gameOverTimer = 0;
        decideGameTimer = 0;
        break;

    case display_my_move_st:
        moveNumber++;//increment number of moves by one
        ticTacToeDisplay_touchScreenComputeBoardRowColumn(&row, &column);//call function to compute location of move
        if(you_are_X == true)
        {
            ticTacToeDisplay_drawX(row, column);//draw an X
            board.squares[row][column] = MINIMAX_OPPONENT_SQUARE;//update board with most recent move
        }
        else
        {
            ticTacToeDisplay_drawO(row, column);//draw an O
            board.squares[row][column] = MINIMAX_OPPONENT_SQUARE;//update board with most recent move
        }
        break;

    case compute_computer_move_st:
        //make sure the second move is in center
        if((moveNumber == TICTACTOECONTROL_FIRST_MOVE || moveNumber == TICTACTOECONTROL_SECOND_MOVE) && board.squares[1][1] == MINIMAX_EMPTY_SQUARE)
        {
            row = TICTACTOECONTROL_CENTER_SQUARE;//set row equal to one
            column = TICTACTOECONTROL_CENTER_SQUARE;//set column equal to one
        }
        else
        {
            minimax_computeNextMove(&board, false, &row, &column); //call the recursion otherwise
        }
        break;

    case display_computer_move_st:
        moveNumber++;//increment number of moves by one
        if(you_are_X == true)
        {
            ticTacToeDisplay_drawO(row, column);//draw an O
            board.squares[row][column] = MINIMAX_PLAYER_SQUARE;//update board with most recent move
        }
        else
        {
            ticTacToeDisplay_drawX(row, column);//draw an X
            board.squares[row][column] = MINIMAX_PLAYER_SQUARE;//update board with most recent move
        }
        break;

    case game_over_st:
        gameOverTimer++;//increase the secTimer by one
        break;

    default:
        currentState = init_st; //default state is init
        break;
    }// actions


    switch(currentState)// Transitions
    {
    case init_st:  // Initial transition
        display_setTextColor(TICTACTOEDISPLAY_GREEN);//set text color to green
        display_setCursor(TICTACTOEDISPLAY_HALF_WIDTH - TICTACTOEDISPLAY_ONE_THIRD_WIDTH, //position x coordinate of cursor
                          TICTACTOEDISPLAY_HALF_HEIGHT - TICTACTOEDISPLAY_ONE_SIXTH_HEIGHT);//position y coordinate of cursor
        display_println("Touch Board to play X\n\r");//print to the lcd
        display_println("--or--\n\r");//print to the lcd
        display_println("wait for the computer and play O\n\r");//print to the lcd
        currentState = decide_game_st;  //automatically go to waiting state
        break;

    case decide_game_st:
        if(decideGameTimer == TICTACTOECONTROL_DECIDE_GAME_EXPIRED_VALUE)
        {
            display_setTextColor(TICTACTOEDISPLAY_BLACK);//set text color to black
            display_setCursor(TICTACTOEDISPLAY_HALF_WIDTH - TICTACTOEDISPLAY_ONE_THIRD_WIDTH, //position x coordinate of cursor
                              TICTACTOEDISPLAY_HALF_HEIGHT - TICTACTOEDISPLAY_ONE_SIXTH_HEIGHT);//position y coordinate of cursor
            display_println("Touch Board to play X\n\r");//print to the lcd
            display_println("--or--\n\r");//print to the lcd
            display_println("wait for the computer and play O\n\r");//print to the lcd

            ticTacToeDisplay_drawBoardLines();//draw the board lines
            minimax_initBoard(&board);//initialize the board to all zeros
            you_are_X = false;//this makes you the O player
            moveNumber++;//increment number of moves by one
            ticTacToeDisplay_drawX(0, 0);//hardcode the first move to be in the top left corner
            board.squares[0][0] = MINIMAX_PLAYER_SQUARE; //to shorten processing time
            currentState = waiting_for_touch_st;//stay in waiting state
        }
        else if(display_isTouched())
        {
            display_setTextColor(TICTACTOEDISPLAY_BLACK);//set text color to black
            display_setCursor(TICTACTOEDISPLAY_HALF_WIDTH - TICTACTOEDISPLAY_ONE_THIRD_WIDTH, //position x coordinate of cursor
                              TICTACTOEDISPLAY_HALF_HEIGHT - TICTACTOEDISPLAY_ONE_SIXTH_HEIGHT);//position y coordinate of cursor
            display_println("Touch Board to play X\n\r");//print to the lcd
            display_println("--or--\n\r");//print to the lcd
            display_println("wait for the computer and play O\n\r");//print to the lcd

            ticTacToeDisplay_drawBoardLines();//draw the board lines
            display_clearOldTouchData();//clear old touch data
            minimax_initBoard(&board);//initialize the board to all zeros
            you_are_X = true;//this makes you the X player
            currentState = waiting_for_touch_st;//stay in waiting state
        }
        else if(buttons_read() == (TICTACTOEDISPLAY_BTN1_ON))
        {
            currentState = init_st;//if BTN is pressed reset the game
        }
        else
        {
            currentState = decide_game_st; //default is to remain in decide_game_st
        }
        break;

    case waiting_for_touch_st:
        if(display_isTouched())
        {
            display_clearOldTouchData();//clear old touch data
            ticTacToeDisplay_touchScreenComputeBoardRowColumn(&row, &column);//compute location of touch
            if(board.squares[row][column] != MINIMAX_EMPTY_SQUARE)
            {
                currentState = waiting_for_touch_st;//if square is used dont make move
            }
            else
            {
                currentState = display_my_move_st;//default to stay
            }
        }
        else if(minimax_didPlayerWin(&board, true) != MINIMAX_NOT_ENDGAME)//minimax_didPlayerWin(&board, true))
        {
            display_setTextColor(TICTACTOEDISPLAY_GREEN);//set text color to green
            display_setCursor(TICTACTOEDISPLAY_HALF_WIDTH - TICTACTOEDISPLAY_ONE_THIRD_WIDTH, //position x coordinate of cursor
                              TICTACTOEDISPLAY_HALF_HEIGHT - TICTACTOEDISPLAY_ONE_SIXTH_HEIGHT);//position y coordinate of cursor
            display_println("Game Over!");//print to the lcd
            currentState = game_over_st;
        }
        else if(buttons_read() == (TICTACTOEDISPLAY_BTN1_ON))
        {
            currentState = init_st;//if BTN is pressed reset the game
        }
        else
        {
            currentState = waiting_for_touch_st; //default stay in waiting state
        }
        break;

    case display_my_move_st:
        if(minimax_didPlayerWin(&board, true) != MINIMAX_NOT_ENDGAME)//minimax_didPlayerWin(&board, true))
        {
            display_setTextColor(TICTACTOEDISPLAY_GREEN);//set text color to green
            display_setCursor(TICTACTOEDISPLAY_HALF_WIDTH - TICTACTOEDISPLAY_ONE_THIRD_WIDTH, //position x coordinate of cursor
                              TICTACTOEDISPLAY_HALF_HEIGHT - TICTACTOEDISPLAY_ONE_SIXTH_HEIGHT);//position y coordinate of cursor
            display_println("Game Over!");//print to the lcd
            currentState = game_over_st;
        }
        else if(buttons_read() == (TICTACTOEDISPLAY_BTN1_ON))
        {
            currentState = init_st;//if BTN is pressed reset the game
        }
        else
        {
            currentState = compute_computer_move_st;//default to stay
        }
        break;

    case compute_computer_move_st:
        if(buttons_read() == (TICTACTOEDISPLAY_BTN1_ON))
        {
            currentState = init_st;//if BTN is pressed reset the game
        }
        else
        {
            currentState = display_computer_move_st;//default to stay
        }
        break;

    case display_computer_move_st:
        if(buttons_read() == (TICTACTOEDISPLAY_BTN1_ON))
        {
            currentState = init_st;//if BTN is pressed reset the game
        }
        else
        {
            currentState = waiting_for_touch_st;//default to stay
        }
        break;

    case game_over_st:
        if(gameOverTimer == TICTACTOECONTROL_GAME_OVER_EXPIRED_VALUE)
        {
            display_setTextColor(TICTACTOEDISPLAY_BLACK);//set text color to black
            display_setCursor(TICTACTOEDISPLAY_HALF_WIDTH - TICTACTOEDISPLAY_ONE_THIRD_WIDTH, //position x coordinate of cursor
                              TICTACTOEDISPLAY_HALF_HEIGHT - TICTACTOEDISPLAY_ONE_SIXTH_HEIGHT);//position y coordinate of cursor
            display_println("Game Over!");//print to the lcd
            currentState = init_st;//return to init state at end of game
        }
        else
        {
            currentState = game_over_st;//default is to stay in rate timer expired state
        }
        break;

    default:
        currentState = init_st;//set the default state to init
        break;
    }// Transitions
}
