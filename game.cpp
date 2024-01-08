#include "print.h"
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <iostream>
#include <cstdlib>

bool gameOver;
const int width = 20;
const int heigth = 20;

struct point
{
    int x;
    int y;
};

int x, y, fruitX, fruitY, score;
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGTH,
    UP,
    DOWN
};
eDirection dir;
int tailX[100], tailY[100];
int nTail;

void setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = heigth / 2;
    fruitX = rand() % width;
    fruitY = rand() % heigth;
    score = 0;
}

void draw()
{
    clear();
    for (size_t i = 0; i <= width; i++)
    {
        printw("#");
    }
    printw("\n");

    for (size_t i = 0; i < heigth; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
            {
                printw("#");
            }
            if (i == y && j == x)
            {
                printw("G");
            }
            else if (i == fruitY && j == fruitX)
            {
                printw("O");
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        print = true;
                        printw("g");
                    }
                }
                if (!print)
                {
                    printw(" ");
                }
            }
        }
        printw("\n");
    }

    for (size_t i = 0; i <= width; i++)
    {
        printw("#");
    }
    printw("\n");
    printw("Score ");

    std::string str = std::to_string(score);
    const char *charArray = str.c_str();
    printw(charArray);
    printw("\n");
    printw("\n");
}

void input()
{
    int ch = getch();
    if (ch != -1)
    {
        switch (ch)
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGTH;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }

    // if (x >= width || x <= 0 || y >= heigth || y <= 0){
    //   gameOver = true;
    //}

    if (x >= width)
    {
        x = 0;
    }
    else if (x < 0)
    {
        x = width - 2;
    }

    if (y >= heigth)
    {
        y = 0;
    }
    else if (x < 0)
    {
        y = heigth - 1;
    }

    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % heigth;
        nTail++;
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

        for (int i = 0; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGTH:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
}

int main()
{
    initscr();
    setup();
    while (!gameOver)
    {
        draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        input();
        logic();
    }

    println("");
    println("Game over");
    return 0;
}
