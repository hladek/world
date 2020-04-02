#ifndef _GAME_H_INCLUDE_
#define _GAME_H_INCLUDE_
#include "world.h"

// Set of variables that expresses state of the game.
// 
struct game {
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

// Returns pointer to  newly allocated world
void* init_game(struct world* g);

// Changes world according to the game state (pressed key, screen size or other event)
int world_event(struct world* world,void* game);

#endif
