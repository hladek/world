#include "game.h"
#include "world.h"
#include <stdlib.h>


int main(int argc, char** argv){
    start_world(world_event,init_game,free);
    return 0;
}
