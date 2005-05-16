#ifndef GUIWIDGET_H
#define GUIWIDGET_H

#include "GuiDrawContext.h"
#include "../Service.h"
#include <SDL/SDL_keyboard.h>

class GuiWidget
{
 public:
  virtual void onDraw();
  virtual void onMouseButton(char down, char button, int x, int y);
  virtual void onMouseMotion(char buttonstate, int x, int y, int dx, int dy);
  virtual void onKeyboard(char down, SDL_keysym keysym);
  virtual void onMouseFocus(char on);
  GuiDrawContext draw;
  static int dirty;
  GuiWidget(); 
  
  Rectangle rect;
  
  void setRect(Rectangle rect);
  void setDirty();
  int ifDirty();
 
  char visible;
};

#endif
