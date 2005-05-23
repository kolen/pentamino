#ifndef GUIMENU_H
#define GUIMENU_H

// $Id: GuiMenu.h,v 1.3 2005/05/23 14:17:25 kolen Exp $

#include "GuiWidget.h"
#include "../Sprite.h"
#include "../Shell.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define MENUWIDTH 200
#define MENULINEHEIGHT 16
#define MENUTEXTOFFSET_X 16
#define MENUTEXTOFFSET_Y 2

struct MenuItem
{
  string text;
  string action;
};

class GuiMenu: public GuiWidget
{
 public:
  GuiMenu(int x, int y);
  void onDraw();
  void addItem(string text, string action);
  void onMouseFocus(char on);
  void onMouseMotion(char buttonstate, int x, int y, int dx, int dy);
  void onMouseButton(char, char, int, int);
  void onClickOutside(char down, char button, int x, int y);
  void bury();
 private:
  vector<MenuItem> items;
  int lastSelected;
  static Sprite gfx;
  static Rectangle gfx_area_header;
  static Rectangle gfx_area_item;
  static Rectangle gfx_area_footer;
  static Rectangle gfx_area_item_sel;
 
  int getInFocus();

};

#endif
