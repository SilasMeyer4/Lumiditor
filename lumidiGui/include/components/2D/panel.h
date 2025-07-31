

#ifndef LUMIDITOR_PANEL_H
#define LUMIDITOR_PANEL_H

#include "raylib.h"
#include "element2D.h"
#include <string>

namespace LumidiGui
{
  class Panel : public Element2D
  {
  private:
  public:
    Panel(std::string name, Vector2 position, Vector2 size) : Element2D(name, position, size) {};
    ~Panel() = default;
    void Draw() const override;
    ElementType GetType() const override { return ElementType::Panel; }

    Color backgroundColor = WHITE;
  };
}

#endif // LUMIDITOR_PANEL_H