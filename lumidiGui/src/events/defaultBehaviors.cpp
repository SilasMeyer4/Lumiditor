#include "defaultBehaviors.h"

namespace LumidiGui
{
  namespace Events
  {
    void InitalizeDefaultBehaviors(std::unordered_map<std::type_index, std::vector<std::function<void(std::shared_ptr<LumidiGui::Element>)>>> &defaultBehaviorsRegistry)
    {
      defaultBehaviorsRegistry = {
          // Checkbox default behavior: Switch isChecked OnClick
          {typeid(LumidiGui::Checkbox),
           {[](std::shared_ptr<LumidiGui::Element> elemBase)
            {
              // Cast to Checkbox
              auto elem = std::static_pointer_cast<LumidiGui::Checkbox>(elemBase);

              auto weakElem = std::weak_ptr<LumidiGui::Checkbox>(elem);

              std::function<void()> callback = [weakElem]()
              {
                if (auto locked = weakElem.lock())
                {
                  locked->isChecked = !locked->isChecked;
                }
              };

              elem->AddBehavior<LumidiGui::Events::ClickBehavior>(callback);
            }}}};
    }

  }

}