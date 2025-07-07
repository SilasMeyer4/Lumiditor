#ifndef LUMIDITOR_UIMANAGER_H
#define LUMIDITOR_UIMANAGER_H

#include <memory>
#include "uiElement2D.h"
#include <vector>

namespace LumidiGui
{
  class UIManager
  {
  private:
    std::vector<std::shared_ptr<UIElement2D>> elements;    // Vector to hold UI elements
    std::shared_ptr<UIElement2D> focusedElement = nullptr; // Pointer to the currently focused UI element
  public:
    // Constructor
    UIManager() = default;

    template <typename T, typename... Args>
    void AddElement(Args &&...args);

    // Method to add a UI element
    void AddElement(std::shared_ptr<UIElement2D> element);

    // Method to update all UI elements
    void Update(Vector2 mousePosition, bool mousePressed = false);

    // Method to draw all UI elements
    void Draw() const;

    void OnMouseMove(Vector2 position);
    void OnMouseDown(MouseButton button);
  };
}

#endif // LUMIDITOR_UIMANAGER_H
