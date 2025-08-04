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
    /**
     * @class ClickBehavior
     * @brief UI behavior for handling click events on elements.
     *
     * This behavior allows an element to react to click events, including integration with Lua callbacks.
     */
    class ClickBehavior : public UIBehavior
    {
    private:
      /**
       * @brief Lua function to be called on click.
       */
      sol::function luaOnClick_;

      /**
       * @brief Internal state to track if the element is currently clicked.
       */
      bool isClicked_ = false;

    public:
      /**
       * @brief Constructs a ClickBehavior with a parent element and a C++ onClick callback.
       * @param parent Weak pointer to the parent element.
       * @param onClick C++ function to be called on click (also exposed to Lua).
       */
      ClickBehavior(std::weak_ptr<Element> parent, std::function<void()> onClick)
          : UIBehavior(parent)
      {
        auto &lua = LumidiGui::LuaManager::Instance().Lua();
        lua["onClick"] = onClick;
        luaOnClick_ = lua["onClick"];
      }

      /**
       * @brief Updates the click state and triggers the callback if clicked.
       * @param inputManager Reference to the input manager.
       */
      void Update(InputManager &inputManager) override;
    };
  }
}

#endif // LUMIDI_GUI_EVENTS_CLICK_BEHAVIOR_H