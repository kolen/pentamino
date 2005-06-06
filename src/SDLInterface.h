#ifndef SDLINTERFACE_H
#define SDLINTERFACE_H
#include <SDL/SDL.h>

class SDLInterface
{
 public:
  ///Screen surface
  static SDL_Surface *screen;
  int
    setVideoMode(int w, int h, int bpp, 
		 Uint32 flags_set, Uint32 flags_reset);    
  void flip()
    {
      SDL_Flip(screen);
    }
};

#endif
