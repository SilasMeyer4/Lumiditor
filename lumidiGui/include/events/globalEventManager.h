#ifndef LUMIDI_GUI_EVENTS_GLOBAL_EVENT_MANAGER_H
#define LUMIDI_GUI_EVENTS_GLOBAL_EVENT_MANAGER_H

namespace LumidiGui
{
  class GlobalEventManager
  {
  private:
    GlobalEventManager() = default;

  public:
    // Delete copy constructor and assignment operator to prevent copying
    GlobalEventManager(const GlobalEventManager &) = delete;
    GlobalEventManager &operator=(const GlobalEventManager &) = delete;

    // Method to get the singleton instance
    static GlobalEventManager &GetInstance()
    {
      static GlobalEventManager instance; // Guaranteed to be destroyed, instantiated on first use
      return instance;
    }
  };
}

#endif