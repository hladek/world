#include "world.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


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
    mvaddch(x,y,character);
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

void start(int argc,char** argv,void* (*step_world)(void*,struct game*),void* (*init_world)(struct game*),void (*destroy_world)(void*)){
    srand(time(NULL));
    int r = 1;
    if (initscr() == NULL){
        // TODO Which Error?
        puts("Curses Error.");
        return;
    }
    noecho(); // Nevypisuj vstup na obrazovku
    cbreak(); // Zabudni starý vstup
    nodelay(stdscr,TRUE); // Nečakaj na stlačenie
    keypad(stdscr,TRUE); // Aktivuje šípky
    curs_set(FALSE); // Neviditeľný kurzor
    if (has_colors()){ // Zistenie či terminál podporuje farby
        start_color();
        init_pair(0, COLOR_BLACK, COLOR_BLACK);
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_WHITE, COLOR_BLACK);
    }
    struct game game;
    game.height = LINES;
    game.width = COLS;
    game.interval = 100;

    void* world = NULL;
    if (init_world != NULL){
          world = init_world(&game);
    }
    r = step_world(world,&game);
    while (!r) {
        game.height = LINES;
        game.width = COLS;
        game.key = getch();
        if (game.key == ERR){
            usleep(game.interval);
        }
        r = step_world(world,&game);
    }
    if (destroy_world != NULL){
        destroy_world(world);
    }
    endwin();
};
