#ifndef LUMIDIGUI_EVENTS_UIBEHAVIOR_H
#define LUMIDIGUI_EVENTS_UIBEHAVIOR_H

#include "raylib.h"
#include <memory>

namespace LumidiGui
{
  class UIElement2D;
  namespace Events
  {

    class UIBehavior
    {
    protected:
      std::weak_ptr<UIElement2D> parent_;

    public:
      virtual void Update(Vector2 mousePosition, bool mousePressed) {}
      UIBehavior(std::weak_ptr<UIElement2D> parent) : parent_(parent) {}
      virtual void Render() {}
      virtual ~UIBehavior() = default;
      bool isEnabled = true;
    };
  }
}

#endif // LUMIDIGUI_EVENTS_UIBEHAVIOR_H