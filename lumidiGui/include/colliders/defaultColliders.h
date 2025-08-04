#ifndef LUMIDIGUI_DEFAULTCOLLIDERS_H
#define LUMIDIGUI_DEFAULTCOLLIDERS_H

#include "element.h"
#include "concepts.h"
#include <memory>
#include <typeindex>
#include <vector>
#include <unordered_map>
#include <functional>

namespace LumidiGui
{

  using ColliderFactory = std::function<void(std::shared_ptr<LumidiGui::Element>)>;

  /**
   * @brief Registers default collider functions for various element types.
   *
   * This function initializes the default colliders registry by associating
   * each supported element type (identified by std::type_index) with a list
   * of collider functions. Each collider function operates on a shared pointer
   * to a LumidiGui::Element.
   *
   * @param defaultCollidersRegistry
   *        Reference to a map where the key is the type index of an element,
   *        and the value is a vector of functions to be used as default colliders
   *        for that element type.
   */
  void InitializeDefaultColliders(std::unordered_map<std::type_index, std::vector<std::function<void(std::shared_ptr<LumidiGui::Element>)>>> &defaultCollidersRegistry);

}

#endif