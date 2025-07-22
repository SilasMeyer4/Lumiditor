#include "uiManager.h"
#include <iostream>
#include "defaultBehaviors.h"

namespace LumidiGui
{

  void UIManager::Update(InputManager &inputManager)
  {

    auto scene = UIManager::activeScene_.lock();
    if (!scene)
      return;

    if (auto root = scene->GetRootElement().lock())
    {
      if (root->isVisible)
      {
        root->Update(inputManager);
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

    auto scene = UIManager::activeScene_.lock();
    if (!scene)
      return false;

    if (!element->parent.lock())
    {
      std::cerr << "[UIManager] Cannot remove root element '" << element->name << "'!" << std::endl;
      return false;
    }

    if (auto parent = element->parent.lock())
    {
      parent->RemoveChild(element);
    }

    scene->GetElementsMap().erase(element->name);
    return false;
  }

  std::shared_ptr<Scene> UIManager::GetScene(const std::string &sceneName) const
  {
    auto it = scenes_.find(sceneName);
    if (it == scenes_.end())
      return nullptr;
    auto scene = it->second;
  }

  UIManager::UIManager()
  {
    LumidiGui::Events::InitalizeDefaultBehaviors(defaultBehaviorsRegistry_);
  }

  void UIManager::Draw() const
  {
    auto scene = UIManager::activeScene_.lock();
    if (!scene)
      return;

    if (auto root = scene->GetRootElement().lock())
    {
      if (root->isVisible)
      {
        root->Draw();
      }
    }
  }

  std::weak_ptr<Element> UIManager::GetElementByName(const std::string &name) const
  {
    auto scene = UIManager::activeScene_.lock();
    if (!scene)
      return std::weak_ptr<Element>{};

    auto it = scene->GetElementsMap().find(name);
    return (it != scene->GetElementsMap().end()) ? it->second : std::weak_ptr<Element>{};
  }
}