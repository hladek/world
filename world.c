#include "world.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void abort_game(const char* message){
    endwin();
    puts(message);
    exit(1);
}

void assert_message(int event,const char* message){
    if (event == 0){
        abort_game(message);
    }
}

void stamp_cell(struct world* w,int character,enum color_stamp pen, int x,int y) {
    assert_message(w != NULL,"stamp_cell:: world is NULL"); 
    if (x < 0 || x >= w->width){
        char msg[100];
        sprintf(msg,"stamp_cell:: width %d is out of bounds (0,%d)",x,w->width);
        abort_game(msg);
    }
    if (y < 0 || y >= w->height){
        char msg[100];
        sprintf(msg,"stamp_cell:: height %d is out of bounds (0,%d)",y,w->height);
        abort_game(msg);
    }
    attron(pen);
    mvaddch(y,x,character);
    attroff(pen);
}

void set_cell(struct world* w,int character,int x,int y) {
    stamp_cell(w,character,0,x,y);
}

int start_world(int (*world_event)(struct world* world,void* game),void* (*init_game)(struct world*),void (*destroy_game)(void*)){
    srand(time(NULL));
    int r = 1;
    if (initscr() == NULL){
        // TODO Which Error?
        puts("Curses Error.");
        return -1;
    }
    noecho(); // Nevypisuj vstup na obrazovku
    cbreak(); // Zabudni starý vstup
    nodelay(stdscr,TRUE); // Nečakaj na stlačenie
    keypad(stdscr,TRUE); // Aktivuje šípky
    curs_set(FALSE); // Neviditeľný kurzor
    if (has_colors()){ // Zistenie či terminál podporuje farby
        start_color();
        // Pera na ciernom podklade
        init_pair(BLACK_FRONT,  COLOR_BLACK, COLOR_BLACK);
        init_pair(WHITE_FRONT,  COLOR_WHITE, COLOR_BLACK);
        init_pair(RED_FRONT,    COLOR_RED, COLOR_BLACK);
        init_pair(GREEN_FRONT,  COLOR_GREEN, COLOR_BLACK);
        init_pair(BLUE_FRONT,   COLOR_BLUE, COLOR_BLACK);
        init_pair(CYAN_FRONT,   COLOR_CYAN, COLOR_BLACK);
        init_pair(MAGENTA_FRONT,COLOR_MAGENTA, COLOR_BLACK);
        init_pair(YELLOW_FRONT, COLOR_YELLOW, COLOR_BLACK);
        init_pair(BLACK_BACK,   COLOR_BLACK, COLOR_BLACK);
        init_pair(WHITE_BACK,   COLOR_BLACK, COLOR_WHITE);
        init_pair(RED_BACK,     COLOR_BLACK, COLOR_RED);
        init_pair(GREEN_BACK,   COLOR_BLACK, COLOR_GREEN);
        init_pair(BLUE_BACK,    COLOR_BLACK, COLOR_BLUE);
        init_pair(CYAN_BACK,    COLOR_BLACK, COLOR_CYAN);
        init_pair(MAGENTA_BACK, COLOR_BLACK, COLOR_MAGENTA);
        init_pair(YELLOW_BACK,  COLOR_BLACK, COLOR_YELLOW);
    }
    else {
        puts("No colors!\n");
    }
    struct world world;
    world.height = LINES;
    world.width = COLS;
    world.interval = 100;
    world.key = ERR;

    void* game = NULL;
    if (init_game != NULL){
         game = init_game(&world);
         assert_message(game != NULL,"init_game should return non null pointer");
    }
    timeout(world.interval);
    // Initial step
    r = world_event(&world,game);
    refresh();
    while (!r) {
        world.height = LINES;
        world.width = COLS;
        world.key = getch();
        // Clear screen
        mvaddch(0,0,' ');
        int screenchars = LINES*COLS;
        for (int j = 1; j < screenchars;j++ ){
            addch(' ');
        }
        // Draw new world
        r = world_event(&world,game);
        refresh();
        // set new timeout
        timeout(world.interval);
    }
    if (destroy_game != NULL){
        destroy_game(game);
    }
    endwin();
    return r;
};
