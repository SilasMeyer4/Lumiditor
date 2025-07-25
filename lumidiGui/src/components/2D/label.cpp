#include "label.h"

namespace LumidiGui
{

  Label::~Label()
  {
  }
  void Label::Draw() const
  {
    DrawText(this->text.c_str(), this->position_.x, this->position_.y, this->fontSize, this->foregroundColor);
    DrawChildren();
  }
}