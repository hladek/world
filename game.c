#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "game.h"

void set_message(struct world* w,const char* message,int x,int y) {
    int l = strlen(message);
    for (int i = 0; i < l; i++){
        set_cell(w,message[i],x+i,y);
    }
}

// Start is called one in the beginning
void* init_game(struct world* g){
    // Allocate memory for the state
    struct game* st = calloc(1,(sizeof(struct game)));
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
int world_event(struct world* world,void* game){
    // Get state pointer
    struct game* state = game;

    // Read game variable and update the world state

    // Is mouse caught ?
    if ((state->caty == state->mousey) && (state->catx == state->mousex)){
        // Just print message
        strcpy(state->message,"HAM!!!");
    }
    else {
        // random mouse movement
        int m = rand() % 4;
        if (m == 0){
            state->mousey -= 1;
        }
        else if (m == 1){
            state->mousey += 1;
        }
        else if (m == 2){
            state->mousex -= 1;
        }
        else if (m == 3){
            state->mousex += 1;
        }
        // Move cat according to keyboard
        if (world->key == KEY_UP){
            state->caty -= 1;
        }
        else if (world->key == KEY_DOWN){
            state->caty += 1;
        }
        else if (world->key == KEY_LEFT){
            state->catx -= 1;
        }
        else if (world->key == KEY_RIGHT){
            state->catx += 1;
        }
    }
    if (world->key == KEY_ENTER){
    // Non zero means finish the loop and stop the game.
        return 1;
    }
	// Draw world state 
    //
    // Draw cat
    set_cell(world,'c',state->catx,state->caty);
    // Draw mouse
    set_cell(world,'m',state->mousex,state->mousey);
    set_message(world,state->message,12,13);
    return 0;
}

