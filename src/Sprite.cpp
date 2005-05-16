#include "Sprite.h"
#include "Service.h"
#include <SDL/SDL_image.h> 
#include <assert.h>
#include "File.h"


Sprite::Sprite(std::string filename)
{
  loadImage(filename);
}

Sprite::Sprite(std::string filename, Uint32 flag, Uint8 r, Uint8 g, Uint8 b)
{
  loadImage(filename);
  setColorKey(flag, r, g, b);
}

void Sprite::loadImage(std::string filename)
{
  filename = path("img/"+filename);
  std::cerr << "Loading sprite " << filename << std::endl;
  surface = IMG_Load (filename.c_str());
}

void Sprite::setColorKey(Uint32 flag, Uint8 r, Uint8 g, Uint8 b)
{
  int result;
  result = SDL_SetColorKey(surface, flag, SDL_MapRGB(surface->format, r, g, b));
  assert(result == 0);
}

int
Sprite::draw(int x, int y, Rectangle *region)
{
  Rectangle xy;
  xy.x = x;
  xy.y = y;
  draw(&xy, region);
}
