
#ifndef LUMIDI_GUI_UI_COLLIDER_H
#define LUMIDI_GUI_UI_COLLIDER_H
#include "raylib.h"

namespace LumidiGui
{

  class UICollider
  {
  public:
    Vector2 position; // Position of the collider
    Vector2 size;     // Size of the collider

    UICollider() = default;
    UICollider(const Vector2 &position, const Vector2 &size) : position(position), size(size) {}
    virtual bool Contains(const Vector2 &point) const = 0;
    virtual ~UICollider() = default;
  };
}

#endif // LUMIDI_GUI_UI_COLLIDER_H