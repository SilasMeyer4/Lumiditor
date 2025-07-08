#ifndef LUMIDITOR_UIMANAGER_H
#define LUMIDITOR_UIMANAGER_H

#include <memory>
#include "uiElement2D.h"
#include <vector>

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
    std::vector<std::shared_ptr<UIElement2D>> elements;                       // Vector to hold UI elements
    std::unordered_map<std::string, std::shared_ptr<UIElement2D>> elementMap; // Map to hold UI elements by name for quick access
  public:
    // Constructor
    UIManager() = default;

    /**
     * @brief Flag to allow or disallow multiple UI elements with the same name.
     * If set to false (default), adding an element with an existing name will fail.
     */
    bool allowDuplicateNames = false; // Flag to allow multiple UI elements with the same name

    /**
     * @brief Adds a single UI element to the manager.
     *
     * @param element The element to add.
     * @return true if the element was added successfully.
     * @return false if an element with the same name already exists and duplicates are not allowed.
     */
    bool AddElement(std::shared_ptr<UIElement2D> element);

    /**
     * @brief Adds multiple UI elements to the manager.
     *
     * @tparam Elements Variadic template parameter.
     * @param elements Elements to add.
     * @return true if all elements were added successfully, false otherwise.
     */
    template <typename... Elements>
    bool AddElements(Elements &&...elements)
    {
      return (AddElement(std::forward<Elements>(elements)) && ...);
    }

    /**
     * @brief Retrieves a UI element by its name.
     *
     * @param name Name of the element.
     * @return A shared pointer to the element, or nullptr if not found.
     */
    std::shared_ptr<UIElement2D> GetElementByName(const std::string &name) const;

    /**
     * @brief Updates all managed UI elements with the current mouse state.
     *
     * @param mousePosition The current position of the mouse.
     * @param mousePressed Whether the mouse is pressed.
     */
    void Update(Vector2 mousePosition, bool mousePressed = false);

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
    bool RemoveElement(std::shared_ptr<UIElement2D> element);

    template <typename... Elements>
    bool RemoveElements(Elements &&...elements)
    {
      return (RemoveElement(std::forward<Elements>(elements)) && ...);
    }

    /**
     * @brief Renders all UI elements by calling their Draw() method.
     */
    void Draw() const;
  };
}

#endif // LUMIDITOR_UIMANAGER_H
