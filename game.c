#include <termbox.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"

struct state {
    int catx;
    int caty;
    int mousex;
    int mousey;
    char message[100];
};

void start(struct world* world,int argc, char** argv){
    struct state* st = calloc(1,(sizeof(struct state)));
    st->mousex = 11;
    st->mousey = 12;
    st->catx = 5;
    st->caty = 5;
    world->state = st;
}

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
        else if (key == TB_KEY_ARROW_LEFT){
            st->mousex -= 1;
        }
        else if (key == TB_KEY_ARROW_UP){
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

    return 0;
}

void stop(struct world* world){
    free(world->state);
}
