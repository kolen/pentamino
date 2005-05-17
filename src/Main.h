#ifndef PENTA_MAIN_H
#define PENTA_MAIN_H

#include <SDL/SDL.h>
#include "SDLInterface.h"
#include "gui/GuiRootWindow.h"
#include "GameField.h"
#include "Shell.h"

#define EVENT_50SEC 1

class Main: public ShellUser, public SDLInterface
{
 public:
  Main();
  ~Main();

  int mainLoop();
  int initSDL();

  GuiRootWindow rootwindow;
  GameField gamefield;
  int onCommand(int cmdId, std::string &command, std::list<std::string> &args);
};

#endif
