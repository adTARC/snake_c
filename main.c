/*
	Programmer					:	Aditya Sathish
	Date Created				:	16th January 2016
	File Name					:	main.c
	Dependent Files				:	snake.c, snake.h
	Description					:	Classic Snake Game based off Nokia's famous game during their 3310-era.
	
	NOTES						:	Tried and tested using Ubuntu 16.04 LTS
	
	HOW TO COMPILE				:	This program uses curses.h header for some functions. Therefore, inorder to run this game,
									Make sure you download the curses.h header file into your linux machine.
									To do this, run this command type in this (without the $ character):
						
									$ sudo apt-get install libncurses5-dev
					
									After you install it. Make sure you compile it with a rule to like it to ncurses
					
									$ gcc main.c snake.c -lncurses
					
	ORIGINAL WORK				:	petrvolny (http://github.com/petrvolny)
	LICENSING INFORMATION		:	GNU General Purpose License
*/


#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <curses.h>

#include "snake.h"


/*
	Main Function
*/
int main() {
	food_body food;
	snake_body snake[MAX_LENGTH];
    char c;
	extern int speed;
	
    init_game();
    welcome_splash();
    getch();
    clear();
    init_snake();
    level_create();
    draw_snake();
    add_food();
    refresh();

    // Main Game Loop
    while (1) {
        timeout(speed);
        c = getch();
        map_control(c);
        clear();
        level_create();
        move_snake_full();
        game_state_update();
        draw_snake();
        draw_food();
        refresh();
    }
}