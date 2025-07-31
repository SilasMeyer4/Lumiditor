#ifndef LUMIDIGUI_XMLSERIALIZER_H
#define LUMIDIGUI_XMLSERIALIZER_H

#include "serializer.h"
#include "element.h"
#include "scene.h"
#include "pugixml.hpp"
#include "collider.h"

#define USE_XML_SERIALIZER (std::make_unique<LumidiGui::Data::XmlSerializer>())

namespace LumidiGui::Data
{
  class XmlSerializer : public Serializer
  {
  private:
    void SerializeElement(pugi::xml_node &parentNode, const std::shared_ptr<LumidiGui::Element> &element) const;
    void SerializeBehavior(pugi::xml_node &parentNode, const std::shared_ptr<Events::UIBehavior> &behavior) const;
    void SerializeCollider(pugi::xml_node &parentNode, const std::shared_ptr<Collider> &collider, const std::string &label) const;
    std::string ToString(const Vector3 &vec) const;

  public:
    XmlSerializer() = default;
    void SerializeScene(LumidiGui::Scene &scene) const override;
  };
}

#endif