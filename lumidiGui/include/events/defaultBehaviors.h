#ifndef LUMIDIGUI_EVENTS_DEFAULTBEHAVIORS_H
#define LUMIDIGUI_EVENTS_DEFAULTBEHAVIORS_H

/**
 * @file defaultBehaviors.h
 * @brief Declaration of default UI behaviors and their registration for LumidiGui.
 *
 * This header provides type definitions and the initialization function for default UI behaviors
 * that can be automatically assigned to UI elements.
 */

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
    /**
     * @brief Factory function type for adding behaviors to UI elements.
     *
     * Used to register default behaviors for different UI element types.
     */
    using BehaviorFactory = std::function<void(std::shared_ptr<LumidiGui::Element>)>;

    /**
     * @brief Initializes and registers the default UI behaviors.
     *
     * Adds default behaviors for known UI element types to the provided registry container.
     * @param defaultBehaviorsRegistry The registry to which the default behaviors will be added.
     */
    void InitalizeDefaultBehaviors(std::unordered_map<std::type_index, std::vector<std::function<void(std::shared_ptr<LumidiGui::Element>)>>> &defaultBehaviorsRegistry);

  }

}

#endif