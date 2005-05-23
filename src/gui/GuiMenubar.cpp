#include "GuiMenubar.h"
#include "../Shell.h"

Sprite GuiMenubar::menubarSprite("menu.png");

Rectangle GuiMenubar::fromR(0, 0, 592, 16);
Rectangle GuiMenubar::item1_sprite(10, 16, 143, 16);
Rectangle GuiMenubar::item1_screen(10,  0, 143, 16);

void
GuiMenubar::onDraw()
{  
  menubarSprite.draw(&rect, &rect);
  if (focus == 1) menubarSprite.draw(&item1_screen, &item1_sprite);
}

GuiMenubar::GuiMenubar()
{
  rect.x = 0;
  rect.y = 0;
  rect.w = 592;
  rect.h = 16;
  focus = 0;
}

void 
GuiMenubar::onMouseMotion(char buttonstate, int x, int y, int dx, int dy)
{
  if ((focus != 1) && item1_screen.in(x, y)) { focus = 1; setDirty(); }
  else if (focus != 0 && !item1_screen.in(x, y)) { focus = 0; setDirty(); }
}

void
GuiMenubar::onMouseFocus(char on)
{
  if (!on) {
    focus=0;
    setDirty();
  }
}

void
GuiMenubar::onMouseButton(char down, char button, int x, int y)
{
  if (button == 1 && !down && item1_screen.in(x, y)) {
    shell->execCode("mainMenu");
    setDirty();
  }
}
