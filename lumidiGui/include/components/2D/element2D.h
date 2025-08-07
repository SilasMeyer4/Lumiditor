#ifndef LUMIDITOR_ELEMENT2D_H
#define LUMIDITOR_ELEMENT2D_H

#include "element.h"

namespace LumidiGui
{

  class Element2D : public Element
  {
  public:
    Element2D(std::string name, Vector2 position, Vector2 size)
        : Element(name, Vector3{position.x, position.y, 0}, Vector3{size.x, size.y, 0})
    {
    }
    ~Element2D() = default;
  };
}

#endif // LUMIDITOR_ELEMENT2D_H