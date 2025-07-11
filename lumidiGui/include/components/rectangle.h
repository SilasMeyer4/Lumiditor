#ifndef LUMIDITOR_Rectangle_H
#define LUMIDITOR_Rectangle_H

#include "raylib.h"
#include "uiElement2D.h"

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
  class Rectangle : public UIElement2D
  {
  private:
    float rotation_ = 0.f;

  public:
    Rectangle(std::string name, Vector2 position, Vector2 size, Color color)
        : UIElement2D(name, position, size), color(color) {}

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

    void SetRotation(float rotation);
    float GetRotation() const;
    bool hasBorder = false;
    Border border;
  };
}

#endif // LUMIDITOR_LABEL_H