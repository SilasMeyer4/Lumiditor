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
      bool isDragging_ = false; // Track if the button was clicked

    public:
      DragBehavior(std::weak_ptr<UIElement2D> parent)
          : UIBehavior(parent) {}

      void Update(InputManager &inputManager) override;
    };
  }
}

#endif // LUMIDI_GUI_EVENTS_DRAG_BEHAVIOR_H