#include <stdlib.h>
#include <string.h>
#include "world.h"
#include <curses.h>

// Set of variables that expresses state of the game.
// 
struct world {
    // X position of the cat
    int catx;
    // Y opsition of the cat
    int caty;
    // X position of the mouse
    int mousex;
    // Y position of the mouse
    int mousey;
    // Funny message
    char message[100];
};

// Start is called one in the beginning
void* init_world(struct game* g){

    // Allocate memory for the state
    struct world* st = calloc(1,(sizeof(struct world)));
    // Initialize state
    st->mousex = 11;
    st->mousey = 12;
    st->catx = 5;
    st->caty = 5;
    // Store pointer to the state to the world variable
    return st;
}

// Step is called in a loop once in interval.
// It should modify the state and draw it.
void* step_world(void* world,struct game* g){
    // Get state pointer
    struct world* st = world;

    // Update state

    // Is mouse caught ?
    if ((st->caty == st->mousey) && (st->catx == st->mousex)){
        // Just print message
        strcpy(st->message,"HAM!!!");
    }
    else {
    	// random mouse movement
        int m = rand() % 4;
        if (m == 0){
            st->mousey -= 1;
        }
        else if (m == 1){
            st->mousey += 1;
        }
        else if (m == 2){
            st->mousex -= 1;
        }
        else if (m == 3){
            st->mousex += 1;
        }
        // Move cat according to keyboard
        if (g->key == KEY_UP){
            st->caty -= 1;
        }
        else if (g->key == KEY_DOWN){
            st->caty += 1;
        }
        else if (g->key == KEY_LEFT){
            st->catx -= 1;
        }
        else if (g->key == KEY_RIGHT){
            st->catx += 1;
        }	
    }
	// Draw state 
    set_character(g,st->catx,st->caty,'c');
    set_character(g,st->mousex,st->mousey,'m');
    set_message(g,12,13,st->message);
    if (g.key == KEY_ESC){
    	// Non zero means finish the loop and stop the game.
        return 1;
    }

    return 0;
}

