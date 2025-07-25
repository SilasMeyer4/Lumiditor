#include "element.h"

namespace LumidiGui
{
  inline Vector2 CalculateCenterPoint(const Element &element)
  {
    float xCenter = (element.GetSize().x / 2.f);
    float yCenter = (element.GetSize().y / 2.f);
    return Vector2{xCenter, yCenter};
  }
}