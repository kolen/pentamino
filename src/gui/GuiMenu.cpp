// $Id: GuiMenu.cpp,v 1.1 2005/05/19 15:00:50 kolen Exp $ 

#include "GuiMenu.h"

Sprite GuiMenu::gfx("menu.png");

Rectangle GuiMenu::gfx_area_header (0, 0, MENUWIDTH, MENULINEHEIGHT);
Rectangle GuiMenu::gfx_area_item (0, MENULINEHEIGHT, MENUWIDTH, MENULINEHEIGHT);
Rectangle GuiMenu::gfx_area_footer (0, MENULINEHEIGHT*2, MENUWIDTH, MENULINEHEIGHT);

GuiMenu::GuiMenu(int x, int y)
{
  rect.x = x;
  rect.y = y;
  rect.w = MENUWIDTH;
  rect.h = MENULINEHEIGHT;
}

void
GuiMenu::addItem(string text, string action)
{
  MenuItem item = {text, action};
  items.push_front(item);
  rect.h += MENULINEHEIGHT;
}

void
GuiMenu::onDraw()
{
  list<MenuItem>::iterator i;
  int ii=0;
  for (i=items.begin(); i!=items.end(); i++)
    {
      ii++;
      gfx.draw(rect.x, rect.y + ii*MENULINEHEIGHT,
	       &gfx_area_item
	       );
    }
  gfx.draw(rect.x, rect.y + (ii+1)*MENULINEHEIGHT,
	   &gfx_area_footer);
  gfx.draw(rect.x, rect.y, &gfx_area_footer);
}
