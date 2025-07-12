#ifndef LUMIDITOR_LINE_H
#define LUMIDITOR_LINE_H

#include "raylib.h"
#include "uiElement2D.h"

namespace LumidiGui
{
  class Line : public UIElement2D
  {
  private:
  public:
    Line(std::string name, Vector2 startPosition, Vector2 endPosition, std::string text, int fontSize, Color color)
        : UIElement2D(name, position, size) {}
    ~Line() = default;
    void Draw() const override;
    Color color = BLACK;
    float width;
    Vector2 endPosition;
  };
}

#endif // LUMIDITOR_LABEL_H