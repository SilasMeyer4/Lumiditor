#ifndef LUMIDI_GUI_COLORS_H
#define LUMIDI_GUI_COLORS_H

#include "raylib.h"

namespace LumidiGui
{
  CLITERAL(Color)
  CreateColorRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
  {
    return CLITERAL(Color){r, g, b, a}; // Default color: black with full opacity
  }
}

#define LUMIDIGUI_COLOR(r, g, b, a) \
  CLITERAL(Color) { r, g, b, a }

#endif // LUMIDI_GUI_COLORS_H