#ifndef LUMIDITOR_LINE_H
#define LUMIDITOR_LINE_H

#include "raylib.h"
#include "element2D.h"

namespace LumidiGui
{
  class Line : public Element2D
  {
  private:
    Vector3 endPosition_;

  public:
    Line(std::string name, Vector2 startPosition, Vector2 endPosition) : Element2D(name, startPosition, Vector2{0, 0}) { endPosition_ = Vector3{endPosition.x, endPosition.y, 0}; }

    ~Line() = default;
    void Draw() const override;
    ElementType GetType() const override { return ElementType::Line; }
    Color color = BLACK;
    float width;
  };
}

#endif // LUMIDITOR_LABEL_H