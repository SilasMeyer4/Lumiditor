#include "uiElement2D.h"

namespace LumidiGui
{
  inline Vector2 CalculateCenterPoint(const UIElement2D &element)
  {
    float xCenter = (element.size.x / 2.f);
    float yCenter = (element.size.y / 2.f);
    return Vector2{xCenter, yCenter};
  }
}