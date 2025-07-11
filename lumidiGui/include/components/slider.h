#ifndef LUMIDITOR_SLIDER_H
#define LUMIDITOR_SLIDER_H

#include "raylib.h"
#include "uiElement2D.h"

namespace LumidiGui
{
  class Slider : public UIElement2D
  {
  private:
  public:
    Slider(std::string name, Vector2 position, Vector2 size)
        : UIElement2D(name, position, size), text(text) {}
    ~Slider();
    void Draw() const override;
    std::string text;
    Color foregroundColor = BLACK;
    Color backgroundColor;
    int fontSize;
  };
}

#endif // LUMIDITOR_SLIDER_H