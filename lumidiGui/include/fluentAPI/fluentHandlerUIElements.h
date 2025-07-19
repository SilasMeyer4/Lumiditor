#ifndef LUMIDIGUI_FLUENTAPI_FLUENT_HANDLER_UIELEMENTS_H
#define LUMIDIGUI_FLUENTAPI_FLUENT_HANDLER_UIELEMENTS_H

#include "fluentHandler.h"
#include "concepts.h"

namespace LumidiGui
{
  namespace FluentAPI
  {
    template <DerivedFromUIElement2D T>
    class FluentHandlerUIElements : public FluentHandler<T>
    {
    private:
      std::shared_ptr<Element> LockAsBase() const
      {
        return std::static_pointer_cast<Element>(weakPtr_.lock());
      }

    public:
      using FluentHandler<T>::weakPtr_;
      FluentHandlerUIElements(std::weak_ptr<T> ptr) : FluentHandler<T>(ptr) {}

      template <DerivedFromUIBehavior Behavior, typename... Args>
      FluentHandlerUIElements<T> &AddBehavior(Args &&...args)
      {
        if (auto ptr = LockAsBase())
        {
          ptr->AddBehavior<Behavior>(std::forward<Args>(args)...);
        }
        else
        {
          std::cerr << "[Fluent API] Warning: Element no longer exists." << std::endl;
        }
        return *this;
      }
    };
  }
}

#endif