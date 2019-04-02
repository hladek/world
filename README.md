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
- `int interval`: maximum time between steps in miliseconds.
- `void* state`: a pointer to the game state. it is responsibility of the programmer to design the structure. It should be  allocated and initialized in the `start()` function and freed in the `stop()` function. 

### Step function

The `step()` function should:

1. Resd the game state (from the `void* state`) pointer.
1. Examine the pressed key. If the `key` variable is non-zero, a key was pressed. According to the pressed key, modify the game state.
1. Draw the game state. In the beginning of the step function the screen is empty.
1. Returning non/zero value ends the game loop. 

At the start the step() is called with zero `key` argument.

Mapping of values to pressed keys can be raead from file 
[termbox.h](https://github.com/nsf/termbox/blob/master/src/termbox.h).

Some important key constants:


	#define TB_KEY_F12              (0xFFFF-11)
	#define TB_KEY_INSERT           (0xFFFF-12)
	#define TB_KEY_DELETE           (0xFFFF-13)
	#define TB_KEY_HOME             (0xFFFF-14)
	#define TB_KEY_END              (0xFFFF-15)
	#define TB_KEY_PGUP             (0xFFFF-16)
	#define TB_KEY_PGDN             (0xFFFF-17)
	#define TB_KEY_ARROW_UP         (0xFFFF-18)
	#define TB_KEY_ARROW_DOWN       (0xFFFF-19)
	#define TB_KEY_ARROW_LEFT       (0xFFFF-20)
	#define TB_KEY_ARROW_RIGHT (0xFFFF-21)
	#define TB_KEY_BACKSPACE        0x08
	#define TB_KEY_CTRL_H           0x08 /* clash with 'CTRL_BACKSPACE' */
	#define TB_KEY_TAB              0x09
	#define TB_KEY_CTRL_I           0x09 /* clash with 'TAB' */
	#define TB_KEY_CTRL_J           0x0A
	#define TB_KEY_CTRL_K           0x0B
	#define TB_KEY_CTRL_L           0x0C
	#define TB_KEY_ENTER 0x0D

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
