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

enum color_pen_world {
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

#endif
