#include "Main.h"
#include "Shell.h"

#include "Sprite.h"

#include <SDL/SDL.h>

#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  Main Main;
  return 0;
}

Main::Main()
{
  initSDL();
  rootwindow.setDirty();
  rootwindow.setGameField(&gamefield);  

  //Test
  ShellInterpreter interp;
  interp.addShellUser(this);
  interp.execCode("fullscreen yes");


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
Main::onCommand(std::string cmd, std::list<std::string> args)
{
    std::cerr << "eeeFIXME\n";

  if (cmd == "fullscreen") 
  {
    std::cerr << "fullscreenFIXME\n" << std::endl;
    return 1;
  }
  return 0;
}

Uint32 timer_50(Uint32 interval, void *param)
{
  SDL_Event event;
  event.type = SDL_USEREVENT;
  event.user.code = EVENT_50SEC;
  SDL_PushEvent(&event);
}
