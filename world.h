#ifndef _GAME_H_
#define _GAME_H_

#include <curses.h>
/**
 * Game world represented as a rectangular matrix of colorful characters.
 * 
 * Point [0,0] is displayed the upper left corner of the screen.
 * 
 */

struct game {
    /**
     * Last width of the screen.
     */
    int width;
    /**
     * Last height of the screen.
     */
    int height;
    /**
     * Interval to wait for next step. 
     */
    int interval;
    /**
     * Last pressed key. ERR if none.
     */
    int key;
};


/**
 * Sets cell to a state.
 * @param world
 * @param x coordinate of cell
 * @param y coordinate of cell
 * @param new state of the cell
 */
void set_character(struct game* w,int x,int y,int value);

void set_message(struct game* w,int x,int y,const char* message);

/**
 *
 * @param world
 * @param number of commandline arguments
 * @param init_world
 * @param destroy_world
 *
 * void init_world(struct world* w);
 * Initializes user state.
 * Free user state.
 * @param world
 */

int start_world(int (*step_world)(void*,struct game*),void* (*init_world)(struct game*),void (*destroy_world)(void*));



#endif
