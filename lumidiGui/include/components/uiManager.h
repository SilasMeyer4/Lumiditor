#ifndef LUMIDITOR_UIMANAGER_H
#define LUMIDITOR_UIMANAGER_H

#include <memory>
#include "uiElement2D.h"
#include "concepts.h"
#include <vector>
#include <iostream>
#include "inputManager.h"
#include "defaultBehaviors.h"

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
    std::vector<std::shared_ptr<UIElement2D>> elements;                     // Vector to hold UI elements
    std::unordered_map<std::string, std::weak_ptr<UIElement2D>> elementMap; // Map to hold UI elements by name for quick access
    std::unordered_map<std::type_index, std::vector<std::function<void(std::shared_ptr<LumidiGui::UIElement2D>)>>> defaultBehaviorsRegistry_;
    bool RemoveElement(std::shared_ptr<UIElement2D> element);

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

    /**
     * @brief Flag to allow or disallow multiple UI elements with the same name.
     * If set to false (default), adding an element with an existing name will fail.
     */
    bool allowDuplicateNames = false; // Flag to allow multiple UI elements with the same name

    template <DerivedFromUIElement2D T, typename... Args>
    std::weak_ptr<T> Create(const std::string &name, Args &&...args)
    {
      // Namenskonflikt abfangen
      if (elementMap.contains(name))
      {
        std::cerr << "[UIManager] Element with name '" << name << "' already exists!" << std::endl;
        return std::weak_ptr<T>{}; // empty weakpointer
      }
      auto element = std::make_shared<T>(name, std::forward<Args>(args)...);
      elementMap[name] = element;
      elements.push_back(element);
      AddDefaultBehaviors<T>(element);
      return element;
    }

    template <DerivedFromUIElement2D T, typename... Args>
    std::weak_ptr<T> CreateChild(const std::string &name, const std::string &parentName, Args &&...args)
    {
      // Namenskonflikt abfangen
      if (elementMap.contains(name))
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
      parent->AddChild(element); // Add the new element as a child of the parent
      elementMap[name] = element;
      return element;
    }

    /**
     * @brief Retrieves a UI element by its name.
     *
     * @param name Name of the element.
     * @return A weak pointer to the element, or nullptr if not found.
     */
    std::weak_ptr<UIElement2D> GetElementByName(const std::string &name) const;

    template <DerivedFromUIElement2D T>
    std::weak_ptr<T> GetElementByNameAs(const std::string &name) const
    {
      auto it = elementMap.find(name);

      if (it == elementMap.end())
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

    bool MoveChildToParent(const std::string &childName, const std::string &newParentName)
    {
      auto child = GetElementByName(childName).lock();
      ;
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
        // If the child has no parent, we need to remove it from the to level elements vector
        auto it = std::remove(elements.begin(), elements.end(), child);
        if (it != elements.end())
        {
          elements.erase(it, elements.end());
        }
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
