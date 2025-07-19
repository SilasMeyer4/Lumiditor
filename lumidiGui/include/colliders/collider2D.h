
#ifndef LUMIDIGUI_COLLIDER2D_H
#define LUMIDIGUI_COLLIDER2D_H
#include "collider.h"

namespace LumidiGui
{

  class Collider2D : public Collider
  {
  public:
    Vector3 position; // Position of the collider
    Vector3 size;     // Size of the collider

    Collider2D(const Vector3 &position, const Vector3 &size) : Collider(position, size) {}
    Collider2D(const Vector2 &position, const Vector2 &size) : Collider(position, size) {}
    virtual ~Collider2D() = default;
  };
}

#endif // LUMIDIGUI_COLLIDER2D_H