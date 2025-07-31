#include "checkbox.h"
#include "operatorOverloads.h"
#include "shapes.h"

void LumidiGui::Checkbox::Draw() const
{
  if (rectangle_)
  {

    rectangle_->Draw();
    if (isChecked)
    {
      LumidiGui::Shapes::DrawCross(Vector2{GetAbsolutePosition().x, GetAbsolutePosition().y}, Vector2{size_.x, size_.y}, 2.0f, BLACK);
    }
    // Draw Cross

    DrawChildren();
  }
}
