#include "button.h"
#include "rectangleCollider.h"

namespace LumidiGui
{

  Button::Button(std::string name, Vector2 position, Vector2 size, std::string text)
      : UIElement2D(name, position, size), text(text) // Call the base class constructor
  {
    this->SetCollider<RectangleCollider>(position, size);
  }

  Button::~Button()
  {
  }
  void Button::Draw() const
  {
    // Draw the button rectangle
    DrawRectangleV(position, size, this->backgroundColor);
    // Draw the button text
    DrawText(text.c_str(), position.x + 10, position.y + 10, 20, this->foregroundColor);
    DrawChildren(); // Draw any child elements
  }

}