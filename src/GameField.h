#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "Shape.h"

#define IS_SHAPE 0x10

class GameField
{
 public:
  static const int width=37, height=29;
  int selected;
  int isSelected;
 
  GameField();
  void updateShape(int num);
  void removeShape(int num);
  int getShapeAt(int x, int y);
  int tryFit(int n, int x, int y);
  void selectShape(int n);
  inline char& at(int x, int y)
  {
    return shapenums[x][y];
  }
  inline char& tileAt(int x, int y)
  {
    return tiles[x][y];
  }
  inline Shape &shape(int num)
  {
    return shapes[num];
  }
  inline Shape &selectedShape()
  {
    return shapes[selected];
  }
  
 private:
  Shape shapes[12];
  char tiles[width][height];
  char shapenums[width][height];
};

#endif
