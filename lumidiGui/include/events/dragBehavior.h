#ifndef LUMIDI_GUI_EVENTS_DRAG_BEHAVIOR_H
#define LUMIDI_GUI_EVENTS_DRAG_BEHAVIOR_H

#include <memory>
#include <functional>

#include "uiBehavior.h"
#include "uiElement2D.h"
#include "inputManager.h"

namespace LumidiGui
{
  namespace Events
  {
    class DragBehavior : public UIBehavior
    {
    private:
      bool isDragging_ = false;     // Track if the button was clicked
      Vector2 lastElementPosition_; // Store the initial position when dragging starts
      Vector2 lastMousePosition_;
      int leaveTimerMs_ = 100;
      int leaveCounter_ = 0;

    public:
      DragBehavior(std::weak_ptr<UIElement2D> parent)
          : UIBehavior(parent) {}

      void Update(InputManager &inputManager) override;

      void SetLeaveTimerMs(int miliseconds)
      {
        leaveTimerMs_ = miliseconds;
      }
    };
  }
}

#endif // LUMIDI_GUI_EVENTS_DRAG_BEHAVIOR_H