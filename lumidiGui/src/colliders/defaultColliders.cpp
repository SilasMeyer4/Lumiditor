#include "defaultColliders.h"
#include "button.h"
#include "uiComponents.h"
#include "uiColliders.h"

void LumidiGui::InitializeDefaultColliders(std::unordered_map<std::type_index, std::vector<std::function<void(std::shared_ptr<LumidiGui::Element>)>>> &defaultCollidersRegistry)
{
  defaultCollidersRegistry = {

      {typeid(LumidiGui::Button),
       {[](std::shared_ptr<LumidiGui::Element> elemBase)
        {
          // Cast to Checkbox
          auto elem = std::static_pointer_cast<LumidiGui::Button>(elemBase);

          auto weakElem = std::weak_ptr<LumidiGui::Button>(elem);

          elem->AddCollider<LumidiGui::RectangleCollider>("default");
        }}},
      {typeid(LumidiGui::Checkbox),
       {[](std::shared_ptr<LumidiGui::Element> elemBase)
        {
          // Cast to Checkbox
          auto elem = std::static_pointer_cast<LumidiGui::Checkbox>(elemBase);

          auto weakElem = std::weak_ptr<LumidiGui::Checkbox>(elem);

          elem->AddCollider<LumidiGui::RectangleCollider>("default");
        }}}};
}
