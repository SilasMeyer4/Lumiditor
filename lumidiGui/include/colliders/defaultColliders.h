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

  void InitializeDefaultColliders(std::unordered_map<std::type_index, std::vector<std::function<void(std::shared_ptr<LumidiGui::Element>)>>> &defaultCollidersRegistry);

}

#endif