#ifndef LUMIDI_GUI_EVENTS_LUA_MANAGER_H
#define LUMIDI_GUI_EVENTS_LUA_MANAGER_H

#include "sol/sol.hpp"

namespace LumidiGui
{
  class LuaManager
  {
  private:
    sol::state lua_;
    LuaManager()
    {
      lua_.open_libraries(sol::lib::base, sol::lib::math);
    }

  public:
    static LuaManager &Instance()
    {
      static LuaManager instance;
      return instance;
    }

    sol::state &Lua() { return lua_; }
    void RegisterFunction(const std::string &name, std::function<void()> function)
    {
      lua_[name] = function;
    }

    void RunFunction(const std::string &name)
    {
      sol::function func = lua_[name];
      if (func.valid())
        func();
    }
  };
}

#endif