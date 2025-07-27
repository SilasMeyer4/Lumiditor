#ifndef LUMIDI_GUI_EVENTS_HOVER_BEHAVIOR_H
#define LUMIDI_GUI_EVENTS_HOVER_BEHAVIOR_H

#include <memory>
#include <functional>
#include "luaManager.h"
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
      sol::function luaOnHoverEnter_;
      sol::function luaOnHoverLeave_;
      bool isHovering_ = false;

    public:
      HoverBehavior(std::weak_ptr<Element> parent, std::string colliderLabel, std::function<void()> onEnter, std::function<void()> onLeave)
          : UIBehavior(parent), colliderLabel_(colliderLabel)
      {
        auto &lua = LumidiGui::LuaManager::Instance().Lua();
        lua["onHoverEnter"] = onEnter;
        lua["onHoverLeave"] = onLeave;
        luaOnHoverEnter_ = lua["onHoverEnter"];
        luaOnHoverLeave_ = lua["onHoverLeave"];
      }
      void Update(InputManager &inputManager) override;
    };

  }

}

#endif // LUMIDI_GUI_EVENTS_HOVER_BEHAVIOR_H