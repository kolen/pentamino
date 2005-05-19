#include "GuiContainer.h" 
#include <iostream>

void
GuiContainer::addChild(GuiWidget *child)
{
  children.push_back(child);
}

void GuiContainer::onDraw()
{
  std::list<GuiWidget*>::iterator i;
  for(i=children.begin(); i!=children.end(); i++)
    {
      (*i)->onDraw();
    }
}

void 
GuiContainer::onMouseButton(char down, char button, int x, int y)
{
  std::list<GuiWidget*>::reverse_iterator i;
  for(i=children.rbegin(); i!=children.rend(); i++)
    {
      if ((*i)->rect.in(x, y))
        {        
          (*i)->onMouseButton(down, button, x, y);
          break;
        }
    }  
}

void
GuiContainer::onMouseMotion(char buttonstate, int x, int y, int dx, int dy)
{
  std::list<GuiWidget*>::reverse_iterator i;
  for(i=children.rbegin(); i!=children.rend(); i++)
    {
      if ((*i)->rect.in(x, y))
        {        
          if (focusMouse != *i) {
	    if (focusMouse)
	      focusMouse->onMouseFocus( 0 );
            (*i)->onMouseFocus( 1 );
            focusMouse = *i;
          }
          (*i)->onMouseMotion(buttonstate, x, y, dx, dy);
          break;
        }
    }  
}

void
GuiContainer::onKeyboard(char down, SDL_keysym keysym)
{
}

GuiContainer::GuiContainer()
{
  focusMouse = 0;
}
