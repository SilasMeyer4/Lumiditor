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

    class JsonSerializerRegistry
    {
    public:
      static JsonSerializerRegistry &Instance()
      {
        static JsonSerializerRegistry instance;
        return instance;
      }

      void Register(const std::string &typeName, JsonSerializeFunction func)
      {
        registry_[typeName] = std::move(func);
      }

      json Serialize(const std::string &typeName, const std::shared_ptr<LumidiGui::Element> &elem)
      {
        auto it = registry_.find(typeName);
        if (it != registry_.end())
        {
          return it->second(elem);
        }
        // Fallback
        return DefaultSerialize(elem);
      }

      // Serialisierung mit RTTI - hole Typ aus shared_ptr und rufe Serialize auf
      json Serialize(const std::shared_ptr<LumidiGui::Element> &elem)
      {
        if (!elem)
          return json();
        return Serialize(typeid(*elem).name(), elem);
      }

    private:
      std::unordered_map<std::string, JsonSerializeFunction> registry_;

      static json DefaultSerialize(const std::shared_ptr<LumidiGui::Element> &elem)
      {
        json j = SerializeBaseElement(elem);
        return j;
      }
    };

    // Beispiel-Helper zum Registrieren
    template <typename T>
    struct JsonSerializerRegister
    {
      JsonSerializerRegister()
      {
        JsonSerializerRegistry::Instance().Register(typeid(T).name(),
                                                    [](const std::shared_ptr<LumidiGui::Element> &elem) -> json
                                                    {
                                                      auto casted = std::dynamic_pointer_cast<T>(elem);
                                                      if (casted)
                                                      {
                                                        return SerializeSpecific(casted);
                                                      }
                                                      return json();
                                                    });
      }
    };

    json SerializeSpecific(const std::shared_ptr<LumidiGui::Button> &button)
    {
      json j = SerializeBaseElement(button);
      j["type"] = "Button";
      j["name"] = button->name;
      // ... button-spezifische Daten
      return j;
    }

    json SerializeBaseElement(const std::shared_ptr<LumidiGui::Element> &elem)
    {
      return JsonSerializerRegistry::Instance().Serialize(typeid(LumidiGui::Element).name(), elem);
    }

    static JsonSerializerRegister<LumidiGui::Button> registerButton;
    static JsonSerializerRegister<LumidiGui::Element> registerElement;

  }
}

#endif