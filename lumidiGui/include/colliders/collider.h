
#ifndef LUMIDIGUI_COLLIDER_H
#define LUMIDIGUI_COLLIDER_H
#include "raylib.h"

namespace LumidiGui
{

  class Collider
  {
  public:
    Vector3 position; // Position of the collider
    Vector3 size;     // Size of the collider

    Collider(const Vector3 &position, const Vector3 &size) : position(position), size(size) {}
    Collider(const Vector2 &position, const Vector2 &size)
    {
      this->position = Vector3{position.x, position.y, 0};
      this->size = Vector3{size.x, size.y};
    }
    virtual bool Contains(const Vector2 &point) const = 0;
    virtual bool Contains(const Vector3 &point) const = 0;
    virtual ~Collider() = default;
  };
}

#endif // LUMIDIGUI_COLLIDER_H