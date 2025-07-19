#ifndef LUMIDI_GUI_EVENTS_HOVER_BEHAVIOR_H
#define LUMIDI_GUI_EVENTS_HOVER_BEHAVIOR_H

#include <memory>
#include <functional>

#include "uiBehavior.h"
#include "element.h"

namespace LumidiGui
{
  namespace Events
  {
    class HoverBehavior : public UIBehavior
    {
    private:
      std::string colliderLabel_;
      std::function<void()> onHoverEnter_;
      std::function<void()> onHoverLeave_;
      bool isHovering_ = false;

    public:
      HoverBehavior(std::weak_ptr<Element> parent, std::string colliderLabel, std::function<void()> onEnter, std::function<void()> onLeave)
          : UIBehavior(parent), colliderLabel_(colliderLabel), onHoverEnter_(std::move(onEnter)), onHoverLeave_(std::move(onLeave)) {}

      void Update(InputManager &inputManager) override;
    };
  }
}

#endif // LUMIDI_GUI_EVENTS_HOVER_BEHAVIOR_H