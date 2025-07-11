#ifndef LUMIDI_GUI_EVENTS_CLICK_BEHAVIOR_H
#define LUMIDI_GUI_EVENTS_CLICK_BEHAVIOR_H

#include <memory>
#include <functional>

#include "uiBehavior.h"
#include "uiElement2D.h"

namespace LumidiGui
{
  namespace Events
  {
    class ClickBehavior : public UIBehavior
    {
    private:
      std::function<void()> onClick_;
      bool isClicked_ = false; // Track if the button was clicked

    public:
      ClickBehavior(std::weak_ptr<UIElement2D> parent, std::function<void()> onClick)
          : UIBehavior(parent), onClick_(std::move(onClick)) {}

      void Update(InputManager &inputManager) override;
    };
  }
}

#endif // LUMIDI_GUI_EVENTS_CLICK_BEHAVIOR_H