#include "uiElement2D.h"

namespace Lumiditor
{
  UIElement2D::UIElement2D(Vector2 position, Vector2 size) : position(position), size(size)
  {
  }

  void UIElement2D::Update()
  {
    // Default implementation does nothing, can be overridden in derived classes
  }
}
