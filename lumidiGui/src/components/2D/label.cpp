#include "label.h"

namespace LumidiGui
{

  Label::~Label()
  {
  }
  void Label::Draw() const
  {
    DrawText(this->text.c_str(), this->position.x, this->position.y, this->fontSize, this->foregroundColor);
    DrawChildren();
  }
}