#ifndef LUMIDIGUI_SCENE_H
#define LUMIDIGUI_SCENE_H

#include <memory>
#include <map>
#include <vector>
#include <element.h>
#include <string>

namespace LumidiGui
{
  class Scene
  {

  private:
    std::shared_ptr<Element> rootElement_;                               // Vector to hold UI elements
    std::unordered_map<std::string, std::weak_ptr<Element>> elementMap_; // Map to hold UI elements by name for quick access
    std::string name;                                                    // Name of the scene
  public:
    Scene(std::string name, std::string rootName);
    Scene(std::string name) : Scene(name, "root") {}
    ~Scene() = default;

    std::weak_ptr<Element> GetRootElement();
    std::unordered_map<std::string, std::weak_ptr<Element>> &GetElementsMap();
    void SetName(const std::string &name);
    std::string GetName() const;
  };
}

#endif
