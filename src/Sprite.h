#ifndef SPRITE_H
#define SPRITE_H

#include <SDL/SDL.h>
#include <string>

#include "SDLInterface.h"
#include "Service.h"

class Sprite: SDLInterface
{
 public:
  SDL_Surface *surface;

  Sprite(std::string filename);
  Sprite(std::string filename, Uint32 flag, Uint8 r, Uint8 g, Uint8 b);

  int draw(int x, int y, Rectangle *region=0);
  //  inline int draw(Rectangle *point, Rectangle *region=0);
  int draw(Rectangle *point, Rectangle *region=0)
    {
      SDL_BlitSurface(surface, region, screen, point);
    }

  void setColorKey(Uint32 flag, Uint8 r, Uint8 g, Uint8 b);
  void loadImage(std::string filename);
};

#endif
