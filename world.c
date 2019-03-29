#include "world.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termbox.h>
#include <time.h>

void destroy_world(struct world* world){
    stop(world);
    if (world->plane != NULL){
        free(world->plane);
    }
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
    int sz = w->width * w->height * sizeof(struct tb_cell);
    if (w->plane == NULL){
        w->plane = calloc(1,sz);
    }
    else if (sz != w->plane_size){
        w->plane = realloc(w->plane,sz);
    }
    w->plane_size = sz;
    if (w->interval <= 0){
        w->interval = 100;
    }
}

void set_color_character(struct world* w,int x,int y,int character,uint16_t foreground,uint16_t background) {
    assert_message(w != NULL,w,"set_character:: world is NULL"); 
    assert_message((x >= 0) && (x < w->width),w,"set_character:: width is out of bounds");
    assert_message((y >= 0) && (y < w->height),w,"set_character:: height is out of bounds");
    assert_message(w->plane != NULL,w,"set_character:: plane is NULL");
    struct tb_cell* c = w->plane + w->width * y + x;
    c->ch = character;
    c->fg = foreground;
    c->bg = background;
}

void set_character(struct world* w,int x,int y,int character) {
    set_color_character(w,x,y,character,TB_WHITE,TB_BLACK);
}

void clear_world(struct world* w){
    memset(w->plane,0,w->plane_size);
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

void draw_world(struct world* w){
    assert_message(w != NULL,w,"draw_world:: world is NULL"); 
    assert_message(w->width > 0,w,"draw_world:: width is zero ");
    assert_message(w->height > 0,w,"draw_world:: height is zero ");
    tb_clear();
    memcpy(tb_cell_buffer(), w->plane, w->plane_size);   
    tb_present();
}


void game(int argc, char** argv){
    srand(time(NULL));
    tb_init();
    struct tb_event event;
    struct world world;
    memset(&world,0,sizeof(struct world));
    world.height = tb_height();
    world.width = tb_width();
    start(&world,argc,argv);
    init_world(&world);
    clear_world(&world);
    int r = step(&world,0);
    draw_world(&world);
    while (!r) {
        int t = tb_peek_event(&event,world.interval);
        if (t == -1){
            end_message(&world,"termox poll error");
        }
        else if (t == TB_EVENT_RESIZE){
            init_world(&world);
        }
        int eventkey = 0;
        if (event.type == TB_EVENT_KEY){
            eventkey = event.key;
            if (event.ch > 0){
                eventkey = event.ch;
            }
        }
        clear_world(&world);
        r = step(&world,eventkey);
        if (eventkey == TB_KEY_ESC){
            r = 1;
        }
        else if (eventkey == TB_KEY_CTRL_C){
            r = 1;
        }
        else if (eventkey == TB_KEY_CTRL_D){
            r = 1;
        }
        draw_world(&world);
    }
    destroy_world(&world);
};
