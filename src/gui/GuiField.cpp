#include "GuiField.h"

Sprite GuiField::graphics("tiles.png");

void GuiField::onDraw()
{
  drawTiles();
  if (gf->isSelected) {
    draw.text("Selected", 0, 18);
  
    if (isMouseIn) {
      //Draw moving tile
      int x, y, mx, my;
      SDL_GetMouseState(&mx, &my);
      for (x=0; x<5; x++)
        for (y=0; y<5; y++)
          if (gf->selectedShape().at(x, y))
          drawTile(x*tilesize + mx + rect.x - 40,
                   y*tilesize + my + rect.y - 72,
                   gf->selectedShape().at(x, y) & 0x0f,
                   0
                  );
    }
  }
}

GuiField::GuiField()
{
  rect.x = 0;
  rect.y = top_offset;
  rect.w = 640 - 40;
  rect.h = 480 - top_offset;
}

void
GuiField::drawTiles()
{
  int xx, yy, xmax, ymax;
  xmax = gf->width;
  ymax = gf->height;
  for (xx=0; xx<xmax; xx++)
    {
      for (yy=0; yy<ymax; yy++)
        {
          drawTile(xx, yy, gf->tileAt(xx, yy));
        }
    }
}

void
GuiField::onMouseButton(char down, char button, int x, int y)
{
  if (down) {
    if (button == 1) {
      int tx, ty; // Tile coords
      coord2tile(x, y, &tx, &ty);
      if (gf->isSelected)
      //-put-  
        {
          if (gf->tryFit(gf->selected, tx-2, ty-2)) {
            gf->selectedShape().x = tx-2;
            gf->selectedShape().y = ty-2;
            gf->updateShape(gf->selected);
            gf->isSelected = 0;
            SDL_ShowCursor(SDL_ENABLE);
          }
        }
      else
      //if !isSelected : -pick-
        {                  
          gf->selected = gf->getShapeAt(tx, ty);
          if (gf->selected == -1) return;
          Shape &sh = gf->selectedShape();
          gf->removeShape(gf->selected);
          sh.isOnField = 0;
          gf->isSelected = 1;
          SDL_ShowCursor(SDL_DISABLE);
        }  
      setDirty();
    }
    else if ((button == 3 || button == 4) && gf->isSelected) {
      gf->selectedShape().rotate();
      setDirty();
    }
    else if (button == 5 && gf->isSelected) {
      gf->selectedShape().rotate(-1);
      setDirty();
    }
    else if (button == 2 && gf->isSelected) {
      gf->selectedShape().sideswap();
      setDirty();
    }
    
  // if !down
  } else {
  }
  // endof if (down)
}

void
GuiField::onMouseMotion
(char buttonstate, int x, int y, int dx, int dy)
{
  if (gf->isSelected) {
    setDirty();
  }
}

void GuiField::onMouseFocus(char on)
{
  if (on) {
    if (gf->isSelected) SDL_ShowCursor(SDL_DISABLE);
    isMouseIn = 1;
  } else {
    if (gf->isSelected) SDL_ShowCursor(SDL_ENABLE);
    isMouseIn = 0;
  }
  if (gf->isSelected)
    setDirty();
}
