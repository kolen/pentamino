#include "GameField.h"
#include <cstring>
#include <cassert>
#include <iostream>

GameField::GameField()
{
  std::memset(tiles, 0x10, sizeof(tiles));
  std::memset(shapenums, 0x00, sizeof(tiles));

  isSelected = selected = 0;

  //Ставим начальное поле которое будет после запуска
  for (int i = 0; i< 12; i++)
    {
      shapes[i].num = i;
      shapes[i].x = 20 + (i%3) * 6;
      shapes[i].y = (i/3) * 6;
      updateShape(i);
    }
}

void
GameField::removeShape(int num)
{
  int x, y, xt, yt;
  Shape &thisshape = shape(num);
  if (!thisshape.isOnField) return;

  for (x=0; x<5; x++)
    for (y=0; y<5; y++)
      if (thisshape.at(x, y))
        {
          at(x+thisshape.x, y+thisshape.y) = 0;
          tileAt(x+thisshape.x, y+thisshape.y) = 0x10;
        }
  thisshape.isOnField = 0;
}

void 
GameField::updateShape(int num)
{
  Shape &tshape = shapes[num];
  int x, y;
  for (x=0; x<5; x++)
    for (y=0; y<5; y++)
      {
        if (tshape.at(x, y)) {
          tileAt(x + tshape.x, y + tshape.y) = tshape.at(x, y) & 0x0f;
          at(x + tshape.x, y+tshape.y) = num | 0x10;
        }
      }
  
  tshape.updateLastPos();
  tshape.isOnField = 1;
}

int GameField::getShapeAt(int x, int y)
{
  if (at(x, y) & 0x10)
    {
      return at(x, y) & 0x0f;
    }
  else
    {
      return -1;
    }
}

int GameField::tryFit(int n, int x, int y)
{
  Shape &sh = shapes[n];
  int xx, yy;

  for (xx=0; xx<5; xx++)
    for (yy=0; yy<5; yy++)
      {
        if (sh.at(xx, yy) && (at(xx+x, yy+y) & IS_SHAPE))
          return 0;
      }
  return 1;  
}

void
GameField::selectShape(int n)
{
  if (isSelected)
    {
      selected = n;
    }
  else
    {
      if (shape(n).isOnField)
        removeShape(n); 
      isSelected = 1;
      selected = n;
    }
}
