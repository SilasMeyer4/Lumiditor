
#ifndef LUMIDI_GUI_SHAPES_H
#define LUMIDI_GUI_SHAPES_H

#include "raylib.h"

namespace LumidiGui
{
  namespace Shapes
  {
    void DrawCross(Vector2 position, Vector2 size, float lineWidth, Color color);
    void DrawCheckMark();
  }
}

#endif