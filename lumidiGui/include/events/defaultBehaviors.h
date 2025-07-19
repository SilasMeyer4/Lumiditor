#ifndef LUMIDIGUI_EVENTS_DEFAULTBEHAVIORS_H
#define LUMIDIGUI_EVENTS_DEFAULTBEHAVIORS_H

#include "checkbox.h"
#include "element.h"
#include "uiEvents.h"
#include "concepts.h"
#include <memory>
#include <typeindex>
#include <vector>
#include <unordered_map>
#include <functional>

namespace LumidiGui
{
  namespace Events
  {
    using BehaviorFactory = std::function<void(std::shared_ptr<LumidiGui::Element>)>;

    void InitalizeDefaultBehaviors(std::unordered_map<std::type_index, std::vector<std::function<void(std::shared_ptr<LumidiGui::Element>)>>> &defaultBehaviorsRegistry);

  }

}

#endif