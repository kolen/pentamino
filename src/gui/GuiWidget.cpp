#include "GuiWidget.h" 
#include "GuiDrawContext.h"

#include <iostream>

int GuiWidget::dirty = 1;

GuiWidget::GuiWidget()
{
  ;
}
void
GuiWidget::onDraw()
{
  std::cerr << "Warning! Draw on pure widget!" << std::endl;
  ;
}

void
GuiWidget::onMouseButton(char down, char button, int x, int y)
{
  ;
}

void
GuiWidget::onMouseMotion(char buttonstate, int x, int y, int dx, int dy)
{
  ;
}

void
GuiWidget::onKeyboard(char down, SDL_keysym keysym)
{
  ;
}

void GuiWidget::onMouseFocus(char on){}

void GuiWidget::setRect(Rectangle rect)
{
  this->rect = rect;
}

void GuiWidget::setDirty()
{
  dirty = 1;
}

int GuiWidget::ifDirty()
{
  if (dirty) {
    dirty = 0;
    return 1;
  }
  else return 0;
}
