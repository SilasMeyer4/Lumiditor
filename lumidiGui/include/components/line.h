#ifndef LUMIDITOR_LINE_H
#define LUMIDITOR_LINEL_H

#include "raylib.h"
#include "uiElement2D.h"

namespace LumidiGui
{
  class Line : public UIElement2D
  {
  private:
  public:
    Line(std::string name, Vector2 position, Vector2 size, std::string text, int fontSize, Color color)
        : UIElement2D(name, position, size) {}
    ~Line();
    void Draw() const override;
    Color color = GRAY;
  };
}

#endif // LUMIDITOR_LABEL_H