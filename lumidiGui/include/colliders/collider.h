
#ifndef LUMIDIGUI_COLLIDER_H
#define LUMIDIGUI_COLLIDER_H
#include "raylib.h"

/**
 * @namespace LumidiGui
 * @brief Contains classes and functions related to the Lumidi GUI system, including collider definitions for GUI elements.
 */
namespace LumidiGui
{

  class Collider
  {
  public:
    Vector3 position; // Position of the collider
    Vector3 size;     // Size of the collider

    Collider(const Vector3 &position, const Vector3 &size) : position(position), size(size) {}
    /**
     * @brief Constructs a Collider object with the specified position and size.
     *
     * Initializes the collider's position and size using 2D vectors, converting them to 3D vectors
     * with the Z component set to 0 for position and default for size.
     *
     * @param position The 2D position (x, y) of the collider.
     * @param size The 2D size (width, height) of the collider.
     */
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