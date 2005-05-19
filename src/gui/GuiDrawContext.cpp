#include "GuiDrawContext.h"
#include <iterator>

Sprite GuiDrawContext::font("font.png", SDL_SRCCOLORKEY, 0xff, 0xff, 0xff);

void
GuiDrawContext::text(std::string text, int x, int y)
{
  Rectangle srect;
  srect.w = font_w;
  srect.h = font_h;

  std::string::iterator si;

  for (si = text.begin(); si != text.end(); si++)
    {
      char c = *si;
      srect.x = (c & 0x1f) * font_w;
      srect.y = ((c >> 5) - 1) * font_h;  
      font.draw(x, y, &srect);
      x += font_w;
    }
  
}

int
GuiDrawContext::textLength(const std::string &text)
{
  return text.size() * font_w;
}
