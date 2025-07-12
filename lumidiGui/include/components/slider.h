#ifndef LUMIDITOR_SLIDER_H
#define LUMIDITOR_SLIDER_H

#include "raylib.h"
#include "uiElement2D.h"
#include "rectangle.h"
#include "line.h"

namespace LumidiGui
{
  class Slider : public UIElement2D
  {
  private:
  public:
    Slider(std::string name, Vector2 position, bool isVertical, Vector2 size)
        : UIElement2D(name, position, size) { this->isVertical = isVertical; }
    ~Slider() = default;
    void Draw() const override;

    bool isVertical = false;
    std::weak_ptr<Rectangle> thumb;
    std::weak_ptr<Line> line;
  };
}

#endif // LUMIDITOR_SLIDER_H