#ifndef GUISHAPESEL_H
#define GUISHAPESEL_H

#include <iostream>

#include "GuiWidget.h" 
#include "../Sprite.h"
#include "../GameField.h"

#define KUBE_SIZE 40
#define SHAPESEL_LOCATION 600

class GuiShapeSel: public GuiWidget
{
 public:
  void onDraw();
  void onMouseButton(char, char, int, int);
  GuiShapeSel();
  void setGameField(GameField *gf1)
    {
      gf = gf1;
    }
 private:
  static Sprite shapesSprite;
  GameField *gf;
};

#endif
