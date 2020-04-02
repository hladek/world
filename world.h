#ifndef _WORLD_H_
#define _WORLD_H_

#include <curses.h>
/**
 * World represented as a rectangular matrix of colorful characters.
 * 
 * Point [0,0] is displayed the upper left corner of the screen.
 * 
 */

struct world {
    /**
     * Last width of the screen.
     */
    int width;
    /**
     * Last height of the screen.
     */
    int height;
    /**
     * Interval in miliseconds to wait for next step. 
     */
    int interval;
    /**
     * Last pressed key or Curses event.
     *
     * Special event  values:
     * ERR if timeout,
     * KEY_RESIZE if screen resize
     * KEY_EVENT, other event,
     * KEY_MOUSE, mouse clicked
     *
     * Key values:
     *
     * ' ' Space
     * KEY_DOWN Arrow down
     * KEY_UP Arrow up
     * KEY_LEFT Arrow left
     * KEY_RIGHT Arrow right
     * KEY_A1 Upper left of keypad
     * KEY_A3 Upper right of keypad
     * KEY_B2 Center of keypad
     * KEY_C1 Lower left of keypad
     * KEY_C3 Lower right of keypad
     *
     * KEY_ENTER
     * KEY_BACKSPACE
     */
    int key;
};


enum color_stamp {
    BLACK_FRONT,
    WHITE_FRONT,
    RED_FRONT,
    GREEN_FRONT,
    BLUE_FRONT,
    CYAN_FRONT,
    MAGENTA_FRONT,
    YELLOW_FRONT,
    BLACK_BACK,
    WHITE_BACK,
    RED_BACK,
    GREEN_BACK,
    BLUE_BACK,
    CYAN_BACK,
    MAGENTA_BACK,
    YELLOW_BACK,
};

/**
 * Sets cell to a state.
 * @param world
 * @param x coordinate of cell
 * @param y coordinate of cell
 * @param new state of the cell
 */
void set_cell(struct world* w,int character,int x,int y);

void stamp_cell(struct world* w,int character,enum color_stamp stamp,int x,int y);

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

int start_world(int (*world_event)(struct world* world,void* game),void* (*init_game)(struct world* world),void (*destroy_game)(void* game));


#endif
