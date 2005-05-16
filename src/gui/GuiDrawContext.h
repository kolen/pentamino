#ifndef GUIDRAWCONTEXT_H
#define GUIDRAWCONTEXT_H

#include <SDL/SDL.h>
#include <string>
#include "../SDLInterface.h"
#include "../Sprite.h"

class GuiDrawContext: public SDLInterface
{
 public:
  void text(std::string text, int x, int y);

  static const int font_w = 6;
  static const int font_h = 12;
 private:
  static Sprite font;  
};

#endif
