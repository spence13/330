/*
 * wamDisplay.c
 *
 *  Created on: Nov 23, 2015
 *      Author: spence13
 */


#include "wamDisplay.h"
#include "wamControl.h"

uint32_t curr_hits = 0; //initialize running tally of hits to zero
uint32_t curr_misses = 0;//initialize running tally of misses to zero
uint32_t level = 0;//initialize running tally of level to zero
uint8_t board_size = 0;//initalize board size to zero
uint8_t runtest = WAMDISPLAY_RUN_TEST_ONE_LOOP;//initalize runtest variable to be used for milestone one
char print_hits[WAMDISPLAY_CHAR_LENGTH];//initalize length of array of characters used to print hits
char print_misses[WAMDISPLAY_CHAR_LENGTH];//initalize length of array of characters used to print misses
char print_level[WAMDISPLAY_CHAR_LENGTH];//initalize length of array of characters used to print level
char print_prev_hits[WAMDISPLAY_CHAR_LENGTH];//initalize length of array of characters used to print prev_hits
char print_prev_misses[WAMDISPLAY_CHAR_LENGTH];//initalize length of array of characters used to print prev_misses
char print_prev_level[WAMDISPLAY_CHAR_LENGTH];//initalize length of array of characters used to print prev_level

/********************** typedefs **********************/
// This keeps track of all mole information.
typedef struct
{
    wamDisplay_point_t origin;  // This is the origin of the hole for this mole.
    // A mole is active if either of the tick counts are non-zero. The mole is dormant otherwise.
    // During operation, non-zero tick counts are decremented at a regular rate by the control state machine.
    // The mole remains in his hole until ticksUntilAwake decrements to zero and then he pops out.
    // The mole remains popped out of his hole until ticksUntilDormant decrements to zero.
    // Once ticksUntilDomant goes to zero, the mole hides in his hole and remains dormant until activated again.
    wamDisplay_moleTickCount_t ticksUntilAwake;  // Mole will wake up (pop out of hole) when this goes from 1 -> 0.
    wamDisplay_moleTickCount_t ticksUntilDormant; // Mole will go dormant (back in hole) this goes 1 -> 0.
} wamDisplay_moleInfo_t;

// This will contain pointers to all of the mole info records.
// This will ultimately be treated as an array of pointers.
static wamDisplay_moleInfo_t** wamDisplay_moleInfo;

// Allocates the memory for wamDisplay_moleInfo_t records.
// Computes the origin for each mole assuming a simple row-column layout:
// 9 moles: 3 rows, 3 columns, 6 moles: 2 rows, 3 columns, 4 moles: 2 rows, 2 columns
// Also inits the tick counts for awake and dormant.
void wamDisplay_computeMoleInfo()
{
    // Setup all of the moles, creates and inits mole info records.
    // Create the container array. It contains pointers to each of the mole-hole info records.
    wamDisplay_moleInfo = (wamDisplay_moleInfo_t**) malloc(board_size * sizeof(wamDisplay_moleInfo_t*)); // makes one for each mole
    for (uint16_t i=0; i<board_size; i++)//loop through all moles of the board size
    {
        wamDisplay_moleInfo[i] = (wamDisplay_moleInfo_t*) malloc(sizeof(wamDisplay_moleInfo_t));//makes origin, #ticksAwake, #ticksDormant for each mole
        wamDisplay_moleInfo[i]->ticksUntilAwake = 0;//initialize ticks until awake to zero for every mole
        wamDisplay_moleInfo[i]->ticksUntilDormant = 0;//initialize ticks until dormant to zero for every mole
    }
    uint16_t i = 0;//create a variable to increment thru all moles
    if(board_size == WAMDISPLAY_BOARD_SIZE_NINE)//check to see what the board size is
    {
        for (uint16_t row=WAMDISPLAY_BOARD_ROW_ONE; row<=WAMDISPLAY_BOARD_ROW_THREE; row++)//move through all moles in the row
        {
            for(uint16_t col=WAMDISPLAY_BOARD_COL_ONE; col<=WAMDISPLAY_BOARD_COL_THREE; col++)//move through all moles in the col
            {
                wamDisplay_moleInfo[i]->origin.x = col;//set the x origin equal to the col number as you move thru the cols
                wamDisplay_moleInfo[i]->origin.y = row;//set the y origin equal to the row number as you move thru the rows
                i++;//move thru the array by one to initialize all the moles
            }
        }
    }
    else if(board_size == WAMDISPLAY_BOARD_SIZE_SIX)//check to see what the board size is
    {
        for (uint16_t row=WAMDISPLAY_BOARD_ROW_ONE; row<=WAMDISPLAY_BOARD_ROW_THREE; row+=WAMDISPLAY_BOARD_ROW_TWO)//move through all moles in the row
        {
            for(uint16_t col=WAMDISPLAY_BOARD_COL_ONE; col<=WAMDISPLAY_BOARD_COL_THREE; col++)//move through all moles in the col
            {
                wamDisplay_moleInfo[i]->origin.x = col;//set the x origin equal to the col number as you move thru the cols
                wamDisplay_moleInfo[i]->origin.y = row;//set the y origin equal to the row number as you move thru the rows
                i++;//move thru the array by one to initialize all the moles
            }
        }
    }
    else if(board_size == WAMDISPLAY_BOARD_SIZE_FOUR)//check to see what the board size is
    {
        for (uint16_t row=WAMDISPLAY_BOARD_ROW_ONE; row<=WAMDISPLAY_BOARD_ROW_THREE; row+=WAMDISPLAY_BOARD_ROW_TWO)//move through all moles in the row
        {
            for(uint16_t col=WAMDISPLAY_BOARD_COL_ONE; col<=WAMDISPLAY_BOARD_COL_THREE; col+=WAMDISPLAY_BOARD_COL_TWO)//move through all moles in the col
            {
                wamDisplay_moleInfo[i]->origin.x = col;//set the x origin equal to the col number as you move thru the cols
                wamDisplay_moleInfo[i]->origin.y = row;//set the y origin equal to the row number as you move thru the rows
                i++;//move thru the array by one to initialize all the moles
            }
        }
    }
}

