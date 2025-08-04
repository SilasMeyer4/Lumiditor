#ifndef LUMIDIGUI_EVENTS_UIBEHAVIOR_H
#define LUMIDIGUI_EVENTS_UIBEHAVIOR_H

#include "raylib.h"
#include "inputManager.h"
#include <memory>

namespace LumidiGui
{
  class Element;
  namespace Events
  {
    /**
     * @class UIBehavior
     * @brief Abstract base class for UI behaviors attached to elements.
     *
     * Provides an interface for update and render logic that can be attached to UI elements.
     */
    class UIBehavior
    {
    protected:
      /**
       * @brief Weak pointer to the parent element this behavior is attached to.
       */
      std::weak_ptr<Element> parent_;

    public:
      /**
       * @brief Updates the behavior based on input.
       * @param inputManager Reference to the input manager.
       */
      virtual void Update(InputManager &inputManager) = 0;

      /**
       * @brief Constructs a UIBehavior with a parent element.
       * @param parent Weak pointer to the parent element.
       */
      UIBehavior(std::weak_ptr<Element> parent) : parent_(parent) {}

      /**
       * @brief Renders the behavior (optional override).
       */
      virtual void Render() {}

      /**
       * @brief Virtual destructor.
       */
      virtual ~UIBehavior() = default;

      /**
       * @brief Whether this behavior is enabled.
       */
      bool isEnabled = true;
    };
  }
}

#endif // LUMIDIGUI_EVENTS_UIBEHAVIOR_H