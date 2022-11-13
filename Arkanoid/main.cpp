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
    //getch();
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
    //getch();
}

void createRacket()
{
    racket.xpos = (board.XMAX - racket.width) / 2;
    racket.ypos = board.YMAX - 1;

    for (int i = racket.xpos; i < racket.xpos + racket.width; ++i){
        racket.rarr[racket.ypos][i] = 'x';
    }
}

void printRacket()
{
    for (int i = racket.xpos; i < racket.xpos + racket.width; ++i)
    {
        move(racket.ypos = board.YMAX - 1, i);
        addch(racket.rarr[racket.ypos][i] = 'x');
    }
    //getch();
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

int main()
{
    createDisplay();
    createBoard();
    createRacket();
    printDisplay();

    do
    {
        printBoard();
        printRacket();
        moveRacket();
    }
    while (racket.xpos != 200);

    return 0;
}
