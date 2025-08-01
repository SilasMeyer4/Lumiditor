#ifndef LUMIDITOR_BUTTON_H
#define LUMIDITOR_BUTTON_H

#include "raylib.h"
#include "element2D.h"
#include <string>
#include <functional>

namespace LumidiGui
{
  class Button : public Element2D
  {
  private:
    /* data */
  public:
    Button(std::string name, Vector2 position, Vector2 size, std::string text = "Button");
    ~Button();
    void Draw() const override;
    ElementType GetType() const override { return ElementType::Button; }
    // Properties
    std::string text;              // Text displayed on the button
    Color foregroundColor = BLACK; // Color of the button
    Color backgroundColor = GRAY;  // Color when hovered
  };
}

#endif // LUMIDITOR_BUTTON_H