#include "rectangle.h"
#include "helpers.h"
#include <cmath>

void LumidiGui::Rectangle::Draw() const
{
  Vector2 originPoint = {0, 0};

  ::Rectangle rec = {this->position_.x, this->position_.y, this->size_.x, this->size_.y};

  if (isFilled)
  {
    DrawRectanglePro(rec, originPoint, rotation_, color);
  }

  if (hasBorder)
  {
    if (this->border.isRounded)
    {
      DrawRectangleRoundedLinesEx(rec, this->border.roundness, border.segments, border.width, border.color);
    }
    else
    {
      DrawRectangleLinesEx(rec, this->border.width, this->border.color);
    }
  }

  DrawChildren();
}

void LumidiGui::Rectangle::SetRotation(float rotation)
{
  rotation_ = std::fmod(rotation, 360.f);
  if (rotation_ < 0)
  {
    rotation_ += 360.f;
  }
}

float LumidiGui::Rectangle::GetRotation() const
{
  return rotation_;
}
