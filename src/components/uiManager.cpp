#include "UIManager.h"

namespace Lumiditor
{
  void UIManager::AddElement(std::shared_ptr<UIElement2D> element)
  {
    elements.push_back(element);
  }

  template <typename T, typename... Args>
  void UIManager::AddElement(Args &&...args)
  {
    static_assert(std::is_base_of<UIElement2D, T>::value, "T must derive from UIElement2D");
    this->elements.push_back(std::make_shared<T>(std::forward<Args>(args)...));
  }

  void UIManager::Update()
  {
    for (const auto &element : elements)
    {
      element->Update();
    }
  }

  void UIManager::Draw() const
  {
    for (const auto &element : elements)
    {
      element->Draw();
    }
  }
  void UIManager::OnMouseMove(Vector2 position)
  {
    std::shared_ptr<UIElement2D> newFocusedElement = nullptr;

    for (auto iterator = elements.rbegin(); iterator != elements.rend(); iterator++)
    {
      if ((*iterator)->ContainsPoint(position))
      {
        newFocusedElement = *iterator;
        break; // Stop at the first element that contains the point
      }
    }

    if (newFocusedElement != this->focusedElement)
    {
      // If the focused element has changed, update the focused element
      this->focusedElement = newFocusedElement;
    }
  }

  void UIManager::OnMouseDown(MouseButton button)
  {
    if (this->focusedElement && this->focusedElement->onClick)
    {
      this->focusedElement->onClick(button);
    }
  }
}