// Provide support to set games with varying numbers of moles. This function
// would be called prior to calling wamDisplay_init();
void wamDisplay_selectMoleCount(wamDisplay_moleCount_e moleCount)
{
    if(moleCount == wamDisplay_moleCount_9)//if mole switches equals nine
    {
        board_size = WAMDISPLAY_BOARD_SIZE_NINE;//set board size equal to nine
    }
    else if(moleCount == wamDisplay_moleCount_6)//if mole switches equals six
    {
        board_size = WAMDISPLAY_BOARD_SIZE_SIX;//set board size equal to six
    }
    else if(moleCount == wamDisplay_moleCount_4)//if mole switches equals four
    {
        board_size = WAMDISPLAY_BOARD_SIZE_FOUR;//set board size equal to four
    }
    else//default mole count equals 9
    {
        board_size = WAMDISPLAY_BOARD_SIZE_NINE;//set board size equal to nine
    }
}

// Call this before using any wamDisplay_ functions.
void wamDisplay_init()
{
    wamDisplay_computeMoleInfo();//create all moles
}

// Draw the game display with a background and mole holes.
void wamDisplay_drawMoleBoard()
{
    display_fillScreen(WAMDISPLAY_BLACK);//blank the screen with black
    display_fillRect(WAMDISPLAY_BACKGROUND_OFFSET, WAMDISPLAY_BACKGROUND_OFFSET, WAMDISPLAY_PIXEL_WIDTH - WAMDISPLAY_BACKGROUND_OFFSET_DOUBLE, WAMDISPLAY_PIXEL_HEIGHT - WAMDISPLAY_BACKGROUND_OFFSET_QUADRUPLE, WAMDISPLAY_GREEN);//draw a green rectangle for the board
    if(board_size == WAMDISPLAY_BOARD_SIZE_NINE)//check to see what the board size is
    {
        for(uint16_t row = WAMDISPLAY_BOARD_ROW_ONE; row <= WAMDISPLAY_BOARD_ROW_THREE; row++)//iterate through all the rows depending on board size
        {
            for(uint16_t col = WAMDISPLAY_BOARD_COL_ONE; col <= WAMDISPLAY_BOARD_COL_THREE; col++)//iterate through all the cols depending on board size
            {
                display_fillCircle(WAMDISPLAY_HOLE_XPOS_ONE*col, WAMDISPLAY_HOLE_YPOS_ONE*row - WAMDISPLAY_BACKGROUND_OFFSET, WAMDISPLAY_HOLE_RADIUS, WAMDISPLAY_BLACK);//draw a black circle for a hole at the (row, col) coordinate
            }
        }
    }
    else if(board_size == WAMDISPLAY_BOARD_SIZE_SIX)//check to see what the board size is
    {
        for(uint16_t row = WAMDISPLAY_BOARD_ROW_ONE; row <= WAMDISPLAY_BOARD_ROW_THREE; row+=WAMDISPLAY_BOARD_ROW_TWO)//iterate through all the rows depending on board size
        {
            for(uint16_t col = WAMDISPLAY_BOARD_COL_ONE; col <= WAMDISPLAY_BOARD_COL_THREE; col++)//iterate through all the cols depending on board size
            {
                display_fillCircle(WAMDISPLAY_HOLE_XPOS_ONE*col, WAMDISPLAY_HOLE_YPOS_ONE*row - WAMDISPLAY_BACKGROUND_OFFSET, WAMDISPLAY_HOLE_RADIUS, WAMDISPLAY_BLACK);//draw a black circle for a hole at the (row, col) coordinate
            }
        }
    }
    else if(board_size == WAMDISPLAY_BOARD_SIZE_FOUR)//check to see what the board size is
    {
        for(uint16_t row = WAMDISPLAY_BOARD_ROW_ONE; row <= WAMDISPLAY_BOARD_ROW_THREE; row+=WAMDISPLAY_BOARD_ROW_TWO)//iterate through all the rows depending on board size
        {
            for(uint16_t col = WAMDISPLAY_BOARD_COL_ONE; col <= WAMDISPLAY_BOARD_COL_THREE; col+=WAMDISPLAY_BOARD_COL_TWO)//iterate through all the cols depending on board size
            {
                display_fillCircle(WAMDISPLAY_HOLE_XPOS_ONE*col, WAMDISPLAY_HOLE_YPOS_ONE*row - WAMDISPLAY_BACKGROUND_OFFSET, WAMDISPLAY_HOLE_RADIUS, WAMDISPLAY_BLACK);//draw a black circle for a hole at the (row, col) coordinate
            }
        }
    }
    display_setTextColor(WAMDISPLAY_WHITE);//Make the text green.
    display_setCursor(0, WAMDISPLAY_PIXEL_HEIGHT - WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_HEIGHT);//set the cursor position for printing score board
    display_setTextSize(WAMDISPLAY_TEXT_SIZE_TWO);//set the text size to two
    display_print(WAMDISPLAY_SCORE_BOARD);//print touch to start to the screen
}

