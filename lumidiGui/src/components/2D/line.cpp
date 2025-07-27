#include "line.h"

void LumidiGui::Line::Draw() const
{
  DrawLineEx(Vector2{position_.x, position_.y}, Vector2{endPosition_.x, endPosition_.y}, 2, BLACK);
  DrawChildren();
}