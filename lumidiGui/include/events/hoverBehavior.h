#ifndef LUMIDI_GUI_EVENTS_HOVER_BEHAVIOR_H
#define LUMIDI_GUI_EVENTS_HOVER_BEHAVIOR_H

#include <memory>
#include <functional>

#include "uiBehavior.h"
#include "uiElement2D.h"

namespace LumidiGui
{
  namespace Events
  {
    class HoverBehavior : public UIBehavior
    {
    private:
      std::function<void()> onHoverEnter_;
      std::function<void()> onHoverLeave_;
      bool isHovering_ = false;

    public:
      HoverBehavior(std::weak_ptr<UIElement2D> parent, std::function<void()> onEnter, std::function<void()> onLeave)
          : UIBehavior(parent), onHoverEnter_(std::move(onEnter)), onHoverLeave_(std::move(onLeave)) {}

      void Update(InputManager &inputManager) override;
    };
  }
}

#endif // LUMIDI_GUI_EVENTS_HOVER_BEHAVIOR_H