// Draw the initial splash (instruction) screen.
void wamDisplay_drawSplashScreen()
{
    display_fillScreen(WAMDISPLAY_BLACK);//blank the screen with black
    display_setTextColor(WAMDISPLAY_WHITE);//Make the text green.
    display_setCursor(0, WAMDISPLAY_THIRD_PIXEL_HEIGHT);//set the cursor position
    display_setTextSize(WAMDISPLAY_TEXT_SIZE_FOUR);//set the text size to four
    display_println(WAMDISPLAY_WAC_START_SCREEN);//print touch to start to the screen
    display_setTextSize(WAMDISPLAY_TEXT_SIZE_TWO);//set the text size to two
    display_println(WAMDISPLAY_WAC_START_TOUCH);//print touch to start to the screen
}

// Draw the game-over screen.
void wamDisplay_drawGameOverScreen()
{
    display_fillScreen(WAMDISPLAY_BLACK);//blank the screen with black
    display_setTextColor(WAMDISPLAY_WHITE);//Make the text green.
    display_setCursor(WAMDISPLAY_FIFTH_PIXEL_WIDTH, WAMDISPLAY_THIRD_PIXEL_HEIGHT);//set the cursor position
    display_setTextSize(WAMDISPLAY_TEXT_SIZE_FOUR);//set the text size to four
    display_println(WAMDISPLAY_GAME_OVER_SCREEN);//print touch to start to the screen
    display_setTextSize(WAMDISPLAY_TEXT_SIZE_TWO);//set the text size to two
    sprintf(print_hits, "%d", curr_hits);//print the display numbers to an array
    sprintf(print_misses, "%d", curr_misses);//print the display numbers to an array
    sprintf(print_level, "%d", level);//print the display numbers to an array
    display_print(WAMDISPLAY_GAME_OVER_HITS);//print number of hits to the screen
    display_println(print_hits);//print touch to start to the screen
    display_print(WAMDISPLAY_GAME_OVER_MISSES);//print touch to start to the screen
    display_println(print_misses);//print touch to start to the screen
    display_print(WAMDISPLAY_GAME_OVER_LEVEL);//print touch to start to the screen
    display_println(print_level);//print touch to start to the screen
    display_println(WAMDISPLAY_GAME_OVER_RETOUCH);//print touch to start to the screen
}

