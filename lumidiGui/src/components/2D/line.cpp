#include "line.h"

void LumidiGui::Line::Draw() const
{
  DrawLineEx(Vector2{GetAbsolutePosition().x, GetAbsolutePosition().y}, Vector2{GetAbsolutePosition().x, GetAbsolutePosition().y}, 2, BLACK);
  DrawChildren();
}