
#ifndef LUMIDI_GUI_RECTANGLE_COLLIDER_H
#define LUMIDI_GUI_RECTANGLE_COLLIDER_H
#include "raylib.h"
#include "collider2D.h"

namespace LumidiGui
{

  class RectangleCollider : public Collider
  {
  public:
    RectangleCollider(const Vector2 &position, const Vector2 &size) : Collider(position, size) {}
    RectangleCollider(const Vector3 &position, const Vector3 &size) : Collider(position, size) {}
    bool Contains(const Vector2 &point) const override;
    bool Contains(const Vector3 &point) const override;
  };

}

#endif // LUMIDI_GUI_RECTANGLE_COLLIDER_H