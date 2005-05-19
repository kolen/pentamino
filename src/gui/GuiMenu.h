#ifndef GUIMENU_H
#define GUIMENU_H

// $Id: GuiMenu.h,v 1.1 2005/05/19 15:00:50 kolen Exp $

#include "../Sprite.h"
#include "GuiWidget.h"
#include <string>
#include <list>
using namespace std;

#define MENUWIDTH 200
#define MENULINEHEIGHT 32

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
 private:
  list<MenuItem> items;
  
  static Sprite gfx;
  static Rectangle gfx_area_header;
  static Rectangle gfx_area_item;
  static Rectangle gfx_area_footer;

};

#endif
