#ifndef LUMIDITOR_UIELEMENT2D_H
#define LUMIDITOR_UIELEMENT2D_H

#include "raylib.h"
#include <functional>

namespace Lumiditor
{
  class UIElement2D
  {
  private:
    /* data */
  public:
    UIElement2D() = default;
    UIElement2D(Vector2 position, Vector2 size);
    ~UIElement2D() = default;
    virtual void Draw() const = 0; // Function to draw the UI element, to be implemented in derived classes
    virtual void Update();         // Function to update the UI element, can be overridden in derived classes

    virtual bool ContainsPoint(Vector2 pos) const
    {
      // Simple AABB hit test
      return (pos.x >= position.x && pos.x <= position.x + size.x &&
              pos.y >= position.y && pos.y <= position.y + size.y);
    }

    std::function<void(MouseButton)> onClick;

    Vector2 position; // Position of the UI element
    Vector2 size;     // Size of the UI element
  };
}

#endif // LUMIDITOR_UIELEMENT2D_H