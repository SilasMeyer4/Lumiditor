
#ifndef LUMIDI_GUI_RECTANGLE_COLLIDER_H
#define LUMIDI_GUI_RECTANGLE_COLLIDER_H
#include "raylib.h"
#include "collider2D.h"

/**
 * @brief The LumidiGui namespace contains all classes and functions related to the Lumidi GUI system.
 */
namespace LumidiGui
{

  class RectangleCollider : public Collider
  {
  public:
    /**
     * @brief Constructs a 2D rectangle collider.
     * @param position The position of the rectangle (top-left corner).
     * @param size The size (width and height) of the rectangle.
     */
    RectangleCollider(const Vector2 &position, const Vector2 &size) : Collider(position, size) {}

    /**
     * @brief Constructs a 3D rectangle collider (cuboid).
     * @param position The position of the cuboid (minimum corner).
     * @param size The size (width, height, depth) of the cuboid.
     */
    RectangleCollider(const Vector3 &position, const Vector3 &size) : Collider(position, size) {}

    /**
     * @brief Checks if a 2D point is contained within the rectangle.
     * @param point The 2D point to check.
     * @return True if the point is inside the rectangle, false otherwise.
     */
    bool Contains(const Vector2 &point) const override;

    /**
     * @brief Checks if a 3D point is contained within the cuboid.
     * @param point The 3D point to check.
     * @return True if the point is inside the cuboid, false otherwise.
     */
    bool Contains(const Vector3 &point) const override;
  };

}

#endif // LUMIDI_GUI_RECTANGLE_COLLIDER_H