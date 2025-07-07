#include "button.h"
#include "rectangleCollider.h"

namespace LumidiGui
{

  Button::Button(Vector2 position, Vector2 size, std::string text)
      : UIElement2D(position, size), text(text) // Call the base class constructor
  {
    this->SetCollider(std::make_shared<RectangleCollider>(position, size));
  }

  Button::~Button()
  {
  }
  void Button::Draw() const
  {
    // Draw the button rectangle
    DrawRectangleV(position, size, LIGHTGRAY);
    // Draw the button text
    DrawText(text.c_str(), position.x + 10, position.y + 10, 20, BLACK);
  }

}