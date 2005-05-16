#include "GuiShapeSel.h"
#include <iostream>

Sprite GuiShapeSel::shapesSprite("shapes.png");

void
GuiShapeSel::onDraw()
{
  int i;
  Rectangle kubTo(SHAPESEL_LOCATION, 0);
  Rectangle kubFrom(0, 0, KUBE_SIZE, KUBE_SIZE);
  Rectangle kubFromRidge(KUBE_SIZE*3, 0, 8, 640);

  for (i=0; i<12; i++)
    {
      kubFrom.y = kubTo.y = i*KUBE_SIZE;
      if (gf->shape(i).isOnField)
        kubFrom.x = KUBE_SIZE;
      else if (gf->isSelected && i == gf->selected)
        kubFrom.x = KUBE_SIZE*2;
      else
        kubFrom.x = 0;
      shapesSprite.draw(&kubTo, &kubFrom);      
    }
  shapesSprite.draw(SHAPESEL_LOCATION-8, 0, &kubFromRidge);
}

GuiShapeSel::GuiShapeSel()
{
  rect.w = 40;
  rect.h = 480;
  rect.x = SHAPESEL_LOCATION;
  rect.y = 0;
}

void
GuiShapeSel::onMouseButton(char down, char button, int x, int y)
{
  if (down) {
    int selected = y / KUBE_SIZE;
    switch (button)
      {
      case 1:
        if (gf->isSelected) {
          if (gf->selected == selected) {
            gf->isSelected = 0;
          } else {
            gf->selected = selected;            
          }
        } else {
          if (gf->shape(selected).isOnField) break;
          gf->selectShape(selected);
        }
        setDirty();
        break; 
      case 3:
        if (gf->isSelected) {
          gf->isSelected = 0;
        } else {
          gf->removeShape(selected);
        }
        setDirty();
      }
  }  
}
