#ifndef GAMEFIELD_H
#define GAMEFIELD_H

// $Id: GameField.h,v 1.2 2005/05/17 17:38:10 kolen Exp $


#include "Shape.h"
#include <string>

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
  
  void clear(bool edit = false);
  int loadFile(std::string filename, bool edit = false);
 
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
  void divideShape(int n);
};

#endif
