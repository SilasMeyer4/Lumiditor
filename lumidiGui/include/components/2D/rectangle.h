#ifndef LUMIDITOR_RECTANGLE_H
#define LUMIDITOR_RECTANGLE_H

#include "raylib.h"
#include "element2D.h"

namespace LumidiGui
{
  struct Border
  {
    bool isRounded = false;
    float width = 0.f;
    float roundness = 0.f;
    int segments = 0;
    Color color = BLACK;
  };
  class Rectangle : public Element2D
  {
  private:
    float rotation_ = 0.f;

  public:
    Rectangle(std::string name, Vector2 position, Vector2 size, Color color)
        : Element2D(name, position, size), color(color) {}

    Rectangle(std::string name, Vector2 position, Vector2 size, Color color, Border border)
        : Rectangle(name, position, size, color)
    {
      this->hasBorder = true;
      this->border = border;
    }

    Rectangle(std::string name, Vector2 position, Vector2 size, Color color, float rotation)
        : Rectangle(name, position, size, color) { SetRotation(rotation); }

    Rectangle(std::string name, Vector2 position, Vector2 size, Color color, float rotation, Border border)
        : Rectangle(name, position, size, color, rotation)
    {
      this->border = border;
      hasBorder = true;
    }

    ~Rectangle() = default;
    void Draw() const override;
    Color color = GRAY;

    void SetBorder(Border border)
    {
      this->border = border;
      hasBorder = true;
    }

    ElementType GetType() const override { return ElementType::Rectangle; }
    void SetRotation(float rotation);
    float GetRotation() const;
    bool hasBorder = false;
    Border border;
    bool isFilled = true;
  };
}

#endif // LUMIDITOR_LABEL_H