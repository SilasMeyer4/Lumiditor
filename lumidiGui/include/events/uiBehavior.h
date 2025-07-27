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

    class UIBehavior
    {
    protected:
      std::weak_ptr<Element> parent_;

    public:
      virtual void Update(InputManager &inputManager) = 0;
      UIBehavior(std::weak_ptr<Element> parent) : parent_(parent) {}
      virtual void Render() {}
      virtual ~UIBehavior() = default;
      bool isEnabled = true;
    };
  }
}

#endif // LUMIDIGUI_EVENTS_UIBEHAVIOR_H