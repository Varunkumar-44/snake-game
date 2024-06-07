

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROWS 25
#define COLS 75

// terminal escape codes/ANSI escape codes (or ANSI escape sequences)
// "\x1B" is the escape character that tells your terminal that what comes next is not meant to be printed on the screen, 
// but rather a command to the terminal (or most likely terminal emulator).
// Turn escape codes ON.
// Turn escape codes ON.

typedef struct node {
    int x;
    int y;
    struct node* next;
    struct node* prev;
}NODE;

typedef struct SNAKE {
    NODE* head;
    NODE* tail;

}SNAKE;

// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the position.
//     y: the column of the position.
void gotoxy( int x, int y );

// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds. 
void sleep( float secs );

//My Functions///
void init( void );
void print( SNAKE* snake );
void initialTheBoard( char board[ROWS][COLS] );//Initial the board limits and print them
void initialSnaKE( SNAKE* snake );//initial the snake in the middle
void snakeSpeed( float* delay, int counter );
void checkInput( SNAKE* snake, char* keystoke, char* lastmove, int * newX, int * newY );//Check if to change the snake direction
void SnakeMovment( SNAKE* snake, int counter, float* delay, int newX, int newY, char board[ROWS][COLS] );//move the snake
bool checkIfGameOver( SNAKE* snake, char matrix[ROWS][COLS], int newX, int newY );//check if the game is over
void GameOverPrint( char board[ROWS][COLS] );//Print game over in the middle of the screen when the player lose 
void printBoard( char board[ROWS][COLS] );

int main() {

    //variables that will be used in the game
    float delay = 1.000;
    int newX = 0, newY = 0;
    int x = ROWS / 2, y = COLS / 2, count = 0;;
    bool gameOver = false;
    char keystroke = 'd', lastmove = 'd';
    char Boardmatrix[ROWS][COLS];
    //intial the snake and put him in the middle
    SNAKE* snake = (SNAKE*)malloc( sizeof( SNAKE ) );
    initialSnaKE( snake );
    initialTheBoard( Boardmatrix );
    //The Game
    while ( gameOver == false )
    {
        init();
        printBoard( Boardmatrix );
        print( snake );
        count++;
        _kbhit();
        keystroke = _getch();
        checkInput( snake, &keystroke, &lastmove, &newX, &newY );
        gameOver = checkIfGameOver( snake, Boardmatrix, newX, newY );
        SnakeMovment( snake, count, &delay, newX, newY, Boardmatrix );
        snakeSpeed( &delay, count );
        sleep( delay );
    }
    GameOverPrint( Boardmatrix );
}

void initialSnaKE( SNAKE* snake )//maybe x,y of tail need to be different
{
    //Snake start in the middle with the right values
    //Need to add malloc
    NODE* newNode = (NODE*)malloc( sizeof( NODE ) );
    newNode->x = ROWS / 2;
    newNode->y = COLS / 2;
    snake->head = newNode;
    snake->tail = newNode;
    snake->head->prev = NULL;
    snake->head->next = NULL;
}

void initialTheBoard( char board[ROWS][COLS] )
{
    for ( int i = 0; i < ROWS; i++ ) {
        for ( int j = 0; j < COLS; j++ ) {
            board[i][j] = ' ';
        }
    }

    for ( int i = 0; i < ROWS; i++ ) {
        board[i][0] = '#';
        board[i][COLS - 1] = '#';
    }
    for ( int i = 0; i < COLS; i++ ) {
        board[0][i] = '#';
        board[ROWS - 1][i] = '#';
    }
}

void printBoard( char board[ROWS][COLS] ) {
    for ( int i = 0; i < ROWS; i++ ) {
        for ( int j = 0; j < COLS; j++ ) {
            printf( "%c", board[i][j] );
        }
        printf( "\n" );
    }
}

