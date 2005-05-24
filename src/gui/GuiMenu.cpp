// $Id: GuiMenu.cpp,v 1.6 2005/05/24 14:03:34 kolen Exp $ 

#include "GuiMenu.h"
#include "GuiContainer.h"

Sprite GuiMenu::gfx("menuitem.png");

Rectangle GuiMenu::gfx_area_header (0, 0, MENUWIDTH, MENULINEHEIGHT);
Rectangle GuiMenu::gfx_area_item (0, MENULINEHEIGHT, MENUWIDTH, MENULINEHEIGHT);
Rectangle GuiMenu::gfx_area_footer (0, MENULINEHEIGHT*2, MENUWIDTH, MENULINEHEIGHT);
Rectangle GuiMenu::gfx_area_item_sel (0, MENULINEHEIGHT*3, MENUWIDTH, MENULINEHEIGHT);

GuiMenu::GuiMenu(int x, int y)
{
  rect.x = x;
  rect.y = y;
  rect.w = MENUWIDTH;
  rect.h = MENULINEHEIGHT;
  lastSelected = 0;
}

void
GuiMenu::addItem(string text, string action)
{
  MenuItem item = {text, action};
  items.push_back(item);
  rect.h += MENULINEHEIGHT;
}

void
GuiMenu::onDraw()
{
  vector<MenuItem>::iterator i;
  int ii=0, res;
  for (i=items.begin(); i!=items.end(); i++)
    {
      ii++;
      gfx.draw(rect.x, rect.y + ii*MENULINEHEIGHT,
	       ((ii-1)==lastSelected) ? &gfx_area_item_sel : &gfx_area_item
	       );
      draw.text(i->text,
                rect.x+MENUTEXTOFFSET_X ,
                rect.y+MENUTEXTOFFSET_Y + ii*MENULINEHEIGHT 
                );
    }
  gfx.draw(rect.x, rect.y + (ii+1)*MENULINEHEIGHT,
	        &gfx_area_footer);
  gfx.draw(rect.x, rect.y, &gfx_area_header);
  draw.text(title, rect.x+MENUTEXTOFFSET_X*2, rect.y+MENUTEXTOFFSET_Y);
}

int
GuiMenu::getInFocus()
{
  int x, y, ys;
  SDL_GetMouseState(&x, &y);
  ys = (y-rect.y) / MENULINEHEIGHT;
  ys--;
  return ys;
}

void
GuiMenu::onMouseFocus(char on)
{
  int thisSelected;
  if (on) {
    if (thisSelected = getInFocus() == lastSelected) {
      lastSelected = thisSelected;
      setDirty();
    }
  } else {
    lastSelected = -1;
    setDirty();
  }
}

void
GuiMenu::onMouseMotion(char button, int x, int y, int dx, int dy)
{
  int thisSelected = getInFocus();
  if (thisSelected != lastSelected) {
    lastSelected = thisSelected;
    setDirty();
  }
}

void
GuiMenu::onMouseButton(char down, char button, int x, int y)
{
  if (down) {
    int sel = getInFocus();
    if (sel == -1) return;
    shell->execCode(items[sel].action);
    bury(); 
  }
}

void
GuiMenu::onClickOutside(char down, char button, int x, int y)
{
  if (down)
    bury();
}

void
GuiMenu::bury()
{
  ((GuiContainer*)parent)->removeChild(this);
  delete this;
  setDirty();
}
