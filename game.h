#ifndef _GAME_H_INCLUDE_
#define _GAME_H_INCLUDE_
#include "world.h"

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
    // Funky message
    char message[100];
};

void* init_world(struct game* g);
int step_world(void* world,struct game* g);

#endif