// Selects a random mole and activates it.
// Activating a mole means that the ticksUntilAwake and ticksUntilDormant counts are initialized.
// See the comments for wamDisplay_moleInfo_t for details.
// Returns true if a mole was successfully activated. False otherwise. You can
// use the return value for error checking as this function should always be successful
// unless you have a bug somewhere.
bool wamDisplay_activateRandomMole()
{
    bool active = false;//create a bool variable to keep track of if you've activated a mole
    while (active == false)//keep going until you succesfully activate a mole
    {
        uint32_t index = rand() % board_size;//create a random number to find moles position
        if (wamDisplay_moleInfo[index]->ticksUntilDormant == 0 && wamDisplay_moleInfo[index]->ticksUntilAwake == 0)
        {
            wamDisplay_moleInfo[index]->ticksUntilAwake = wamControl_getRandomMoleAsleepInterval();//set ticks until awake equal to a random number
            wamDisplay_moleInfo[index]->ticksUntilDormant = wamControl_getRandomMoleAwakeInterval() + wamDisplay_moleInfo[index]->ticksUntilAwake;//set ticks until dormant equal to a random number plus awake ticks
            active = true;//set bool equal to true since mole was activated
        }
    }
    return true;//return true since mole was activated
}

// This takes the provided coordinates and attempts to whack a mole. If a
// mole is successfully whacked, all internal data structures are updated and
// the display and score is updated. You can only whack a mole if the mole is awake (visible).
wamDisplay_moleIndex_t wamDisplay_whackMole(wamDisplay_point_t* whackOrigin)
{
    uint8_t touch_x = whackOrigin->x;//set the touch point equal to a variable
    uint8_t touch_y = whackOrigin->y;//set the touch point equal to a coordinate
    for(uint16_t i=0; i<board_size; i++)//loop through all moles of the board size
    {
        uint16_t lower_row_buffer = (wamDisplay_moleInfo[i]->origin.y * WAMDISPLAY_HOLE_YPOS_ONE) - WAMDISPLAY_HOLE_RADIUS;//set a lower y bound for every hole
        uint16_t lower_col_buffer = (wamDisplay_moleInfo[i]->origin.x * WAMDISPLAY_HOLE_XPOS_ONE) - WAMDISPLAY_HOLE_RADIUS;//set a lower x bound for every hole
        uint16_t upper_row_buffer = (wamDisplay_moleInfo[i]->origin.y * WAMDISPLAY_HOLE_YPOS_ONE) + WAMDISPLAY_HOLE_RADIUS;//set an upper y bound for every hole
        uint16_t upper_col_buffer = (wamDisplay_moleInfo[i]->origin.x * WAMDISPLAY_HOLE_XPOS_ONE) + WAMDISPLAY_HOLE_RADIUS;//set an upper x bound for every hole

        if(touch_x >= lower_col_buffer && touch_x <= upper_col_buffer && touch_y >= lower_row_buffer && touch_y <= upper_row_buffer)//check to see if where you touched was over a hole
        {
            if(wamDisplay_moleInfo[i]->ticksUntilAwake == 0 && wamDisplay_moleInfo[i]->ticksUntilDormant != 0)//check to see if that hole had a mole that is awake
            {
                display_fillCircle(WAMDISPLAY_HOLE_XPOS_ONE*wamDisplay_moleInfo[i]->origin.x, WAMDISPLAY_HOLE_YPOS_ONE*wamDisplay_moleInfo[i]->origin.y - WAMDISPLAY_BACKGROUND_OFFSET, WAMDISPLAY_HOLE_RADIUS, WAMDISPLAY_BLACK);//erase mole since you wacked it
                wamDisplay_moleInfo[i]->ticksUntilDormant = 0;//inactivate the mole
                curr_hits++;//increment hits by one
            }
        }
    }
    //this is where i make the game harder
    if(curr_hits % WAMDISPLAY_FIVE_HITS == 0 && curr_hits != 0)//if the level is a multiple of 5
    {
        level++;//increment level
        wamControl_decrementRandNumLimit();//decrement upper interval rand num
        if(wamControl_getMaxActiveMoles() < board_size)//make this check so you dont set active moles greater than board size
        {
            wamControl_setMaxActiveMoles(wamControl_getMaxActiveMoles() + WAMDISPLAY_INCREMENT_ACTIVE_MOLES);//increment max number of allowed active moles
        }
    }
    wamDisplay_drawScoreScreen();//call this to update the scores on the screen as you play
}

