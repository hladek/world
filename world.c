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

void set_color_character(struct game* w,int x,int y,int character,int pen) {
    assert_message(w != NULL,"set_character:: world is NULL"); 
    if (x < 0 || x >= w->width){
        char msg[100];
        sprintf(msg,"set_character:: width %d is out of bounds (0,%d)",x,w->width);
        abort_game(msg);
    }
    if (y < 0 || y >= w->height){
        char msg[100];
        sprintf(msg,"set_character:: height %d is out of bounds (0,%d)",y,w->height);
        abort_game(msg);
    }
    attron(pen);
    mvaddch(y,x,character);
    attroff(pen);
}

void set_character(struct game* w,int x,int y,int character) {
    set_color_character(w,x,y,character,0);
}

void set_message(struct game* w,int x,int y,const char* message) {
    int l = strlen(message);
    for (int i = 0; i < l; i++){
        set_character(w,x+i,y,message[i]);
    }
}

void set_color_message(struct game* g,int x,int y,const char* message,int character,int pen) {
    int l = strlen(message);
    for (int i = 0; i < l; i++){
        set_color_character(g,x+i,y,message[i],pen);
    }
}

int start_world(int (*step_world)(void*,struct game*),void* (*init_world)(struct game*),void (*destroy_world)(void*)){
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
    struct game game;
    game.height = LINES;
    game.width = COLS;
    game.interval = 100;
    game.key = ERR;

    void* world = NULL;
    if (init_world != NULL){
         world = init_world(&game);
         assert_message(world != NULL,"init_world should return non null pointer");
    }
    timeout(game.interval);
    // Initial step
    r = step_world(world,&game);
    refresh();
    while (!r) {
        game.height = LINES;
        game.width = COLS;
        game.key = getch();
        // Clear screen
        mvaddch(0,0,' ');
        int screenchars = LINES*COLS;
        for (int j = 1; j < screenchars;j++ ){
            addch(' ');
        }
        // Draw new world
        r = step_world(world,&game);
        refresh();
        // set new timeout
        timeout(game.interval);
    }
    if (destroy_world != NULL){
        destroy_world(world);
    }
    endwin();
    return r;
};
