#include <termbox.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"

// Set of variables that expresses state of the game.
// 
struct state {
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
void start(struct world* world,int argc, char** argv){
    // Allocate memory for the state
    struct state* st = calloc(1,(sizeof(struct state)));
    // Initialize state
    st->mousex = 11;
    st->mousey = 12;
    st->catx = 5;
    st->caty = 5;
    // Store pointer to the state to the world variable
    world->state = st;
}

// Step is called in a loop once in interval.
// It should modify the state and draw it.
int step(struct world* w,int key){
    // Get state pointer
    struct state* st = w->state;

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
        else if (my == 2){
            st->mousex -= 1;
        }
        else if (key == 3){
            st->mousex += 1;
        }
        // Move cat according to keyboard
        if (key == TB_KEY_ARROW_UP){
            st->caty -= 1;
        }
        else if (key == TB_KEY_ARROW_DOWN){
            st->caty += 1;
        }
        else if (key == TB_KEY_ARROW_LEFT){
            st->catx -= 1;
        }
        else if (key == TB_KEY_ARROW_RIGHT){
            st->catx += 1;
        }	
    }
	// Draw state 
    set_character(w,st->catx,st->caty,'c');
    set_character(w,st->mousex,st->mousey,'m');
    set_message(w,12,13,st->message);
    if (key == TB_KEY_ESC){
    	// Non zero means finish the loop and stop the game.
        return 1;
    }

    return 0;
}

// Stop is called after game loop is finished
void stop(struct world* world){
    // Free memory for game state
    free(world->state);
}
