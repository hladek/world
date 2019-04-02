#include "world.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termbox.h>
#include <time.h>

void destroy_world(struct world* world){
    stop(world);
    tb_shutdown();
}

void end_message(struct world* world, const char* message){
    destroy_world(world);
    puts(message);
    exit(0);
}

void assert_message(int event, struct world* world, const char* message){
    if (event == 0){
        end_message(world,message);
    }
}

void init_world(struct world* w) {
    assert_message(w != NULL,w,"init_world:: world is NULL"); 
    w->height = tb_height();
    w->width = tb_width();
    if (w->interval <= 0){
        w->interval = 100;
    }
}

void set_color_character(struct world* w,int x,int y,int character,uint16_t foreground,uint16_t background) {
    assert_message(w != NULL,w,"set_character:: world is NULL"); 
    assert_message((x >= 0) && (x < w->width),w,"set_character:: width is out of bounds");
    assert_message((y >= 0) && (y < w->height),w,"set_character:: height is out of bounds");
    tb_change_cell(x,y,character,foreground,background);
}

void set_character(struct world* w,int x,int y,int character) {
    set_color_character(w,x,y,character,TB_WHITE,TB_BLACK);
}

void set_message(struct world* w,int x,int y,const char* message) {
    int l = strlen(message);
    for (int i = 0; i < l; i++){
        set_character(w,x+i,y,message[i]);
    }
}

void set_color_message(struct world* w,int x,int y,const char* message,int character,uint16_t foreground,uint16_t background) {
    int l = strlen(message);
    for (int i = 0; i < l; i++){
        set_color_character(w,x+i,y,message[i],foreground,background);
    }
}

int step_world(struct world* world,int eventkey){
    init_world(world);
    tb_clear();
    int r = step(world,eventkey);
    tb_present();
    return r;
}

void game(int argc, char** argv){
    srand(time(NULL));
    int r = tb_init();
    if (r < 0){
        puts("Termbox Error.");
        return;
    }
    struct tb_event event;
    struct world world;
    memset(&world,0,sizeof(struct world));
    init_world(&world);
    start(&world,argc,argv);
    r = step_world(&world,0);
    while (!r) {
        int t = tb_peek_event(&event,world.interval);
        if (t == -1){
            end_message(&world,"termox poll error");
        }
        // Zero abuses tilda keycode
        int eventkey = 0;
        if (event.type == TB_EVENT_KEY){
            eventkey = event.key;
            if (event.ch > 0){
                eventkey = event.ch;
            }
        }
        if (event.type == TB_EVENT_RESIZE){
            // This abuses Ctrl A key code
            eventkey = 1;
        }
        r = step_world(&world,eventkey);
        if (eventkey == TB_KEY_CTRL_C){
            r = 1;
        }
        else if (eventkey == TB_KEY_CTRL_D){
            r = 1;
        }
    }
    destroy_world(&world);
};
