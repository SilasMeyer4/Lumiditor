#include "button.h"
#include "rectangleCollider.h"

namespace LumidiGui
{

  Button::Button(std::string name, Vector2 position, Vector2 size, std::string text)
      : Element2D(name, position, size),
        text(text)
  {
    this->AddCollider<RectangleCollider>("default", position, size);
  }

  Button::~Button()
  {
  }
  void Button::Draw() const
  {
    // Draw the button rectangle
    DrawRectangleV(Vector2{GetAbsolutePosition().x, GetAbsolutePosition().y}, Vector2{size_.x, size_.y}, this->backgroundColor);
    // Draw the button text
    DrawText(text.c_str(), GetAbsolutePosition().x + 10, GetAbsolutePosition().y + 10, 20, this->foregroundColor);
    DrawChildren(); // Draw any child elements
  }

}