// This updates the ticksUntilAwake/ticksUntilDormant clocks for all of the moles.
void wamDisplay_updateAllMoleTickCounts()
{
    for(uint16_t i=0; i<board_size; i++)//loop through all moles of the board size
    {
        uint16_t col = wamDisplay_moleInfo[i]->origin.x;//create a variable that is equal to the moles x position
        uint16_t row = wamDisplay_moleInfo[i]->origin.y;//create a variable that is equal to the moles y position
        if(wamDisplay_moleInfo[i]->ticksUntilAwake != 0)//if the ticks until awake is not already zero
        {
            wamDisplay_moleInfo[i]->ticksUntilAwake--;//decrement it by one
            if(wamDisplay_moleInfo[i]->ticksUntilAwake == 0)//check to see if mole is awake
            {
                display_fillCircle(WAMDISPLAY_HOLE_XPOS_ONE*col, WAMDISPLAY_HOLE_YPOS_ONE*row - WAMDISPLAY_BACKGROUND_OFFSET, WAMDISPLAY_HOLE_RADIUS, WAMDISPLAY_RED);//draw mole
            }
        }
        if(wamDisplay_moleInfo[i]->ticksUntilDormant != 0)//if the ticks until dormant is not already zero
        {
            wamDisplay_moleInfo[i]->ticksUntilDormant--;//decrement it by one
            if(wamDisplay_moleInfo[i]->ticksUntilDormant == 0)//check to see if mole is went back to sleep
            {
                display_fillCircle(WAMDISPLAY_HOLE_XPOS_ONE*col, WAMDISPLAY_HOLE_YPOS_ONE*row - WAMDISPLAY_BACKGROUND_OFFSET, WAMDISPLAY_HOLE_RADIUS, WAMDISPLAY_BLACK);//erase mole
                curr_misses++;//increment misses by one
                wamDisplay_drawScoreScreen();//call this to update the scores on the screen as you play
            }
        }
    }
}

// Returns the count of currently active moles.
uint16_t wamDisplay_getActiveMoleCount()
{
    uint32_t active_molecount = 0;//create a variable that keeps track of number of active moles
    for(uint16_t i=0; i<board_size; i++)//loop through all moles of the board size
    {
        if(wamDisplay_moleInfo[i]->ticksUntilDormant != 0 || wamDisplay_moleInfo[i]->ticksUntilAwake != 0)//if either of the ticks are non zero the mole is active
        {
            active_molecount++;//increment number of active moles by one
        }
    }
    return active_molecount; //return the number of active moles
}

// Sets the hit value in the score window.
void wamDisplay_setHitScore(uint16_t hits)
{
    curr_hits = hits;//set the current number of hits equal to whatever you pass in
}

// Gets the current hit value.
uint16_t wamDisplay_getHitScore()
{
    return curr_hits;//used to return the number of hits from outside this file
}

// Sets the miss value in the score window.
void wamDisplay_setMissScore(uint16_t misses)
{
    curr_misses = misses;//set the current number of misses equal to whatever you pass in
}

// Gets the miss value.
uint16_t wamDisplay_getMissScore()
{
    return curr_misses;//used to return the number of misses from outside this file
}

// Sets the level value on the score board.
void wamDisplay_incrementLevel()
{
    level++;//increment level by one
}

// Retrieves the current level value.
uint16_t wamDisplay_getLevel()
{
    return level;//used to return the level from outside this file
}

