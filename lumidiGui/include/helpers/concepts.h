#ifndef LUMIDIGUI_CONCEPTS_H
#define LUMIDIGUI_CONCEPTS_H

#include <concepts>
#include <type_traits>
#include <string_view>
#include <memory>

namespace LumidiGui
{
  class Element;
  class Rectangle;
  class Collider;
  namespace Events
  {
    class UIBehavior;
  }

  template <typename T>
  concept StringLike = std::convertible_to<T, std::string_view>;

  template <typename T>
  concept SharedPointerType = (requires {
    typename std::decay_t<T>::element_type;
  } && std::same_as<std::decay_t<T>, std::shared_ptr<typename std::decay_t<T>::element_type>>);

  template <typename T>
  concept StringLikeOrSharedPointerType = StringLike<T> || SharedPointerType<T>;

  template <typename T>
  concept DerivedFromUIElement2D = std::derived_from<T, Element>;

  template <typename T>
  concept RectangleType = std::same_as<T, LumidiGui::Rectangle>;

  template <typename T>
  concept DerivedFromUIBehavior = std::derived_from<T, Events::UIBehavior>;

  template <typename T>
  concept DerivedFromCollider = std::derived_from<T, Collider>;
}

#endif // LUMIDIGUI_CONCEPTS_H
