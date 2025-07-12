#include "line.h"

void LumidiGui::Line::Draw() const
{
  DrawLineEx(position, endPosition, width, color);
  DrawChildren();
}