#ifndef LUMIDIGUI_FLUENTAPI_FLUENT_HANDLER_UIELEMENTS_H
#define LUMIDIGUI_FLUENTAPI_FLUENT_HANDLER_UIELEMENTS_H

#include "fluentHandler.h"
#include "concepts.h"

namespace LumidiGui
{
  namespace FluentAPI
  {
    template <DerivedFromUIElement T>
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

      FluentHandlerUIElements<T> &SetVisible(bool visible)
      {
        if (auto ptr = LockAsBase())
        {
          ptr->SetVisible(visible);
        }
        else
        {
          std::cerr << "[Fluent API] Warning: Element no longer exists. Was not able to change visiblity.\n";
        }
        return *this;
      }

      FluentHandlerUIElements<T> &SetSize(Vector3 size)
      {
        if (auto ptr = LockAsBase())
        {
          ptr->SetSize(size);
        }
        else
        {
          std::cerr << "[Fluent API] Warning: Element no longer exists. Was not able to set size.\n";
        }
        return *this;
      }

      FluentHandlerUIElements<T> &SetPosition(Vector3 position)
      {
        if (auto ptr = LockAsBase())
        {
          ptr->SetPosition(position); // ruft Element::SetPosition auf
        }
        else
        {
          std::cerr << "[Fluent API] Warning: Element no longer exists. Was not able set position.\n";
        }
        return *this;
      }
    };
  }
}

#endif