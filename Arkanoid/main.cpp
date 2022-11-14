#include <stdio.h>
#include <curses.h>

struct Display
{
    static const int XMAX = 80;
    static const int YMAX = 24;

    char dmatrix[YMAX][XMAX];
} display;

struct Board
{
    static const int XMAX = display.XMAX - 1;
    static const int YMAX = display.YMAX - 1;

    char bmatrix[YMAX][XMAX];
} board;

struct Racket
{
    int xpos;
    int ypos;
    static const int width = 8;

    char rarr[1][width];
} racket;

struct Ball
{
    int xpos;
    int ypos;

    char barr[1][1];
} ball;

void createDisplay()
{
    for (int i = 0; i < display.YMAX; ++i){
        for (int j = 0; j < display.XMAX; ++j){
            display.dmatrix[i][j] = '@';
        }
    }

    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
}

void printDisplay()
{
    for (int i = 0; i < display.YMAX; ++i){
        for (int j = 0; j < display.XMAX; ++j){
            move(i, j);
            addch(display.dmatrix[i][j]);
        }
    }
}

void createBoard()
{
    for (int i = 1; i < board.YMAX; ++i){
        for (int j = 1; j < board.XMAX; ++j){
            board.bmatrix[i][j] = ' ';
        }
    }
}

void printBoard()
{
    for (int i = 1; i < board.YMAX; ++i){
        for (int j = 1; j < board.XMAX; ++j){
            move(i, j);
            addch(board.bmatrix[i][j]);
        }
    }
}

void createRacket()
{
    racket.xpos = (board.XMAX - racket.width) / 2;
    racket.ypos = board.YMAX - 1;
}

void printRacket()
{
    for (int i = racket.xpos; i < racket.xpos + racket.width; ++i)
    {
        move(racket.ypos = board.YMAX - 1, i);
        addch(racket.rarr[racket.ypos][i] = 'x');
    }
}

void moveRacket()
{
    int ch = getch();

    switch(ch)
    {
    case KEY_LEFT:
        --racket.xpos;
        break;

    case KEY_RIGHT:
        ++racket.xpos;
        break;
    }

    if (racket.xpos < 1)
    {
        racket.xpos = 1;
    }

    if (racket.xpos > board.XMAX - racket.width)
    {
        racket.xpos = board.XMAX - racket.width;
    }

    for (int i = racket.xpos; i < racket.xpos + racket.width; ++i)
    {
        move(racket.ypos = board.YMAX - 1, i);
        addch(racket.rarr[racket.ypos][i]);
    }
}

void createBall()
{
    ball.xpos = racket.xpos + racket.width / 2 - 1;
    ball.ypos = racket.ypos - 1;
}

void moveBall()
{
    ball.xpos = racket.xpos + racket.width / 2 - 1;
    ball.ypos = racket.ypos - 1;
    move(ball.ypos, ball.xpos);
    addch(ball.barr[ball.ypos][ball.xpos] = 'o');
}

int main()
{
    createDisplay();
    createBoard();
    createRacket();
    createBall();
    printDisplay();

    do
    {
        printBoard();
        printRacket();
        moveBall();
        moveRacket();
    }
    while (racket.xpos != 200);

    return 0;
}
