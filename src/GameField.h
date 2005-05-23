#ifndef GAMEFIELD_H
#define GAMEFIELD_H

// $Id: GameField.h,v 1.4 2005/05/23 17:53:40 kolen Exp $


#include "Shape.h"
#include "Shell.h"
#include <string>

#define IS_SHAPE 0x10

class GameField: public ShellUser
{
 public:
  static const int width=37, height=29;
  int selected;
  int isSelected;
  bool isEditing;
 
  GameField();
  void updateShape(int num);
  void removeShape(int num);
  int getShapeAt(int x, int y);
  int tryFit(int n, int x, int y);
  void selectShape(int n);
  
  void clear(bool edit = false);
  int loadFile(std::string filename, bool edit = false);
  int saveFile(std::string filename);
 
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
  int onCommand(int cmdId, std::string &command, std::list<std::string> &args);
 private:
  Shape shapes[12];
  char tiles[width][height];
  char shapenums[width][height];
  void divideShape(int n);
 
  static const int CMD_save      = 1;
  static const int CMD_load      = 2;
  static const int CMD_edit      = 3;
  static const int CMD_editnew   = 4;  
};

#endif
