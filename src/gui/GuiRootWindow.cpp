#include "GuiRootWindow.h"

#include <iostream>

GuiRootWindow::GuiRootWindow()
{
  ::GuiContainer();
  addChild(&shapeSel);
  addChild(&field);
  addChild(&menubar);
}
