#include "UIManager.h"
#include <iostream>

namespace LumidiGui
{
  std::shared_ptr<UIElement2D> UIManager::GetElementByName(const std::string &name) const
  {
    auto it = elementMap.find(name);
    if (it != elementMap.end())
    {
      return it->second;
    }
    return nullptr; // Return nullptr if the element is not found
  }

  void UIManager::Update(Vector2 mousePosition, bool mousePressed)
  {
    for (const auto &element : elements)
    {
      element->Update(mousePosition, mousePressed);
    }
  }

  bool UIManager::RemoveElement(const std::string &name)
  {
    auto element = GetElementByName(name);
    if (element)
    {
      return RemoveElement(element);
    }
    return false; // Return false if the element was not found
  }

  bool UIManager::RemoveElement(std::shared_ptr<UIElement2D> element)
  {
    auto it = std::remove(elements.begin(), elements.end(), element);
    if (it != elements.end())
    {
      elements.erase(it, elements.end());
      elementMap.erase(element->name);
      return true; // Element was successfully removed
    }
    return false; // Element was not found
  }

  bool UIManager::AddElement(std::shared_ptr<UIElement2D> element)
  {
    if (!allowDuplicateNames && elementMap.find(element->name) != elementMap.end())
    {
      std::cerr << "[UIManager] Error: Element with name '" << element->name << "' already exists." << std::endl;
      return false;
    }

    elements.push_back(element);
    this->elementMap[element->name] = element;
    return true;
  }

  void UIManager::Draw() const
  {
    for (const auto &element : elements)
    {
      element->Draw();
    }
  }
}