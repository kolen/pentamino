#include "SDLInterface.h"

#include <SDL/SDL.h>
#include <iostream>
using namespace std;

SDL_Surface *SDLInterface::screen;

int
SDLInterface::setVideoMode(int w, int h, int bpp, 
			   Uint32 flags_set, Uint32 flags_reset)
{
  static const Uint32 flags_default = SDL_HWSURFACE|SDL_DOUBLEBUF;
  SDL_Surface *newscreen;
  newscreen = SDL_SetVideoMode(w, h, bpp,
			       ( flags_default | flags_set ) & ~flags_reset );
  if (newscreen) {
    screen = newscreen;
    return 1;
  } else {
    std::cerr << "** Couldn't change video mode: " << SDL_GetError() << endl;
  }  
}
