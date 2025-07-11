
#ifndef LUMIDI_GUI_RECTANGLE_COLLIDER_H
#define LUMIDI_GUI_RECTANGLE_COLLIDER_H
#include "raylib.h"
#include "uiCollider.h"

namespace LumidiGui
{

  class RectangleCollider : public UICollider2D
  {
  public:
    RectangleCollider(const Vector2 &position, const Vector2 &size) : UICollider2D(position, size) {}
    bool Contains(const Vector2 &point) const override;
  };

}

#endif // LUMIDI_GUI_RECTANGLE_COLLIDER_H