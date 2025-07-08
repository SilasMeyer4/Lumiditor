#ifndef LUMIDITOR_LABEL_H
#define LUMIDITOR_LABEL_H

#include "raylib.h"
#include "uiElement2D.h"

namespace LumidiGui
{
  class Label : public UIElement2D
  {
  private:
    /* data */
  public:
    Label(std::string name, Vector2 position, Vector2 size, std::string text)
        : UIElement2D(name, position, size) {}
    ~Label();
  };
}

#endif // LUMIDITOR_LABEL_H