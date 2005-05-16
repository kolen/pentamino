#ifndef GUIMENUBAR_H
#define GUIMENUBAR_H
#include "GuiWidget.h"
#include "../Sprite.h"

class GuiMenubar: public GuiWidget
{
public:
  void onDraw();
  GuiMenubar();
private:
  static Sprite menubarSprite;
};

#endif
