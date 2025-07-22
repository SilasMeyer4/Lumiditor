#ifndef LUMIDITOR_UIMANAGER_H
#define LUMIDITOR_UIMANAGER_H

#include <memory>
#include "element.h"
#include "concepts.h"
#include <vector>
#include <iostream>
#include "inputManager.h"
#include "defaultBehaviors.h"
#include "scene.h"

namespace LumidiGui
{

  /**
   * @brief Manages a collection of 2D UI elements.
   *
   * Handles drawing, updating, and organizing UI elements,
   * including optional name-based indexing for efficient access.
   */
  class UIManager
  {
  private:
    std::weak_ptr<Scene> activeScene_;
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes_; // Vector to hold UI elements
    std::unordered_map<std::type_index, std::vector<std::function<void(std::shared_ptr<LumidiGui::Element>)>>> defaultBehaviorsRegistry_;
    bool RemoveElement(std::shared_ptr<Element> element);

    std::shared_ptr<Scene> GetScene(const std::string &sceneName) const;

    template <typename UIElementT>
    void AddDefaultBehaviors(std::shared_ptr<UIElementT> element)
    {
      auto it = defaultBehaviorsRegistry_.find(typeid(UIElementT));
      if (it != defaultBehaviorsRegistry_.end())
      {
        for (auto &factory : it->second)
        {
          factory(element);
        }
      }
    }

  public:
    // Constructor
    UIManager();

    template <DerivedFromScene T, typename... Args>
    std::weak_ptr<T> CreateScene(const std::string &name, Args &&...args)
    {

      // Namenskonflikt abfangen
      if (scenes_.contains(name))
      {
        std::cerr << "[UIManager] Element with name '" << name << "' already exists!" << std::endl;
        return std::weak_ptr<T>{}; // empty weakpointer
      }
      auto scene = std::make_shared<T>(name, std::forward<Args>(args)...);
      scenes_[name] = scene;
      return scene;
    }

    template <DerivedFromScene T, typename... Args>
    std::weak_ptr<T> CreateSceneAndSetAsActive(const std::string &name, Args &&...args)
    {
      auto scene = CreateScene<T>(name, std::forward<Args>(args)...);
      if (auto sharedScene = scene.lock())
      {
        activeScene_ = sharedScene;
      }
      return scene;
    }

    template <DerivedFromUIElement2D T, typename... Args>
    std::weak_ptr<T> CreateChild(const std::string &name, const std::string &parentName, Args &&...args)
    {

      auto scene = activeScene_.lock();
      if (!scene)
        return std::weak_ptr<T>{};

      // Namenskonflikt abfangen
      if (scene->GetElementsMap().contains(name))
      {
        std::cerr << "[UIManager] Element with name '" << name << "' already exists!" << std::endl;
        return std::weak_ptr<T>{}; // empty weakpointer
      }

      auto weakParent = GetElementByName(parentName);
      auto parent = weakParent.lock();
      if (!parent)
      {
        std::cerr << "[UIManager] Parent element with name '" << parentName << "' not found!" << std::endl;
        return std::weak_ptr<T>{}; // empty weakpointer
      }

      auto element = std::make_shared<T>(name, std::forward<Args>(args)...);
      AddDefaultBehaviors<T>(element);
      parent->AddChild(element); // Add the new element as a child of the parent
      scene->GetElementsMap()[name] = element;
      return element;
    }

    /**
     * @brief Retrieves a UI element by its name.
     *
     * @param name Name of the element.
     * @return A weak pointer to the element, or nullptr if not found.
     */
    std::weak_ptr<Element> GetElementByName(const std::string &name) const;

    template <DerivedFromUIElement2D T>
    std::weak_ptr<T> GetElementByNameAs(const std::string &name) const
    {

      auto scene = activeScene_.lock();
      if (!scene)
        return std::weak_ptr<T>{}; // empty weakpointer

      auto it = scene->GetElementsMap().find(name);

      if (it == scene->GetElementsMap().end())
      {
        std::cerr << "[UIManager] Element with name '" << name << "' not found!" << std::endl;
        return std::weak_ptr<T>{}; // empty weakpointer
      }

      auto casted = std::dynamic_pointer_cast<T>(it->second.lock());
      if (!casted)
      {
        std::cerr << "[UIManager] Element with name '" << name << "' is not of type " << typeid(T).name() << "!" << std::endl;
        return std::weak_ptr<T>{}; // empty weakpointer
      }

      return casted;
    }

    /**
     * @brief Updates all managed UI elements with the current mouse state.
     *
     * @param mousePosition The current position of the mouse.
     * @param mousePressed Whether the mouse is pressed.
     */
    void Update(InputManager &InputManager);

    /**
     * @brief Removes an element by its name.
     *
     * @param name The name of the element to remove.
     * @return true if the element was removed.
     * @return false if the element was not found.
     */
    bool RemoveElement(const std::string &name);

    /**
     * @brief Removes multiple UI elements from the manager.
     *
     * @tparam Elements Variadic template parameter.
     * @param elements Elements to remove.
     * @return true if all elements were removed successfully, false otherwise.
     */
    template <StringLike... Elements>
    bool RemoveElements(Elements &&...elements)
    {
      return (RemoveElement(std::forward<Elements>(elements)) && ...);
    }

    bool MoveChildToParent(const std::string &childName, const std::string &newParentName, const std::string &sceneName)
    {

      auto it = scenes_.find(sceneName);
      if (it == scenes_.end())
        return false;
      auto scene = it->second;

      auto child = GetElementByName(childName).lock();
      auto newParent = GetElementByName(newParentName).lock();

      if (!child)
      {
        std::cerr << "[UIManager] Child element with name '" << childName << "' not found!" << std::endl;
        return false; // Return false if the child was not found
      }

      if (!newParent)
      {
        std::cerr << "[UIManager] New parent element with name '" << newParentName << "' not found!" << std::endl;
        return false; // Return false if the new parent was not found
      }

      if (auto oldParent = child->parent.lock())
      {
        oldParent->RemoveChild(child); // Remove from the old parent
      }
      else
      {
        return true; // child is root, can't be moved.
      }

      newParent->AddChild(child); // Add the child to the new parent'

      return true; // Return false if either the child or parent was not found
    }

    /**
     * @brief Renders all UI elements by calling their Draw() method.
     */
    void Draw() const;
  };

}

#endif // LUMIDITOR_UIMANAGER_H
