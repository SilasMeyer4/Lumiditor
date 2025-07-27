#ifndef LUMIDI_GUI_EVENTS_CLICK_BEHAVIOR_H
#define LUMIDI_GUI_EVENTS_CLICK_BEHAVIOR_H

#include <memory>
#include <functional>
#include "luaManager.h"
#include "uiBehavior.h"
#include "element.h"

namespace LumidiGui
{
  namespace Events
  {
    class ClickBehavior : public UIBehavior
    {
    private:
      sol::function luaOnClick_;
      bool isClicked_ = false;

    public:
      ClickBehavior(std::weak_ptr<Element> parent, std::function<void()> onClick)
          : UIBehavior(parent)
      {
        auto &lua = LumidiGui::LuaManager::Instance().Lua();
        lua["onClick"] = onClick;
        luaOnClick_ = lua["onClick"];
      }

      void Update(InputManager &inputManager) override;
    };
  }
}

#endif // LUMIDI_GUI_EVENTS_CLICK_BEHAVIOR_H