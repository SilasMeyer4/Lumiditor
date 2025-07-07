#ifndef LUMIDIGUI_EVENTS_UIBEHAVIOR_H
#define LUMIDIGUI_EVENTS_UIBEHAVIOR_H

#include "raylib.h"

namespace LumidiGui
{
  namespace Events
  {
    class UIBehavior
    {
    public:
      virtual void Update(Vector2 mousePosition, bool mousePressed) {}
      virtual void Render() {}
      virtual ~UIBehavior() = default;
    };
  }
}

#endif // LUMIDIGUI_EVENTS_UIBEHAVIOR_H