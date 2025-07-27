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
    class DragBehavior : public UIBehavior
    {
    private:
      bool isDragging_ = false; // Track if the button was clicked
      std::string colliderLabel_;

    public:
      DragBehavior(std::weak_ptr<Element> parent, std::string colliderLabel)
          : UIBehavior(parent), colliderLabel_(colliderLabel) {}

      void Update(InputManager &inputManager) override;
    };
  }
}

#endif // LUMIDI_GUI_EVENTS_DRAG_BEHAVIOR_H