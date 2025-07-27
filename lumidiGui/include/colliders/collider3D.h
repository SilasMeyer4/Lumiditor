
#ifndef LUMIDIGUI_COLLIDER3D_H
#define LUMIDIGUI_COLLIDER3D_H
#include "collider.h"

namespace LumidiGui
{

  class Collider3D : public Collider
  {
  public:
    Vector3 position; // Position of the collider
    Vector3 size;     // Size of the collider
    Collider3D(const Vector3 &position, const Vector3 &size) : Collider(position, size) {}
    Collider3D(const Vector2 &position, const Vector2 &size) : Collider(position, size) {}
    virtual bool Contains(const Vector3 &point) const = 0;
    virtual ~Collider3D() = default;
  };
}

#endif // LUMIDIGUI_COLLIDER3D_H