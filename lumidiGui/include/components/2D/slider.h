#ifndef LUMIDITOR_SLIDER_H
#define LUMIDITOR_SLIDER_H

#include "raylib.h"
#include "element2D.h"
#include "rectangle.h"
#include "line.h"

namespace LumidiGui
{
  class Slider : public Element2D
  {
  private:
  public:
    Slider(std::string name, Vector2 position, bool isVertical, Vector2 size)
        : Element2D(name, position, size) { this->isVertical = isVertical; }
    ~Slider() = default;
    void Draw() const override;
    ElementType GetType() const override { return ElementType::Slider; }

    bool isVertical = false;

    std::weak_ptr<Rectangle> thumb;
    std::weak_ptr<Line> line;
  };
}

#endif // LUMIDITOR_SLIDER_H