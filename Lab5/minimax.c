/*
 * minimax.c
 *
 *  Created on: Oct 13, 2015
 *      Author: spence13
 */

#include "minimax.h"

//global variables
minimax_move_t choice;//contain the move you care about - the move associated with the highest score (assuming that you are the player).
uint16_t depth = 0;//keeps track of depth


void minimax_initBoard(minimax_board_t* board)
{
    for(int row = 0; row < 3; row++)//iterate through rows
    {
        for(int column = 0; column < 3; column++)//iterate through columns
        {
            board->squares[row][column] = MINIMAX_EMPTY_SQUARE; //set a zero in each of the positions in squares array meaning the square is empty (no X or O)
        }
    }
}

void minimax_computeNextMove(minimax_board_t* board, bool player, uint8_t* row, uint8_t* column)
{
    minimax_computeBoardScore(board, player);//make the recursive call
    *row = choice.row;//set pointer equal to choice of row
    *column = choice.column;//set pointer equal to choice of column
}

bool minimax_isGameOver(minimax_score_t score)
{
    if (score != MINIMAX_NOT_ENDGAME)//if the game has ended
    {
        return true;
    }
    else
    {
        return false;
    }
}

//this is the recursive function
int16_t minimax_computeBoardScore(minimax_board_t* board, bool player)
{
    minimax_move_t move[9] = { };//array filled with move positions (row, column)
    minimax_score_t score[9] = { }; //array filled with scores
    int16_t arraypos = 0;
    depth++; //increment depth everytime recursion is called
    for(int row = 0; row < 3; row++)//iterate through rows
    {
        for(int column = 0; column < 3; column++)//iterate through columns
        {
            if (board->squares[row][column] == MINIMAX_EMPTY_SQUARE)//if the square is empty
            {
                if(player)
                {
                    board->squares[row][column] = MINIMAX_PLAYER_SQUARE;//assign square to player
                    if(minimax_didPlayerWin(board, player) == MINIMAX_PLAYER_WINNING_SCORE)//CHECK THE BASE CASE
                    {
                        board->squares[row][column] = MINIMAX_EMPTY_SQUARE;// Undo the change to the board (return the square to empty) prior to next iteration of for-loops.
                        score[arraypos] = MINIMAX_PLAYER_WINNING_SCORE - depth;//assign position in score array to equal winning score
                        move[arraypos].column = column;//assign position in move array to equal column of winning move
                        move[arraypos].row = row;//assign position in move array to equal row of winning move
                    }
                    else if(minimax_didPlayerWin(board, player) == MINIMAX_DRAW_SCORE)//CHECK THE BASE CASE
                    {
                        board->squares[row][column] = MINIMAX_EMPTY_SQUARE;// Undo the change to the board (return the square to empty) prior to next iteration of for-loops.
                        score[arraypos] = MINIMAX_DRAW_SCORE;//assign position in score array to equal draw score
                        move[arraypos].column = column;//assign position in move array to equal column of draw move
                        move[arraypos].row = row;//assign position in move array to equal row of draw move
                    }
                    else
                    {
                        score[arraypos] = minimax_computeBoardScore(board, !player); //RECURSIVE CALL
                        move[arraypos].column = column;
                        move[arraypos].row = row;
                    }
                }

                else//!player
                {
                    board->squares[row][column] = MINIMAX_OPPONENT_SQUARE;//assign square to opponent
                    if(minimax_didPlayerWin(board, player) == MINIMAX_OPPONENT_WINNING_SCORE)//CHECK THE BASE CASE
                    {
                        board->squares[row][column] = MINIMAX_EMPTY_SQUARE;// Undo the change to the board (return the square to empty) prior to next iteration of for-loops.
                        score[arraypos] = MINIMAX_OPPONENT_WINNING_SCORE + depth;//assign position in score array to equal winning score
                        move[arraypos].column = column;//assign position in move array to equal column of winning move
                        move[arraypos].row = row;//assign position in move array to equal row of winning move
                    }
                    else if(minimax_didPlayerWin(board, player) == MINIMAX_DRAW_SCORE)//CHECK THE BASE CASE
                    {
                        board->squares[row][column] = MINIMAX_EMPTY_SQUARE;// Undo the change to the board (return the square to empty) prior to next iteration of for-loops.
                        score[arraypos] = MINIMAX_DRAW_SCORE;//assign position in score array to equal draw score
                        move[arraypos].column = column;//assign position in move array to equal column of draw move
                        move[arraypos].row = row;//assign position in move array to equal row of draw move
                    }
                    else
                    {
                        score[arraypos] = minimax_computeBoardScore(board, !player); //RECURSIVE CALL
                        move[arraypos].column = column;
                        move[arraypos].row = row;
                    }
                }
                board->squares[row][column] = MINIMAX_EMPTY_SQUARE;// Undo the change to the board (return the square to empty) after coming out of recursion
                arraypos++;//increment position in array by one
            }
        }
    }

    int16_t skor_tobe_passed = 0;

    if(player)
    {
        int16_t highest_score = 0;//default is a draw score if no one wins
        int16_t pos = 0;//remember position of highest score
        for(int i = 0; i < 9; i++)//iterate through score array
        {
            if( score[i] > highest_score)
            {
                highest_score = score[i] ;//keep lowest score
                pos = i; //remember index of highest score
            }
        }
        choice.row = move[pos].row; //move that matches highest score
        choice.column = move[pos].column; //move that matches highest score
        skor_tobe_passed = highest_score; //save score
    }

    else
    {
        int16_t lowest_score = 0;//default is a draw score if no one wins
        int16_t pos = 0;//remember position of highest score
        for(int i = 0; i < 9; i++)//iterate through score array
        {
            if( score[i] < lowest_score)
            {
                lowest_score = score[i];//keep lowest score
                pos = i;//remember index of lowest score
            }
        }
        choice.row = move[pos].row;//move that matches lowest score
        choice.column = move[pos].column;//move that matches lowest score
        skor_tobe_passed = lowest_score;//save score
    }
    depth--;//decrease depth by one as you go out
    return skor_tobe_passed;
}

