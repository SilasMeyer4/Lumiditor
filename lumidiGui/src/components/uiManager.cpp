#include "uiManager.h"
#include <iostream>
#include "defaultBehaviors.h"

namespace LumidiGui
{
  void UIManager::ChangeWindowSize(int newWindowWidth, int newWindowHeight)
  {
    SetWindowSize(newWindowWidth, newWindowHeight);

    if (auto scene = activeScene_.lock())
    {
      if (auto root = scene->GetRootElement().lock())
      {
        root->UpdateLayout(newWindowWidth, newWindowHeight);
      }
    }
  }

  void UIManager::Update(InputManager &inputManager)
  {

    auto scene = UIManager::activeScene_.lock();
    if (!scene)
      return;

    if (auto root = scene->GetRootElement().lock())
    {
      if (root->IsVisible())
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
      std::cerr << "[UIManager] Cannot remove root element '" << element->GetName() << "'!" << std::endl;
      return false;
    }

    if (auto parent = element->parent.lock())
    {
      parent->RemoveChild(element);
    }

    scene->GetElementsMap().erase(element->GetName());
    return false;
  }

  std::shared_ptr<Scene> UIManager::GetScene(const std::string &sceneName) const
  {
    auto it = scenes_.find(sceneName);
    if (it == scenes_.end())
      return nullptr;
    auto scene = it->second;

    return scene;
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
      if (root->IsVisible())
      {
        root->Draw();
      }
    }
  }

  bool UIManager::ChangeElementName(const std::string &oldName, const std::string &newName, const std::string &sceneName)
  {
    auto weakElement = GetElementByName(oldName);
    if (auto element = weakElement.lock())
    {
      auto it = scenes_.find(sceneName);
      if (it != scenes_.end())
      {
        auto scene = it->second;
        if (scene)
        {
          element->SetName(newName);
          scene->GetElementsMap().erase(oldName);
          scene->GetElementsMap()[newName] = element;
          return true;
        }
      }
    }
    return false;
  }

  bool UIManager::ChangeElementName(const std::string &oldName, const std::string &newName)
  {
    if (auto scene = activeScene_.lock())
    {
      return ChangeElementName(oldName, newName, scene->GetName());
    }
    return false;
  }

  std::weak_ptr<Element> UIManager::GetElementByName(const std::string &name) const
  {
    auto scene = UIManager::activeScene_.lock();
    if (!scene)
      return std::weak_ptr<Element>{};

    auto it = scene->GetElementsMap().find(name);
    return (it != scene->GetElementsMap().end()) ? it->second : std::weak_ptr<Element>{};
  }
  void UIManager::SaveActiveScene()
  {
    if (auto scene = activeScene_.lock())
    {
      try
      {
        serializer_->SerializeScene(*scene);
      }
      catch (const std::exception &e)
      {
        std::cerr << e.what() << '\n';
      }
    }
  }
  void UIManager::SaveAllScenes()
  {
    for (const auto &scene : scenes_)
    {
      try
      {
        serializer_->SerializeScene(*scene.second);
      }
      catch (const std::exception &e)
      {
        std::cerr << e.what() << '\n';
      }
    }
  }
}