void checkInput( SNAKE * snake, char* keystoke, char* lastmove, int* newX, int* newY )
{
    if ( *lastmove != 's' && *keystoke == 'w' ) {
        snake->head->x = snake->head->x - 1;
        *newX = -1;
        *newY = 0;
        *lastmove = 'w';

    }
    else if ( *lastmove != 'w' && *keystoke == 's' ) {
        snake->head->x = snake->head->x + 1;
        *lastmove = 's';
        *newX = 1;
        *newY = 0;
    }
    else if ( *lastmove != 'a' && *keystoke == 'd' ) {
        snake->head->y = snake->head->y + 1;
        *lastmove = 'd';
        *newX = 0;
        *newY = 1;
    }
    else if ( *lastmove != 'd' && *keystoke == 'a' ) {
        snake->head->y = snake->head->y - 1;
        *lastmove = 'a';
        *newX = 0;
        *newY = -1;
    }
    else {
        if ( *lastmove == 'a' ) {
            snake->head->y = snake->head->y - 1;
            *newX = 0;
            *newY = -1;
        }
        if ( *lastmove == 'd' ) {
            snake->head->y = snake->head->y + 1;
            *newX = 0;
            *newY = 1;
        }
        if ( *lastmove == 'w' ) {
            snake->head->x = snake->head->x - 1;
            *newX = -1;
            *newY = 0;
        }
        if ( *lastmove == 's' ) {
            snake->head->x = snake->head->x + 1;
            *newX = 1;
            *newY = 0;
        }
    }
}

void SnakeMovment( SNAKE* snake, int counter, float* delay, int newX, int newY, char board[ROWS][COLS] ) {
    
    if (counter < 5) {
        print(snake);

    }
    else {

    NODE* newHead = (NODE*)(malloc( sizeof( NODE ) ));
    NODE* oldHead = (NODE*)(malloc( sizeof( NODE ) ));
    newHead->x = snake->head->x + newX;
    newHead->y = snake->head->y + newY;
    oldHead = snake->head;
    snake->head = newHead;
    snake->head->next = oldHead;
    oldHead->prev = snake->head;
    board[snake->head->x][snake->head->y] = '@';

    
                if (counter % 5 != 0) {
                    board[snake->tail->x][snake->tail->y] = ' ';
                    NODE* oldTail;
                    oldTail = snake->tail->prev;
                    snake->tail->prev = oldTail->prev;
                    free(oldTail);
                }
                print(snake);
            }wsaad
}

void snakeSpeed( float *delay, int counter )
{
    if ( *delay > 100 && counter % 5 == 0 )
    {
        *delay -= (float)0.300;
    }
}


// Turn escape codes ON.
void init( void ) {
    system( "cls" );
}




bool checkIfGameOver( SNAKE* snake, char matrix[ROWS][COLS], int newX, int newY )
{
    int theX = snake->head->x, theY = snake->head->y;
    if ( matrix[theX + newX][theY + newY] != ' ' ) {
        return true;
    }
    else {
        return false;
    }
}

void print( SNAKE* snake ) {
    NODE* snakeTailPtr = snake->tail;
    while ( snakeTailPtr != NULL ) {
        gotoxy( snakeTailPtr->x, snakeTailPtr->y );
        snakeTailPtr = snakeTailPtr->prev;
        printf( "@" );
    }
}


void GameOverPrint( char board[ROWS][COLS] )//need to add board clean
{
    initialTheBoard( board );
    char gameOverMessage[10] = "Game Over";
    int j = 0;
    int middleCol = (COLS / 2);
    for ( int i = middleCol - 4; i <= middleCol + 4; i++ ) {
        board[ROWS / 2][i] = gameOverMessage[j];
        j++;
    }
    printBoard( board );
    for ( int i = 0; i < ROWS; i++ ) {
        printf( "\n" );
    }

}

// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the position.
//     y: the column of the posiiton.
void gotoxy( int x, int y ) {
    printf( "\x1b[%d;%df", x, y );
}


void sleep( float secs ) {
    clock_t clocks_start = clock();

    while ( clock() - clocks_start < secs * CLOCKS_PER_SEC );
}