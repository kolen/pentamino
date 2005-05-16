#ifndef SDLINTERFACE_H
#define SDLINTERFACE_H
#include <SDL/SDL.h>

class SDLInterface
{
 public:
  ///Screen surface
  static SDL_Surface *screen;
  void flip()
    {
      SDL_Flip(screen);
    }
};

#endif
