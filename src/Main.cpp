#include "Main.h"
#include "Shell.h"

#include "Sprite.h"
#include "I18n.h"

#include <SDL/SDL.h>

#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  shell = new ShellInterpreter();
  i18n = new I18n();
  i18n->language = "ru";
  i18n->_("aaa");
  Main Main;
  return 0;
}

Main::Main()
{
  initSDL();
  rootwindow.setDirty();
  rootwindow.setGameField(&gamefield);

  shell->registerCommand(this, "exit",       0);
  shell->registerCommand(this, "fullscreen", 1);

  shell->execCode("exec default.cfg");
  shell->execCode("mainMenu");

  mainLoop();
  
  return;
}

Main::~Main()
{
  SDL_Quit();

}

/**
 * Enters main loop
 *
 * Main loop does events
 */
int Main::mainLoop()
{
  SDL_Event event;
  while (SDL_WaitEvent(&event))
    {
      SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
      switch(event.type)
	{
	case SDL_KEYDOWN:
	  break;
	case SDL_MOUSEMOTION:
	  //(char buttonstate, int x, int y, int dx, int dy)
	  rootwindow.onMouseMotion(
				   event.motion.state,
				   event.motion.x,
				   event.motion.y,
				   event.motion.xrel,
				   event.motion.yrel
				   );
	  break;
	case SDL_MOUSEBUTTONDOWN:	  
	case SDL_MOUSEBUTTONUP:
	  rootwindow.onMouseButton(
				   event.type == SDL_MOUSEBUTTONDOWN,
				   event.button.button,
				   event.button.x,
				   event.button.y
				   );
	  break;
	case SDL_VIDEOEXPOSE:
	  rootwindow.onDraw();
          flip();
	  break;
	case SDL_QUIT:
	  exit(0);
	}
      
      if (rootwindow.ifDirty())
        {
          rootwindow.onDraw();
          flip();
        }
      
      SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);      
    }
}

int Main::initSDL()
{
  /* Initialize the SDL library */
  if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0 ) {
    cout << "Couldn't initialize SDL: " << SDL_GetError() << endl;
    exit(1);
  }

  atexit(SDL_Quit);

  
  setVideoMode(640, 480, 16, 0, 0);
  //  screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
  if ( screen == NULL ) {
    cerr << "Couldn't set video mode: " << SDL_GetError() << endl;
    exit(1);
  }

#ifndef PACKAGE_STRING
#define PACKAGE_STRING "Pentamino"
#endif

  SDL_WM_SetCaption(PACKAGE_STRING, PACKAGE_STRING);

}

int 
Main::onCommand(int cmdId, std::string &command, std::list<std::string> &args)
{
  if (cmdId == 0) { //Exit
    //FIXME:
    exit(0);
  } else if (cmdId == 1) { //Fullscreen <n>
    CHKARGS(1);
    string mode;
    mode=POPARG;
    if (mode == "1")
      setVideoMode(640, 480, 16, SDL_FULLSCREEN, 0);
    else if (mode == "0")
      setVideoMode(640, 480, 16, 0, 0);
    else
      cerr << "Usage: fullscreen <0|1>" << endl;
  }
}
