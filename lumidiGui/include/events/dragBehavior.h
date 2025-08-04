#ifndef LUMIDI_GUI_EVENTS_DRAG_BEHAVIOR_H
#define LUMIDI_GUI_EVENTS_DRAG_BEHAVIOR_H

#include <memory>
#include <functional>

#include "uiBehavior.h"
#include "element.h"
#include "inputManager.h"

namespace LumidiGui
{
  namespace Events
  {
    /**
     * @class DragBehavior
     * @brief UI behavior for handling drag events on elements.
     *
     * This behavior allows an element to be dragged using mouse or pointer input.
     */
    class DragBehavior : public UIBehavior
    {
    private:
      /**
       * @brief Tracks whether the element is currently being dragged.
       */
      bool isDragging_ = false;

      /**
       * @brief The label of the collider used for drag detection.
       */
      std::string colliderLabel_;

    public:
      /**
       * @brief Constructs a DragBehavior with a parent element and collider label.
       * @param parent Weak pointer to the parent element.
       * @param colliderLabel The label of the collider to use for drag detection.
       */
      DragBehavior(std::weak_ptr<Element> parent, std::string colliderLabel)
          : UIBehavior(parent), colliderLabel_(colliderLabel) {}

      /**
       * @brief Updates the drag state and handles dragging logic.
       * @param inputManager Reference to the input manager.
       */
      void Update(InputManager &inputManager) override;
    };
  }
}

#endif // LUMIDI_GUI_EVENTS_DRAG_BEHAVIOR_H