// Completely draws the score screen.
void wamDisplay_drawScoreScreen()
{
    display_setTextColor(WAMDISPLAY_WHITE);//Make the text white.
    display_setTextSize(WAMDISPLAY_TEXT_SIZE_TWO);//set the text size to two
    sprintf(print_prev_hits, "%d", curr_hits--);//print the previous curr_hits to an array
    sprintf(print_prev_misses, "%d", curr_misses--);//print the previous curr_misses to an array
    sprintf(print_prev_level, "%d", level--);//print the previous level to an array
    sprintf(print_hits, "%d", curr_hits);//print the curr_hits to an array
    sprintf(print_misses, "%d", curr_misses);//print the curr_misses to an array
    sprintf(print_level, "%d", level);//print the level to an array
    display_setCursor(WAMDISPLAY_X_PIXEL_POS_HITS*WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_WIDTH, WAMDISPLAY_PIXEL_HEIGHT - WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_HEIGHT);//set the cursor position to erase hits
    display_setTextColor(WAMDISPLAY_BLACK);//Make the text black.
    display_print(print_prev_hits);//erase previous hits
    display_setCursor(WAMDISPLAY_X_PIXEL_POS_HITS*WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_WIDTH, WAMDISPLAY_PIXEL_HEIGHT - WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_HEIGHT);//set the cursor position to print hits
    display_setTextColor(WAMDISPLAY_WHITE);//Make the text white.
    display_print(print_hits);//print the char array called hits to the lcd display
    display_setCursor(WAMDISPLAY_X_PIXEL_POS_MISS*WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_WIDTH, WAMDISPLAY_PIXEL_HEIGHT - WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_HEIGHT);//set the cursor position to erase misses
    display_setTextColor(WAMDISPLAY_BLACK);//Make the text black.
    display_print(print_prev_misses);//erase previous misses
    display_setCursor(WAMDISPLAY_X_PIXEL_POS_MISS*WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_WIDTH, WAMDISPLAY_PIXEL_HEIGHT - WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_HEIGHT);//set the cursor position to print misses
    display_setTextColor(WAMDISPLAY_WHITE);//Make the text white.
    display_print(print_misses);//print the char array called print_misses to the lcd display
    display_setCursor(WAMDISPLAY_X_PIXEL_POS_LEVEL*WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_WIDTH, WAMDISPLAY_PIXEL_HEIGHT - WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_HEIGHT);//set the cursor position to erase level
    display_setTextColor(WAMDISPLAY_BLACK);//Make the text black.
    display_print(print_prev_level);//erase previous level
    display_setCursor(WAMDISPLAY_X_PIXEL_POS_LEVEL*WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_WIDTH, WAMDISPLAY_PIXEL_HEIGHT - WAMDISPLAY_TEXT_SIZE_TWO*WAM_DISPLAY_CHAR_HEIGHT);//set the cursor position to print level
    display_setTextColor(WAMDISPLAY_WHITE);//Make the text white.
    display_print(print_level);//print the char array called print_level to the lcd display
}

// Make this function available for testing purposes.
void wamDisplay_incrementMissScore()
{
    curr_misses++;//increment current misses by one
}

// Reset the scores and level to restart the game.
void wamDisplay_resetAllScoresAndLevel()
{
    //When you are done, you must return the memory to the system or you will create a memory leak.
    // First deallocate all of the structs.
    for (uint16_t l=0; l<board_size; l++)//loop through all moles of the board size
    {
        free(wamDisplay_moleInfo[l]);   // This deallocates the memory.
        wamDisplay_moleInfo[l] = NULL;  // This step is not necessary but will keep you from reusing deallocated memory.
    }
    // Next, deallocate the array that contains the pointers to the structs.
    free(wamDisplay_moleInfo);   // Deallocates the container of arrays.
    wamDisplay_moleInfo = NULL;  // Also keeps you from reusing the deallocated memory.
    curr_misses = 0;//reset the number of misses to zero
    curr_hits = 0;//reset the number of hits to zero
    level = 0;//reset the level to zero
}

// Test function that can be called from main() to demonstrate milestone 1.
// Invoking this function should provide the same behavior as shown in the Milestone 1 video.
void wamDisplay_runMilestone1_test()
{
    if(display_isTouched() == true && runtest == 0)//check runtest variable to print appropriate screen
    {
        runtest = WAMDISPLAY_RUN_TEST_ONE_LOOP;//make the variable 1 so that you go to next screen
        display_clearOldTouchData();//clear old touch data after touching the screen
        wamDisplay_drawSplashScreen();//draw the splash screen
    }
    else if(display_isTouched() == true && runtest == WAMDISPLAY_RUN_TEST_ONE_LOOP)//check runtest variable to print appropriate screen
    {
        runtest = WAMDISPLAY_RUN_TEST_TWO_LOOP;//make the variable 2 so that you go to next screen
        display_clearOldTouchData();//clear old touch data after touching the screen
        wamDisplay_drawMoleBoard();//draw the mole board screen
    }
    else if(display_isTouched() == true && runtest == WAMDISPLAY_RUN_TEST_TWO_LOOP)//check runtest variable to print appropriate screen
    {
        runtest = 0;//make the variable 0 so that you go to next screen
        display_clearOldTouchData();//clear old touch data after touching the screen
        wamDisplay_drawGameOverScreen();//draw the game over screen
    }
}



