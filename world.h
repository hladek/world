#ifndef _GAME_H_
#define _GAME_H_

#include <termbox.h>
/**
 * Game world represented as a rectangular matrix of integers.
 * 
 * Point [0,0] is displayed the upper left corner of the screen.
 * 
 */

struct world {
    /**
     * Width of the game world.
     */
    int width;
    /**
     * Height of the game world.
     */
    int height;
    /**
     * Ponter to the game world. 
     */
    struct tb_cell* plane;

    int plane_size;
    /**
     * State of the game managed by the programmer.
     */
    void* state;
    /**
     * Interval to wait for next step. Next step is also triggered by a keypress
     */
    int interval;
};


/**
 * Initializes the game world. This function is called by the librabry (function game())
 * @param world
 */
void init_world(struct world* w);

/**
 * Draws the world on screen.
 * @param world
 */
 void draw_world(struct world* world);

/**
 * Sets each cell of th world to zero.
 * @param world
 */
void clear_world(struct world* world);

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
