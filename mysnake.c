/*
	Programmer				:	Aditya Sathish
	Date Modified			:	20th January 2016
	
	File Name				:	mysnake.c
	
	Description				:	Classic Snake Game based off Nokia's famous game during their 3310-era.
	
	NOTES					:	Tried and tested using Ubuntu 16.04 LTS
	
	HOW TO COMPILE			:	This program uses curses.h header for some functions. Therefore, inorder to run this game,
								Make sure you download the curses.h header file into your linux machine.
								To do this, run this command type in this (without the $ character):
						
								$ sudo apt-get install libncurses5-dev
						
								After you install it. Make sure you compile it with a rule to like it to ncurses
						
								$ gcc mysnake.c -lncurses
						
	ORIGINAL WORK			:	petrvolny (http://github.com/petrvolny)
	
	LICENSING INFORMATION	:	GNU General Purpose License
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <curses.h>

/* WINDOW INFORMATION */
#define MAX_LENGTH 			200
#define WIN_MSG0 			"Congratulations! You Just Won The Game"
#define WIN_MSG1			"Your score was <%d>"
#define WELCOME_MSG0 		":: Snake 2D by Aditya Sathish::"
#define WELCOME_MSG1		":: Hit [ENTER] to START ::"
#define LOST_MSG 			":: GAME OVER :: TRY AGAIN ::"
#define P_STAMP				"2016 - Aditya Sathish"
#define G_SCORE				"Score - %d"
#define SNAKE_CHAR 			'O'
#define FOOD_CHAR 			'@'
#define WALL_CHAR 			'*'

/* GAME CONTROLS */
#define UP 					1
#define DOWN 				2
#define LEFT 				3
#define RIGHT 				4

/* CREATING STRUCTURES FOR THE SNAKE AND THE FOOD */
typedef struct SnakePart_ {
    int x;
    int y;
} SnakePart;

typedef struct Food_ {
    int x;
    int y;
} Food;
Food food;
SnakePart snake[MAX_LENGTH];

/* CREATING SOME VARIABLES */
int direction;
int snakeLength = 1;
int row, col;
int game_row, game_col;
int score = 0;
int speed = 100;

/* GAME INITIALIZATION */
int init_game(void) {

	// 	Seeding the Number Generator with Current System Time
    srand(time(NULL));
    
    // 	Setting the snake to be off the window then starting
    for (int i=0; i<MAX_LENGTH; i++) {
        snake[i].x = -1;
        snake[i].y = -1;
    }

	// 	Initalizing ncurses Structures and Terminfo Files 
    initscr();
    
    // 	Checking if terminal supports colors. If not, the game is ended
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}

	/* 	Finding the number of columns and rows in a given window
		- stdscr is the pointer to the window where the program is running
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

/* ADDING FOOD AT A RANDOM POINT ON SCREEN */
void addFood() {
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
void drawFood() {
	// Setting the food character at the position defined by the food structure
    move(food.y, food.x);
    
    // Setting the character at the location to be FOOD_CHAR macro
    addch(FOOD_CHAR);
}

/* SETTING UP THE SNAKE DRAWABLE */
void initSnake() {
	// How the snake is located when it starts
    snake[1].x = 2;
    snake[1].y = game_row/2;
    snake[0].x = 3;
    snake[0].y = game_row/2;
    snakeLength = 2;
    direction = RIGHT;
}

/* DRAWING POSITION OF SNAKE */
void drawSnake() {
    int i=0;
    
    // Translation of snake as long as it stays in the bounds of the window
    while (snake[i].x != -1 && snake[i].y != -1) {
        move(snake[i].y, snake[i].x);
        addch(SNAKE_CHAR);
        i++;
    }
}

/* MOVEMENT OF SNAKE */
void shiftSnake() {
    int i=0;
    
    // Helping the snake move
    for (int i=snakeLength-1; i>=0; i--) {
        snake[i+1] = snake[i];
    }
}

/* MOVING THE SNAKE HEAD BASED ON KEYBOARD INPUT */
void addHead() {

     SnakePart origHead = snake[0];
     shiftSnake();
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
void removeTail() {
    mvaddch(snake[snakeLength].y, snake[snakeLength].x, ' ');
    snake[snakeLength].x = -1;
    snake[snakeLength].y = -1;
}

/* CONVERTING KEYBOARD INPUT */
void setDirection(char c) {
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
void showWinner() {
    clear();
    mvprintw(game_row/2-1, game_col/2-strlen(WIN_MSG0)/2, WIN_MSG0);
    mvprintw(game_row/2, game_col/2-strlen(WIN_MSG1)/2, WIN_MSG1);
    refresh();
}

/* DRAW THE SPLASH SCREEN */
void showWelcome() {
    clear();
    mvprintw(game_row/2-1, game_col/2-strlen(WELCOME_MSG0)/2, WELCOME_MSG0);
    mvprintw(game_row/2, game_col/2-strlen(WELCOME_MSG1)/2, WELCOME_MSG1);
    refresh();
}

/* DRAW THE GAME OVER SCREEN */
void showLose() {
    clear();
    mvprintw(game_row/2, game_col/2-strlen(LOST_MSG)/2, LOST_MSG);
    refresh();
}

/* DRAWING WALLS */
void drawLevel() {
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
void checkGame() {

	mvprintw(game_row, game_col/2-strlen(G_SCORE)/2, G_SCORE,score);	
	
	
    if (snakeLength == MAX_LENGTH-1) {
        showWinner();
        timeout(-1);
        getch();
        endwin();
        exit(0);
    }
   
    if ((mvinch(snake[0].y, snake[0].x) & A_CHARTEXT) == WALL_CHAR) {
        showLose();
        timeout(-1);
        getch();
        endwin();
        exit(0);
    }
}

/* REFRESH - SNAKE MOVEMENTS */
void moveSnake() {
    addHead();
    checkGame();
    mvaddch(snake[0].y, snake[0].x, SNAKE_CHAR);
    if (snake[0].x == food.x && snake[0].y == food.y) {
        snakeLength++;
        addFood();
        score += 10;
        if(speed != 60)
        	speed -= 5;
        else
        	speed = 60;
    } else {
        removeTail();
	}
}

/* MAIN FUNCTION */
int main() {
    char c;

    init_game();
    showWelcome();
    getch();
    clear();
    initSnake();
    drawLevel();
    drawSnake();
    addFood();
    refresh();

    // Main game loop
    while (1) {
        timeout(speed);
        c = getch();
        setDirection(c);
        clear();
        drawLevel();
        moveSnake();
        checkGame();
        drawSnake();
        drawFood();
        refresh();
    }
}
