#ifndef LUMIDITOR_LABEL_H
#define LUMIDITOR_LABEL_H

#include "raylib.h"
#include "uiElement2D.h"

namespace LumidiGui
{
  class Label : public UIElement2D
  {
  private:
  public:
    Label(std::string name, Vector2 position, Vector2 size, std::string text, int fontSize, Color color)
        : UIElement2D(name, position, size), text(text), fontSize(fontSize), foregroundColor(color) {}
    ~Label();
    void Draw() const override;
    std::string text;
    Color foregroundColor = BLACK;
    Color backgroundColor;
    int fontSize;
  };
}

#endif // LUMIDITOR_LABEL_H