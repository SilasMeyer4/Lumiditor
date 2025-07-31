#include "scene.h"
#include "panel.h"
#include "raylib.h"

LumidiGui::Scene::Scene(std::string name, std::string rootName)
{
  this->name = name;
  rootElement_ = std::make_shared<Panel>(rootName, Vector2{0, 0}, Vector2{(float)GetScreenWidth(), (float)GetScreenHeight()});
  elementMap_[rootName] = rootElement_;
}

std::weak_ptr<LumidiGui::Element> LumidiGui::Scene::GetRootElement()
{
  return rootElement_;
}

std::unordered_map<std::string, std::weak_ptr<LumidiGui::Element>> &LumidiGui::Scene::GetElementsMap()
{
  return elementMap_;
}

void LumidiGui::Scene::SetName(const std::string &name)
{
  this->name = name;
}

std::string LumidiGui::Scene::GetName() const
{
  return name;
}
