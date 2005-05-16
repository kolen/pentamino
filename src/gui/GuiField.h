#ifndef GUIFIELD_H
#define GUIFIELD_H

#include "GuiWidget.h"
#include "../GameField.h"
#include "../Shell.h"
#include <iostream>
#include <cassert>

class GuiField: public GuiWidget
{
 public:
  void onDraw(); 
  void onMouseButton(char down, char button, int x, int y);
  void onMouseMotion(char buttonstate, int x, int y, int dx, int dy);
  void onMouseFocus(char);
  static const int tilesize = 16;
  static const int top_offset = 16;
  GuiField();
 
  void setGameField(GameField *gf1)
    {
      gf = gf1;
    }
 private:
  static Sprite graphics;
 
  void  drawTile(int x, int y, char tilenum, char rel=1)
    {
      Rectangle from;
      from.w=tilesize; from.h=tilesize;
      from.x=(tilenum & 0x0f) * tilesize;
      from.y=(tilenum & 0xf0) ? tilesize : 0 ;
          
      if (rel)
        graphics.draw(rect.x + x*tilesize, rect.y + y*tilesize, &from);
      else
        graphics.draw(rect.x + x, rect.y + y, &from);
    }
  void coord2tile(int x, int y, int *tx, int *ty)
  {
    *tx = x / tilesize;
    *ty = (y-top_offset) / tilesize;
  }
  void drawTiles();
  
  GameField *gf;
  char isMouseIn;
};

#endif
