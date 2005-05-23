#include "GuiContainer.h" 
#include <iostream>
using namespace std;

void
GuiContainer::addChild(GuiWidget *child)
{
  children.push_back(child);
  child->parentPos = children.end();
  child->parentPos--;
  child->parent = this;
}

void
GuiContainer::removeChild(GuiWidget *child)
{
  children.erase(child->parentPos);
  if (child == focusMouse) focusMouse = 0;
  if (child == exclusive) exclusive = 0;
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
  if (exclusive) {
    if (exclusive->rect.in(x, y))
      exclusive->onMouseButton(down, button, x, y);
    else
      exclusive->onClickOutside(down, button, x, y);
    return;
  }

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

void
GuiContainer::setExclusive(GuiWidget* w)
{
  if (exclusive) return;
  exclusive = w;
}
