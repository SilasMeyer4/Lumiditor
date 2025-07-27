#ifndef LUMIDIGUI_FLUENTAPI_FLUENT_HANDLER_H
#define LUMIDIGUI_FLUENTAPI_FLUENT_HANDLER_H

#include <memory>

namespace LumidiGui
{
  namespace FluentAPI
  {
    template <typename T>
    class FluentHandler
    {
    protected:
      std::weak_ptr<T> weakPtr_;

    public:
      FluentHandler(std::weak_ptr<T> ptr) : weakPtr_(ptr) {}
      std::shared_ptr<T> GetShared() const { return weakPtr_.lock(); }
      bool IsValid() const { return !weakPtr_.expired(); }
      // Implement the FluentHandler class here
    };
  }
}

#endif