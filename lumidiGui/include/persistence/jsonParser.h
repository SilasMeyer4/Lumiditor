#ifndef LUMIDIGUI_PERSISTENCE_JSONPARSER_H
#define LUMIDIGUI_PERSISTENCE_JSONPARSER_H

#include "scene.h"
#include <functional>
#include <map>
#include <memory>
#include "nlohmann/json.hpp"
#include "uiComponents.h"

namespace LumidiGui
{
  namespace Data
  {

    using json = nlohmann::json;
    using JsonSerializeFunction = std::function<json(const std::shared_ptr<LumidiGui::Element> &)>;

    class JsonSerializer
    {
    private:
      std::string version_ = "0.1.0";
      std::string format_ = "LumidiGui";

    public:
      static JsonSerializer &Instance()
      {
        static JsonSerializer instance;
        return instance;
      }

      void SerializeScene(const std::shared_ptr<Scene> &scene, const std::string &filePath, const std::string &description = "")
      {
        auto rootElement = scene->GetRootElement().lock();
        if (!rootElement)
          throw std::runtime_error("[JsonParser]: Scene has no root element");

        json j;
        j["format"] = format_;
        j["version"] = version_;
        j["scene"]["name"] = description;
        j["scene"]["description"] = description;
        j["scene"]["rootElement"] = rootElement->GetName();
        j["scene"]["elementsMap"] = SerializeElementsMap(scene->GetElementsMap());
      }

      json SerializeElementsMap(const std::unordered_map<std::string, std::weak_ptr<Element>> &elementsMap)
      {
        json j;
        for (auto entry : elementsMap)
        {
          if (auto element = entry.second.lock())
          {
            j[element->GetName()] = SerializeElement(element);
          }
          else
          {
            std::cerr << "[JsonParser]: Element with name " << entry.first << " is not found\n";
          }
        }
        return j;
      }

      json SerializeElement(const std::shared_ptr<LumidiGui::Element> &element)
      {
        json j;
        j["name"] = element->GetName();
        j["type"] = element->GetType();

        j["position"] = json{{"x", element->GetPosition().x}, {"y", element->GetPosition().y}, {"z", element->GetPosition().z}};
        j["size"] = json{{"x", element->GetSize().x}, {"y", element->GetSize().y}, {"z", element->GetSize().z}};
        j["isVisible"] = element->IsVisible();
        j["isEnabled"] = element->IsEnabled();
        j["children"] = SerializeChildren(element->GetChildren());
        j["behaviors"] = SerializeBehaviors(element->GetBehaviors());
        j["colliders"] = SerializeColliders(element->GetColliders());
        return j;
      }

      json SerializeChildren(const std::vector<std::shared_ptr<LumidiGui::Element>> &children)
      {
        json j;
        for (auto child : children)
        {
          j.push_back(SerializeElement(child));
        }
        return j;
      }

      json SerializeBehaviors(const std::vector<std::shared_ptr<Events::UIBehavior>> &behaviors)
      {
        json j;
        for (auto behavior : behaviors)
        {
          j.push_back(SerializeBehavior(behavior));
        }
        return j;
      }

      json SerializeBehavior(const std::shared_ptr<Events::UIBehavior> &behaviors)
      {
        json j;
        j["type"] = behaviors.GetType();
        j["enabled"] = behaviors->isEnabled();
        // TODO how to serialize the lua functions
        return j;
      }
    };
  }
}

#endif