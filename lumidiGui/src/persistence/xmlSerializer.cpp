#include "xmlSerializer.h"
#include <sstream>
#include <filesystem>

void LumidiGui::Data::XmlSerializer::SerializeScene(LumidiGui::Scene &scene) const
{
  auto sceneRoot = scene.GetRootElement().lock();
  if (!sceneRoot)
    throw std::runtime_error("[XmlSerializer]: Scene has no root element");

  pugi::xml_document doc;

  auto decl = doc.append_child(pugi::node_declaration);
  decl.append_attribute("version") = "1.0";
  decl.append_attribute("encoding") = "UTF-8";

  auto versionElem = doc.append_child("Version");
  versionElem.append_child(pugi::node_pcdata).set_value(version_.c_str());

  auto formatElem = doc.append_child("Format");
  formatElem.append_child(pugi::node_pcdata).set_value(format_.c_str());

  auto sceneElem = doc.append_child("Scene");
  sceneElem.append_attribute("name") = scene.GetName().c_str();

  SerializeElement(sceneElem, sceneRoot);

  if (!std::filesystem::exists(filePath_))
  {
    std::filesystem::create_directories(filePath_);
  }

  if (!doc.save_file((filePath_ + "/" + scene.GetName() + ".xml").c_str(), "    ", pugi::format_indent))
  {
    throw std::runtime_error("[XmlSerializer]: Failed to save file " + filePath_ + "/" + scene.GetName() + ".xml");
  }
}

void LumidiGui::Data::XmlSerializer::SerializeElement(pugi::xml_node &parentNode, const std::shared_ptr<LumidiGui::Element> &element) const
{
  auto elem = parentNode.append_child("Element");
  elem.append_attribute("name") = element->GetName().c_str();
  elem.append_attribute("size") = ToString(element->GetSize()).c_str();
  elem.append_attribute("position") = ToString(element->GetRelativePosition()).c_str();
  elem.append_attribute("isVisible") = element->IsVisible();
  elem.append_attribute("isEnabled") = element->IsEnabled();
  // ANCHORS
  auto &anchors = element->anchors;
  auto anchorsElem = elem.append_child("Anchors");
  anchorsElem.append_attribute("left") = anchors.left;
  anchorsElem.append_attribute("right") = anchors.right;
  anchorsElem.append_attribute("top") = anchors.top;
  anchorsElem.append_attribute("bottom") = anchors.bottom;

  // COLLIDERS
  {
    auto &elemColliders = element->GetColliders();
    if (!elemColliders.empty())
    {
      auto collidersElem = elem.append_child("Colliders");
      for (const auto &collider : elemColliders)
      {
        SerializeCollider(collidersElem, collider.second, collider.first);
      }
    }
  }

  // BEHAVIORS
  {
    const auto &elemBehaviors = element->GetBehaviors();
    if (!elemBehaviors.empty())
    {
      auto behaviorsElem = elem.append_child("Behaviors");
      for (const auto &behavior : elemBehaviors)
      {
        SerializeBehavior(behaviorsElem, behavior);
      }
    }
  }

  // CHILDREN
  {
    const auto &elemChildren = element->GetChildren();
    if (!elemChildren.empty())
    {
      auto childrenElem = elem.append_child("Children");
      for (const auto &child : elemChildren)
      {
        SerializeElement(childrenElem, child);
      }
    }
  }
}

void LumidiGui::Data::XmlSerializer::SerializeCollider(pugi::xml_node &parentNode, const std::shared_ptr<Collider> &collider, const std::string &label) const
{
  auto colliderElem = parentNode.append_child("Collider");
  colliderElem.append_attribute("type") = "TODO TYPE"; // TODO type
  colliderElem.append_attribute("label") = label.c_str();
  colliderElem.append_attribute("size") = ToString(collider->size).c_str();
  colliderElem.append_attribute("position") = ToString(collider->position).c_str();
}

void LumidiGui::Data::XmlSerializer::SerializeBehavior(pugi::xml_node &parentNode, const std::shared_ptr<Events::UIBehavior> &behavior) const
{
  auto behaviorElem = parentNode.append_child("Behavior");
  behaviorElem.append_attribute("isEnabled") = behavior->isEnabled; // TODO different behaviors
}

std::string LumidiGui::Data::XmlSerializer::ToString(const Vector3 &vec) const
{
  std::ostringstream oss;
  oss << vec.x << ", " << vec.y << ", " << vec.z;
  return oss.str();
}
