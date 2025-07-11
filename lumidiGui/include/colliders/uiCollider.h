
#ifndef LUMIDI_GUI_UI_COLLIDER_H
#define LUMIDI_GUI_UI_COLLIDER_H
#include "raylib.h"

namespace LumidiGui
{

  class UICollider2D
  {
  public:
    Vector2 position; // Position of the collider
    Vector2 size;     // Size of the collider

    UICollider2D() = default;
    UICollider2D(const Vector2 &position, const Vector2 &size) : position(position), size(size) {}
    virtual bool Contains(const Vector2 &point) const = 0;
    virtual ~UICollider2D() = default;
  };
}

#endif // LUMIDI_GUI_UI_COLLIDER_H