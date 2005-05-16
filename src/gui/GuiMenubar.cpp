#include "GuiMenubar.h"

Sprite GuiMenubar::menubarSprite("menu.png");

void
GuiMenubar::onDraw()
{
  Rectangle fromR(0, 0, 592, 16);
  menubarSprite.draw(&rect, &rect);
}

GuiMenubar::GuiMenubar()
{
  rect.x = 0;
  rect.y = 0;
  rect.w = 592;
  rect.h = 16;
}
