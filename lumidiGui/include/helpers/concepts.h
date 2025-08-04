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
  class Scene;
  namespace Events
  {
    class UIBehavior;
  }

  namespace Data
  {
    class Serializer;
  }

  /**
   * @brief Concept for types convertible to std::string_view.
   */
  template <typename T>
  concept StringLike = std::convertible_to<T, std::string_view>;

  /**
   * @brief Concept for std::shared_ptr types.
   *
   * Matches any type that is a std::shared_ptr of some element type.
   */
  template <typename T>
  concept SharedPointerType = (requires {
    typename std::decay_t<T>::element_type;
  } && std::same_as<std::decay_t<T>, std::shared_ptr<typename std::decay_t<T>::element_type>>);

  /**
   * @brief Concept for types that are either StringLike or SharedPointerType.
   */
  template <typename T>
  concept StringLikeOrSharedPointerType = StringLike<T> || SharedPointerType<T>;

  /**
   * @brief Concept for types derived from LumidiGui::Element.
   */
  template <typename T>
  concept DerivedFromUIElement = std::derived_from<T, Element>;

  /**
   * @brief Concept for types that are exactly LumidiGui::Rectangle.
   */
  template <typename T>
  concept RectangleType = std::same_as<T, LumidiGui::Rectangle>;

  /**
   * @brief Concept for types derived from LumidiGui::Events::UIBehavior.
   */
  template <typename T>
  concept DerivedFromUIBehavior = std::derived_from<T, Events::UIBehavior>;

  /**
   * @brief Concept for types derived from LumidiGui::Collider.
   */
  template <typename T>
  concept DerivedFromCollider = std::derived_from<T, Collider>;

  /**
   * @brief Concept for types derived from LumidiGui::Scene.
   */
  template <typename T>
  concept DerivedFromScene = std::derived_from<T, Scene>;

  /**
   * @brief Concept for types derived from LumidiGui::Data::Serializer.
   */
  template <typename T>
  concept DerivedFromSerializer = std::derived_from<T, Data::Serializer>;
}

#endif // LUMIDIGUI_CONCEPTS_H
