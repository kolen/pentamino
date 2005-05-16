#ifndef GUICONTAINER_H
#define GUICONTAINER_H

#include "GuiWidget.h"
#include <list>

/**
 * Виджет, содержащий другие виджеты
 */
class GuiContainer: public GuiWidget
{
 public:
  GuiContainer();
  std::list<GuiWidget*> children;

  void addChild(GuiWidget *child);

  //Events
  //On each event all children gets a copy of event
  void onDraw();
  virtual void onMouseButton(char down, char button, int x, int y);
  void onMouseMotion(char buttonstate, int x, int y, int dx, int dy);
  void onKeyboard(char down, SDL_keysym keysym);
 private:
  GuiWidget *focusMouse;
};

#endif
