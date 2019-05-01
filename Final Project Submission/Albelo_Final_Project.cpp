// Project Name: Simple Snake
// Project purpose: entertain with a simple game of Snake
// Author: Oreste Albelo
// Date last modified: 5/1/2019


#include <iostream>
#include <cstdlib> // for rand function
#include <conio.h> // for getting presses
#include <windows.h> // slow game down
using namespace std;

bool game_Over;

// Needed for the "map"
const int width = 20;
const int height = 20;

//stuff for score and location
int x;
int y;
int apple_x;
int apple_y;
int score;

// tail
int tail_x[100];
int tail_y[100];
int nTail;

// directional input Variables
enum eDirection { STAND = 0, LEFT, RIGHT, UP, DOWN};
eDirection direction;

// Setup everything
void start()
{
   game_Over = false; // set game state

   direction = STAND; // starting direction

   x = width / 2;
   y = height / 2;

   apple_x = rand() % width;
   apple_y = rand() % height;

   score = 0;

}

// Player input
void input()
{
    if (_kbhit()) // if keyboard is pressed it will return value
    {
        switch (_getch())
        {
            case 'a':
              direction = LEFT;
              break;
            case 'd':
              direction = RIGHT;
              break;
            case 'w':
              direction = UP;
              break;
            case 's':
              direction = DOWN;
              break;
            case 'l':
              game_Over = true;
              break;

        }
    }
}

// Show the board
void show()
{
    system("cls"); // constantly wipe the screen

      cout << "Score: " << score << "\t\t" << "move with 'w, a, s, d keys'" << endl; // show score


    // create top wall;  w = width
    for (int w = 0; w < width + 1; w++)
      {
        cout << "#";
      }

        cout << endl; // go to next line

    // create side walls
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
          if (w == 0)
          {
             cout << "#";
          }
          if (h == y && w == x)
          {
             cout << "O";
          }
          else if (h == apple_y && w == apple_x)
          {
             cout << "@";
          }
          else
          {
            bool show = false; // has tail been displayed?
             for (int tail = 0; tail < nTail; tail++)
             {

               if (tail_x[tail] == w && tail_y[tail] == h)
               {
                 cout << "o";
                 show = true;
               }
             }
             if (!show)
             {
               cout << " ";
             }
          }
          if ( w == width - 1)
          {
             cout << "#";
          }
        }
        cout << endl; // make sure each line is printed
    }

    // create bottom wall;  w = width
    for (int w = 0; w < width + 1; w++)
      {
        cout << "#";
      }
        cout << endl;
}

//
void rules()
{
    // these are locational values for the tail for updating purposes
    int prevX = tail_x[0];
    int prevY = tail_y[0];
    int prev2X;
    int prev2Y;

    // attaches tail to head
    tail_x[0] = x;
    tail_y[0] = y;

    for(int i = 1; i < nTail; i++)
    {
      prev2X = tail_x[i];
      prev2Y = tail_y[i];
      tail_x[i] = prevX;
      tail_y[i] = prevY;
    }

  switch (direction) // change direction
  {
    case LEFT:
      x--;
      break;
    case RIGHT:
      x++;
      break;
    case UP:
      y--;
      break;
    case DOWN:
      y++;
      break;
  }
  if (x > width || x < 0 || y > height || y < 0) // lose if out of bounds
  {
    game_Over = true;
  }
  if (x == apple_x && y == apple_y)
  {
      score += 1;
      apple_x = rand() % width;
      apple_y = rand() % height;
      nTail++;
  }

}

int main()
{
    start();

    while (!game_Over)
    {
      show();
      input();
      rules();
      Sleep(25); // game was too fast
    }
    if (game_Over == true)
    {
      cout << "YOU LOSE!!!!" << endl;
    }
    return 0;
}
