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
      std::weak_ptr<UIElement2D> parent_;
      std::function<void()> onClick_;

    public:
      ClickBehavior(std::shared_ptr<UIElement2D> parent, std::function<void()> onClick)
          : parent_(parent), onClick_(std::move(onClick)) {}

      void Update(Vector2 mousePosition, bool mousePressed) override;
    };
  }
}

#endif // LUMIDI_GUI_EVENTS_CLICK_BEHAVIOR_H