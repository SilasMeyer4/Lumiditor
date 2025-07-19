#ifndef LUMIDITOR_LABEL_H
#define LUMIDITOR_LABEL_H

#include "raylib.h"
#include "element2D.h"

namespace LumidiGui
{
  class Label : public Element2D
  {
  private:
  public:
    Label(std::string name, Vector2 position, Vector2 size, std::string text, int fontSize, Color color)
        : Element2D(name, position, size), text(text), fontSize(fontSize), foregroundColor(color) {}
    ~Label();
    void Draw() const override;
    std::string text;
    Color foregroundColor = BLACK;
    Color backgroundColor;
    int fontSize;
  };
}

#endif // LUMIDITOR_LABEL_H