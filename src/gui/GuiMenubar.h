#ifndef GUIMENUBAR_H
#define GUIMENUBAR_H
#include "GuiWidget.h"
#include "../Sprite.h"

class GuiMenubar: public GuiWidget
{
public:
  void onDraw();
  GuiMenubar();
  void onMouseMotion(char buttonstate, int x, int y, int dx, int dy);
  void onMouseFocus(char on);
  void onMouseButton(char, char, int, int);
private:
  static Sprite menubarSprite;
  static Rectangle fromR;
  static Rectangle item1_screen;
  static Rectangle item1_sprite;
  int focus;
};

#endif
