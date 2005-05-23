#ifndef GUIROOTWINDOW_H
#define GUIROOTWINDOW_H

#include "GuiContainer.h"
#include "GuiShapeSel.h"
#include "GuiField.h"
#include "GuiMenubar.h"
#include "GuiMenu.h"
#include "Shell.h"
#include "../GameField.h"


class GuiRootWindow: public GuiContainer, public ShellUser
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
    }
  int onCommand(int, std::string&, std::list<std::string>&);
  void newmenuCreate();
  
  static const int CMD_menu    = 1;
  static const int CMD_mplus   = 2;
  static const int CMD_menuend = 3;
private:
  string newmenu_title;
  int newmenu_pos[2];
  struct mitem{
    string title;
    string cmd;
  };
  list<mitem> newmenu_items;
};

#endif
