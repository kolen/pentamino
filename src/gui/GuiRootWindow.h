#ifndef GUIROOTWINDOW_H
#define GUIROOTWINDOW_H

#include "GuiContainer.h"
#include "GuiShapeSel.h"
#include "GuiField.h"
#include "GuiMenubar.h"
#include "../GameField.h"


class GuiRootWindow: public GuiContainer
{
 public:
  //void onMouseButton(char down, char button, int x, int y);
  //void onMouseMotion(char buttonstate, int x, int y, int dx, int dy);
  GuiRootWindow();
  
  GuiShapeSel shapeSel;
  GuiField field;
  GuiMenubar menubar;
 
  void setGameField(GameField *gf)
    {
      field.setGameField(gf);
      shapeSel.setGameField(gf);
      std::cerr << "sgf!\n";
    }
};

#endif
