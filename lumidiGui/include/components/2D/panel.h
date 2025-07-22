

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
    Panel(std::string name, Vector3 position, Vector3 size) : Element2D(name, position, size) {};
    ~Panel() = default;
    void Draw() const override;

    Color backgroundColor = WHITE;
  };
}

#endif // LUMIDITOR_PANEL_H