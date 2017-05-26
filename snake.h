/* ----------------------------- MACRO DEFINITIONS ----------------------------------- */
/* MAX_LENGTH: Once the snake's length reached MAX_LENGTH, the user wins the game */
#define MAX_LENGTH 			200

/* WIN_MSG(0-1): This is the string displayed once you win the game */
#define WIN_MSG0 			"Congratulations! You Just Won The Game"
#define WIN_MSG1			"Your score was <%d>"

/* WELCOME_MSG(0-1): This is the string displayed before you start the game */
#define WELCOME_MSG0 		":: Snake 2D by Aditya Sathish::"
#define WELCOME_MSG1		":: Press any key to START ::"

/* LOST_MSG(0-1): This is the string displying once you lose the game */
#define LOST_MSG0 			":: GAME OVER ::"
#define LOST_MSG1			":: Press any key to EXIT ::"

/* P_STAMP: This string is put at the bottom of the window during the game execution */
#define P_STAMP				"2016 - Aditya Sathish"

/* G_SCORE: This string contains the score which is displayed during the game execution */
#define G_SCORE				"Score - %d"

/* SNAKE_CHAR: This is what represents the snake */
#define SNAKE_CHAR 			'O'

/* FOOD_CHAR: This represent the food */
#define FOOD_CHAR 			'@'

/* WALL_CHAR: This represents the wall during the game execution */
#define WALL_CHAR 			'*'

/* UP/DOWN/LEFT/RIGHT: Enumerate the keyboard controls */
#define UP 					1
#define DOWN 				2
#define LEFT 				3
#define RIGHT 				4
/* ------------------------------------------------------------------------------------ */

/* ------------------------------ TYPE DEFINITION ------------------------------------- */
/* 
	_snake: A type definition to represent a structure for the snake (in OOPs, it 
	would be an object) 
*/
typedef struct _snake {
    int x;
    int y;
} snake_body;

/* 
	_food: A type definition to represent a structure for the food (in OOPs, it 
	would be an object)
*/
typedef struct _food {
    int x;
    int y;
} food_body;
/* ------------------------------------------------------------------------------------ */

/* ------------------------- FUNCTION DECLARATIONS ------------------------------------- */
/*
	init_game():	This function sets up the window environment for the game before
					starting the game
*/
int init_game(void);

/*
	add_food(): 	This function is responsible for calculating the position of the food at random places
*/
void add_food(void);

/*
	draw_food():	Drawing the food at the position defined by add_food()
*/
void draw_food(void);

/*
	init_snake(): 	Setting up the position of the snake
*/
void init_snake(void);
/*
	draw_snake():	Drawing the snake on the screen
*/
void draw_snake(void);
/*
	move_snake():	Handles the movement of the snake. That is, it is responsible for 
					subtracting a tail element and adding a head element as it moves
					in the particular direction.
*/
void move_snake(void);
/*
	move_snake_head(): 	Responsible for moving the snake head according to the direction
						of the keyboard input.
*/
void move_snake_head(void);
/*
	move_snake_tail():	Removes the tail as the snake moves
*/
void move_snake_tail(void);
/*
	map_control():		Responsible for converting the keyboard input into the enums described in the macros
*/
void map_control(char);
/*
	winner_splash():	Responsible for showing the congratulatory splash screen
*/
void winner_splash(void);
/*
	welcome_splash():	Responsible for displaying the welcome screen before the start of the game
*/
void welcome_splash(void);
/*
	lose_splash():		Responsible for creating the splash screen and displaying it once you lose (hit the wall or yourself)
*/
void lose_splash(void);
/*
	level_created():	Sets up by drawing the walls.
*/
void level_create(void);
/*
	game_state_update():	Checks the game state after every step. Updates score, shows splash screens, etc.
*/
void game_state_update(void);
/*
	move_snake_full():		
*/
void move_snake_full(void);
/* ------------------------------------------------------------------------------------ */