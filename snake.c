#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <curses.h>
#include "snake.h"

/* ---------------------- EXTERNAL VARIABLE DEFINITIONS ---------------------------- */
/* direction: holds the value for the keyboard input */
extern int direction;
/* snakeLength: the length of the snake. It increments by one after each food score */
extern int snakeLength = 1;
/* row/col: the variables used to hold the number of rows and columns at the start of the terminal session */
extern int row, col;
/* game_row/game_col: it is the effective window size of the game, excluding the space for the text and scoreboard */
extern int game_row, game_col;
/* score: the score is assigned to this variable */
extern int score = 0;
/* speed: the starting speed of the snake */
extern int speed = 100;
/* ---------------------------------------------------------------------------------- */
/* ------------------------------ FUNCTION DEFINITION ------------------------------- */
int init_game(void) {
	// Seeding the random number generator (with the current time)
    srand(time(NULL));
    
    // Placing the snake outside the window on startup
    for (int i=0; i<MAX_LENGTH; i++) {
        snake[i].x = -1;
        snake[i].y = -1;
    }

	// 	Initalizing ncurses <structures> and <terminfo> files 
    initscr();
    
    // 	Checking if terminal supports colors. The game won't run without color
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}

	/* 	Finding the number of columns and rows in a given window
		- stdscr is the pointer to the window where the program is running (current process)
		- row is the variable we created to store the number of rows of the terminal
		- col is the variable we created to store the number of columns of the terminal
	*/
    getmaxyx(stdscr, row, col);
    game_row = row - 2;
    game_col  = col;
    
    // Preventing getch() from echoing the input character
    noecho();
    
    // Disables line buffering : hence characters are immediately available to  the program
    cbreak();
    
    // Making the cursor INVISIBLE
    curs_set(0);
    
    // Starting the color process to run colors on the terminal
	start_color();
	
	// Setting the color pair to cyan and black
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	
	// Making all the elements BOLD
    attron(A_BOLD);
    
    // Clearing all content on curses window
    clear();
    
    // Setting the color of the window to match that of the terminal window
    color_set(1, NULL);
}

void add_food() {
    int x,y;
    
    // Getting random values with respect to row and column respectively
    y = rand() % game_row;
    x = rand() % game_col;
    
    // If the content of the cell is not already taken by a white space then, and only then can the food by put there.
    while ((mvinch(y, x) & A_CHARTEXT) != ' ') {
        y = rand() % game_row;
        x = rand() % game_col;
    }
    
    // Setting Food Location
    food.y = y;
    food.x = x;
}

/* DRAWING FOOD */
void draw_food() {
	// Setting the food character at the position defined by the food structure
    move(food.y, food.x);
    
    // Setting the character at the location to be FOOD_CHAR macro
    addch(FOOD_CHAR);
}

/* SETTING UP THE SNAKE DRAWABLE */
void init_snake() {
	// How the snake is located when it starts
    snake[1].x = 2;
    snake[1].y = game_row/2;
    snake[0].x = 3;
    snake[0].y = game_row/2;
    snakeLength = 2;
    direction = RIGHT;
}

/* DRAWING POSITION OF SNAKE */
void draw_snake() {
    int i=0;
    
    // Translation of snake as long as it stays in the bounds of the window
    while (snake[i].x != -1 && snake[i].y != -1) {
        move(snake[i].y, snake[i].x);
        addch(SNAKE_CHAR);
        i++;
    }
}

/* MOVEMENT OF SNAKE */
void move_snake() {
    int i=0;
    
    // Helping the snake move
    for (int i=snakeLength-1; i>=0; i--) {
        snake[i+1] = snake[i];
    }
}

/* MOVING THE SNAKE HEAD BASED ON KEYBOARD INPUT */
void move_snake_head() {

     snake_body origHead = snake[0];
     move_snake();
     switch (direction) {
        case UP:
            origHead.y--;
            break;
        case DOWN:
            origHead.y++;
            break;
        case LEFT:
            origHead.x--;
            break;
        case RIGHT:
            origHead.x++;
            break;
    }
    snake[0] = origHead;
}

/* REMOVING TAIL AS SNAKE MOVES  */
void move_snake_tail() {
    mvaddch(snake[snakeLength].y, snake[snakeLength].x, ' ');
    snake[snakeLength].x = -1;
    snake[snakeLength].y = -1;
}

/* CONVERTING KEYBOARD INPUT */
void map_control(char c) {
    switch(c) {
        case 'w':
            direction = UP;
            break;
        case 's':
            direction = DOWN;
            break;
        case 'd':
            direction = RIGHT;
            break;
        case 'a':
            direction = LEFT;
            break;
    }
}

/* DRAW THE WINNER SCREEN */
void winner_splash() {
    clear();
    mvprintw(game_row/2-1, game_col/2-strlen(WIN_MSG0)/2, WIN_MSG0);
    mvprintw(game_row/2, game_col/2-strlen(WIN_MSG1)/2, WIN_MSG1);
    refresh();
}

/* DRAW THE SPLASH SCREEN */
void welcome_splash() {
    clear();
    mvprintw(game_row/2-1, game_col/2-strlen(WELCOME_MSG0)/2, WELCOME_MSG0);
    mvprintw(game_row/2, game_col/2-strlen(WELCOME_MSG1)/2, WELCOME_MSG1);
    refresh();
}

/* DRAW THE GAME OVER SCREEN */
void lose_splash() {
    clear();
    mvprintw(game_row/2 - 1, game_col/2-strlen(LOST_MSG0)/2, LOST_MSG0);
    mvprintw(game_row/2, game_col/2-strlen(LOST_MSG1)/2, LOST_MSG1);
    refresh();
}

/* DRAWING WALLS */
void level_create() {
    for (int i=0; i<game_row; i++) {
        mvaddch(i, 0, WALL_CHAR);
        mvaddch(i, game_col-1, WALL_CHAR);
    }
    for (int i=1; i<game_col-1; i++) {
        mvaddch(0, i, WALL_CHAR);
        mvaddch(game_row-1, i, WALL_CHAR);
    }
    
    mvprintw(game_row+1, game_col/2-strlen(P_STAMP)/2, P_STAMP);
}

/* CHECKING GAME STATE (AFTER EVERY STEP) */
void game_state_update() {

	mvprintw(game_row, game_col/2-strlen(G_SCORE)/2, G_SCORE,score);	
	
	
    if (snakeLength == MAX_LENGTH-1) {
    	char c;
        winner_splash();
        timeout(-1);
        c = getch();
        endwin();
	exit(0);
    }
   
    if ((mvinch(snake[0].y, snake[0].x) & A_CHARTEXT) == WALL_CHAR) {
    	char c;
        lose_splash();
        timeout(-1);
	c = getch();
        endwin();
	exit(0);
    }
}

/* REFRESH - SNAKE MOVEMENTS */
void move_snake_full() {
    move_snake_head();
    game_state_update();
    mvaddch(snake[0].y, snake[0].x, SNAKE_CHAR);
    if (snake[0].x == food.x && snake[0].y == food.y) {
        snakeLength++;
        add_food();
        score += 10;
        if(speed != 60)
        	speed -= 5;
        else
        	speed = 60;
    } else {
        move_snake_tail();
	}
}
/* ---------------------------------------------------------------------------------- */