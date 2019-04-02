#ifndef _GAME_H_
#define _GAME_H_

// Signalizes game next loop  
// (abuses ctrl tilda keypress code)
#define WORLD_TIMEOUT_EVENT 0
// Signlizes the first step of the game loop
// (abuses ctrl a keypress)
#define WORLD_START_EVENT 1
// Signalizes resize of the screen (width and height have changed)
// (abuses ctrl b keypress)
#define WORLD_RESIZE_EVENT 2

#include <termbox.h>
/**
 * Game world represented as a rectangular matrix of colorful characters.
 * 
 * Point [0,0] is displayed the upper left corner of the screen.
 * 
 */

struct world {
    /**
     * Width of the screen.
     */
    int width;
    /**
     * Height of the screen.
     */
    int height;
    /**
     * State of the game managed by the programmer.
     */
    void* state;
    /**
     * Interval to wait for next step. 
     */
    int interval;
};


/**
 * Initializes the game world. This function is called by the librabry (function game())
 * @param world
 */
void init_world(struct world* w);

/**
 * Sets cell to a state.
 * @param world
 * @param x coordinate of cell
 * @param y coordinate of cell
 * @param new state of the cell
 */
void set_character(struct world* w,int x,int y,int value);

void set_message(struct world* w,int x,int y,const char* message);

/**
 * Runs the game loop.
 * @param number of commandline arguments
 * @param commandline arguments 
 */
void game(int argc,char** argv);

/**
 *  Initializes user state.
 * @param world
 * @param number of commandline arguments
 * @param commandline arguments 
 * 
 */
void start(struct world*,int argc,char** argv);

/**
 * Free user state.
 * @param world
 */
void stop(struct world* world);

/**
 * Changes state of the world according to pressed keys
 * @param world
 * @param code of the pressed key
 */
int step(struct world* world,int key);

#endif
