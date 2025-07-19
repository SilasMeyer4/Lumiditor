#include "rectangleCollider.h"

bool LumidiGui::RectangleCollider::Contains(const Vector2 &point) const
{
  return (point.x >= position.x && point.x <= position.x + size.x &&
          point.y >= position.y && point.y <= position.y + size.y);
}

bool LumidiGui::RectangleCollider::Contains(const Vector3 &point) const
{
  return (point.x >= position.x && point.x <= position.x + size.x &&
          point.y >= position.y && point.y <= position.y + size.y &&
          point.z >= position.z && point.z <= position.z + size.z);
}
