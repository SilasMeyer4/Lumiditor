#include "label.h"

namespace LumidiGui
{

  Label::~Label()
  {
  }
  void Label::Draw() const
  {
    DrawText(this->text.c_str(), this->GetAbsolutePosition().x, this->GetAbsolutePosition().y, this->fontSize, this->foregroundColor);
    DrawChildren();
  }
}