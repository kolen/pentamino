#ifndef SERVICE_H
#define SERVICE_H

#include <SDL/SDL.h>

struct Point
{
  int x;
  int y;
};

struct Rectangle: SDL_Rect
{
  int in(int x1, int y1)
  {
    return (x1>=x && x1<(x+w) && y1>=y && y1<=(y+h));
  }
  Rectangle(Sint16 x1, Sint16 y1, Uint16 w1, Uint16 h1)
  {
    x = x1; y = y1; w = w1; h = h1;
  }
  Rectangle(Sint16 x1, Sint16 y1)
  {
    x = x1; y = y1;
  }
  Rectangle(){}
};

#endif
