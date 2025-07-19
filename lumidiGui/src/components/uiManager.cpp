#include "uiManager.h"
#include <iostream>
#include "defaultBehaviors.h"

namespace LumidiGui
{

  void UIManager::Update(InputManager &inputManager)
  {

    for (const auto &element : elements)
    {
      if (element->isEnabled)
      {
        element->Update(inputManager);
      }
    }
  }

  bool UIManager::RemoveElement(const std::string &name)
  {
    auto weakElement = GetElementByName(name);
    if (auto element = weakElement.lock())
    {
      return RemoveElement(element);
    }
    return false; // Return false if the element was not found
  }

  bool UIManager::RemoveElement(std::shared_ptr<Element> element)
  {
    if (!element)
      return false;

    elementMap.erase(element->name);

    if (element->parent.expired())
    {
      auto it = std::remove_if(elements.begin(), elements.end(),
                               [&](const auto &el)
                               { return el == element; });

      if (it != elements.end())
      {
        elements.erase(it, elements.end());
        return true;
      }
    }
    else
    {
      if (auto parent = element->parent.lock())
      {
        parent->RemoveChild(element);
        return true; // Element was removed from its parent
      }
    }

    return false;
  }

  UIManager::UIManager()
  {
    LumidiGui::Events::InitalizeDefaultBehaviors(defaultBehaviorsRegistry_);
  }

  void UIManager::Draw() const
  {
    for (const auto &element : elements)
    {
      if (element->isVisible)
      {
        element->Draw();
      }
    }
  }

  std::weak_ptr<Element> UIManager::GetElementByName(const std::string &name) const
  {
    auto it = elementMap.find(name);
    return (it != elementMap.end()) ? it->second : std::weak_ptr<Element>{};
  }
}