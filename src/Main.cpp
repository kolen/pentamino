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
  shell->registerCommand(this, "exit", 0);

  shell->execCode("exec default.cfg");
  shell->execCode("menu fafik\nm+ aa bb\nm+ fafik exit\nmenu_end"
                  );

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

  /* Clean up on exit */
  atexit(SDL_Quit);
    
  /*
   * Initialize the display in a 640x480 8-bit palettized mode,
   * requesting a software surface
   */
  screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
  if ( screen == NULL ) {
    cerr << "Couldn't set video mode: " << SDL_GetError() << endl;
    exit(1);
  }

}

int 
Main::onCommand(int cmdId, std::string &command, std::list<std::string> &args)
{
  if (cmdId == 0) { //Exit
    //FIXME:
    exit(0);
  }
}
