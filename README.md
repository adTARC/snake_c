# SNAKE ASCII GAME
This game has been tested to run only on Linux (I tested this on Ubuntu 16.04 LTS and 15.10)

### LANGUAGE
	- C
	
### LIBRARIES USED
	- stdlib.h
	- string.h
	- unistd.h
	- time.h
	- math.h
	- curses.h
	- snake.h

### AUTHOR
	- Aditya Sathish
	
### CREDITS
	- petrvolny (http://github.com/petrvolny)
	
### DATE CREATED
	- 16th January 2016
### DATE MODIFIED
	- 26th May 2017

### DESCRIPTION	
	- This is a clone of the classic game using the C language. It runs using the curses library.
	- This is designed to run on linux and doesn't contain Windows specific libraries like conio and dos
	
### CONTROLS
	- w,a,s,d for moving the snake around
	
### SOME FEATURES
	- Contains only ASCII characters
	- Speeds up after every point
	- Scoreboard

### PLANNED FEATURES
	- Bonus food (x50)
	- Score multipliers
	- Ability to restart game from end screen and win screen

### INSTALLATION INSTRUCTIONS
	- This program uses curses.h header for some functions. Therefore, inorder to run this game,
	- Make sure you download the curses.h header file into your linux machine.
	- To do this, run this command (without the $ character):
						
	$ sudo apt-get install libncurses5-dev
						
	- After you install it. Make sure you compile it with a rule to link to the curses library
						
	$ gcc main.c snake.c -lncurses
	
