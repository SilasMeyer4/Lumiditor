#include "button.h"
#include "rectangleCollider.h"

namespace LumidiGui
{

  Button::Button(std::string name, Vector2 position, Vector2 size, std::string text)
      : Element2D(name, Vector3{position.x, position.y, 0}, Vector3{size.x, size.y, 0}),
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
    DrawRectangleV(Vector2{position.x, position.y}, Vector2{size.x, size.y}, this->backgroundColor);
    // Draw the button text
    DrawText(text.c_str(), position.x + 10, position.y + 10, 20, this->foregroundColor);
    DrawChildren(); // Draw any child elements
  }

}