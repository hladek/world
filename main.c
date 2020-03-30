#include "game.h"
#include "world.h"
#include <stdlib.h>


int main(int argc, char** argv){
    start_world(step_world,init_world,free);
    return 0;
}
