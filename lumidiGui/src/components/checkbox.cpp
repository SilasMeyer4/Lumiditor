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
      LumidiGui::Shapes::DrawCross(position, size, 2.0f, BLACK);
    }
    // Draw Cross

    DrawChildren();
  }
}
