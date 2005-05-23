#ifndef PENTA_MAIN_H
#define PENTA_MAIN_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <SDL/SDL.h>
#include "SDLInterface.h"
#include "gui/GuiRootWindow.h"
#include "GameField.h"
#include "Shell.h"

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
