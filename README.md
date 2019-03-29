# World Game Library

Learn C programming by a game

## Make your own game

The game happens in a rectangular world. 
Your goal as a programmer is to the world according to pressed keys and internal game state.
The library imploements the game loop and draws the world to screen.

Your game consists of three functions. Each function can modify the world.

- start(struct world* w) is called in the beginning. Here you can initialize additional state of the game. 
- step(struct world* w,int key) is called in periodic interval or when a key was pressed. None zero return value or ESC key interrputs the game loop.
- stop(struct world) is called before end. Here you can free additional memory initialized at the start.

## Installation and Running

Make sure, that [Termbox[(https://github.com/nsf/termbox) is installed.

Clone this repository.

Compile:

	make
	
Run:
	./game

Default game will be run.

## API

- [world.h](https://github.com/hladek/world/blob/master/world.h)
- [termbox.h](https://github.com/nsf/termbox/blob/master/src/termbox.h)