//return 10 if player won, -10 if opponent won, -1 if nobody has won yet
int16_t minimax_didPlayerWin(minimax_board_t* board, bool player)
{
    //check to see the horizontals
    int16_t horizontal = 0;//keep track of horizontal moves
    for(int row = 0; row < 3; row++)//iterate through rows
    {
        for(int column = 0; column < 3; column++)//iterate through columns
        {
            if(board->squares[row][column] == MINIMAX_PLAYER_SQUARE)//if occupied by player
            {
                horizontal++;//increment horizontal
            }
            if(board->squares[row][column] == MINIMAX_OPPONENT_SQUARE)//if occupied by opponent
            {
                horizontal--;//decrement horizontal
            }

        }
        if(horizontal == 3)//if the player has won
        {
            return MINIMAX_PLAYER_WINNING_SCORE;
        }
        if(horizontal == -3)//if the opponent won
        {
            return MINIMAX_OPPONENT_WINNING_SCORE;
        }
        horizontal = 0;
    }

    //check to see the verticals
    int16_t vertical = 0;
    for(int column = 0; column < 3; column++)//iterate through columns
    {
        for(int row = 0; row < 3; row++)//iterate through rows
        {
            if(board->squares[row][column] == MINIMAX_PLAYER_SQUARE)//if occupied by player
            {
                vertical++;//increment vertical
            }
            if(board->squares[row][column] == MINIMAX_OPPONENT_SQUARE)//if occupied by opponent
            {
                vertical--;//decrement vertical
            }
        }
        if(vertical == 3)//if the player has won
        {
            return MINIMAX_PLAYER_WINNING_SCORE;
        }
        if(vertical == -3)//if the opponent won
        {
            return MINIMAX_OPPONENT_WINNING_SCORE;
        }
        vertical = 0;
    }

    //check to see first diagonal
    int16_t diagonal = 0;
    for(int i = 0; i < 3; i++)
    {
        if(board->squares[i][i] == MINIMAX_PLAYER_SQUARE)//if occupied by player
        {
            diagonal++;//increment diagonal
        }
        if(board->squares[i][i] == MINIMAX_OPPONENT_SQUARE)//if occupied by opponent
        {
            diagonal--;//increment diagonal
        }
    }

    if(diagonal == 3)//if player won
    {
        return MINIMAX_PLAYER_WINNING_SCORE;
    }
    if(diagonal == -3)//if opponent won
    {
        return MINIMAX_OPPONENT_WINNING_SCORE;
    }

    diagonal = 0;//reset variable
    //check to see second diagonal
    int16_t j = 0;
    for(int i = 2; i >= 0; i--)
    {
        if(board->squares[j][i] == MINIMAX_PLAYER_SQUARE)//if occupied by player
        {
            diagonal++;//increment diagonal
        }
        if(board->squares[j][i] == MINIMAX_OPPONENT_SQUARE)//if occupied by opponent
        {
            diagonal--;//increment diagonal
        }
        j++;
    }

    if(diagonal == 3)//if player won
    {
        return MINIMAX_PLAYER_WINNING_SCORE;
    }
    if(diagonal == -3)//if opponent won
    {
        return MINIMAX_OPPONENT_WINNING_SCORE;
    }
    diagonal = 0;

    int16_t numberofMoves = 0;//keep track of how many moves
    for(int row = 0; row < 3; row++)//iterate through rows
    {
        for(int column = 0; column < 3; column++)//iterate through columns
        {
            if(board->squares[row][column] != MINIMAX_EMPTY_SQUARE)//if square is occupied
            {
                numberofMoves++;//increment the number of moves by one
            }
        }
    }

    if(numberofMoves == 9)// this means all squares have been taken
    {
        return MINIMAX_DRAW_SCORE;//if game is over and it is a tie
    }
    else
    {
        return MINIMAX_NOT_ENDGAME; //if game is not yet over and no one has won
    }
}












