# World Game Library

Learn C programming by a game

## Make your own game

The game happens in a rectangular world of colorful characters. 
Your goal as a programmer is to modify the world according to the pressed keys and the internal game state.
The library implements the game loop and draws the world to screen.

Your game consists of three functions. Each function can modify the world.

- `void start(struct world* w)` is called in the beginning. Here you can initialize the internal state of the game. 
- `int step(struct world* w,int key)` is called in periodic interval or when a key was pressed. Non-zero return value or `Ctrl+C` key interrupts the game loop.
- `void stop(struct world)` is called before end. Here you can free the internal state initialized in the `start()` function.

The world variable represents state of two-dimensional grid of characters on the screen. The screen matrix looks like this:

       origin
       [0,0]     width
	  +--------------------+
    h |                    |
	e |                    |
	i |                    |
	g |                    |
	h |                    |
	t |                    |
	  +--------------------+

The world  has the following parameters:

- `int height`: y-dimension of the grid.
- `it width`: x-dimension of the grid.
- `int interval`: maximum time between steps in milliseconds.
- `void* state`: a pointer to the game state. It is responsibility of the programmer to design the structure. It should be  allocated and initialized in the `start()` function and freed in the `stop()` function. 

### Step function

The `step()` function should:

1. Read the game state (from the `void* state`) pointer.
1. Examine the pressed key. If the `key` variable is non-zero, a key was pressed. According to the pressed key, modify the game state.
1. Draw the game state. In the beginning of the step function the screen is empty.
1. Returning non-zero value ends the game loop. 

At the start the `step()` is called with zero `key` argument.

Mapping of values to pressed keys can be read from file 
[termbox.h](https://github.com/nsf/termbox/blob/master/src/termbox.h).

Some important key constants:

	TB_KEY_ARROW_UP         
	TB_KEY_ARROW_DOWN       
	TB_KEY_ARROW_LEFT       
	TB_KEY_ARROW_RIGHT 
	TB_KEY_F12              
	TB_KEY_INSERT           
	TB_KEY_DELETE           
	TB_KEY_HOME             
	TB_KEY_END              
	TB_KEY_PGUP             
	TB_KEY_PGDN             
	TB_KEY_BACKSPACE        
	TB_KEY_CTRL_H
	TB_KEY_TAB              
	TB_KEY_CTRL_C           
	TB_KEY_ENTER

### Drawing to screen

The internal game state is drawn on screen during each call of the 'step()' function.
In the beginning the screen is clear.

A single character can be drawn using a function 

    void set_character(struct world* w,int character,int x,int y) 
    
The function draws  the given 'character' on screen 'w' in the given place '[x,y]'.
The library supports full Unicode character set, so you can draw beautiful graphics
as it is in the [demo program](https://github.com/nsf/termbox/blob/master/src/demo/paint.c):

        0x20, // ' '
        0x2591, // '░'
        0x2592, // '▒'
        0x2593, // '▓'
        0x2588, // '█'

It is possible to draw a character and set color of the background and foreground using a function

    void set_color_character(struct world* w,int x,int y,int character,uint16_t foreground,uint16_t background)

Parameters `foreground` and `background` are color codes from file `termbox.h`.

Some important color codes:

    TB_DEFAULT 
    TB_BLACK   
    TB_RED     
    TB_GREEN   
    TB_YELLOW  
    TB_BLUE    
    TB_MAGENTA 
    TB_CYAN    
    TB_WHITE   



## Installation and Running

Make sure, that [Termbox](https://github.com/nsf/termbox) is installed.

Clone this repository.

Compile:

```c
make
```
	
Run:

```c
./game
```

Default game will be run.

## API

- [world.h](https://github.com/hladek/world/blob/master/world.h)
- [termbox.h](https://github.com/nsf/termbox/blob/master/src/termbox.h)
