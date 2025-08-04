/**
 * @file xmlSerializer.h
 * @brief XML-based implementation of the Serializer for LumidiGui scenes.
 *
 * This file defines the XmlSerializer class, which serializes scenes, elements, behaviors, and colliders to XML format.
 */

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
  /**
   * @class XmlSerializer
   * @brief Serializer implementation for saving scenes as XML.
   *
   * Provides methods to serialize scenes, elements, behaviors, and colliders into XML using pugixml.
   */
  class XmlSerializer : public Serializer
  {
  private:
    /**
     * @brief Serializes a UI element and its children to XML.
     * @param parentNode The parent XML node.
     * @param element The element to serialize.
     */
    void SerializeElement(pugi::xml_node &parentNode, const std::shared_ptr<LumidiGui::Element> &element) const;

    /**
     * @brief Serializes a UI behavior to XML.
     * @param parentNode The parent XML node.
     * @param behavior The behavior to serialize.
     */
    void SerializeBehavior(pugi::xml_node &parentNode, const std::shared_ptr<Events::UIBehavior> &behavior) const;

    /**
     * @brief Serializes a collider to XML.
     * @param parentNode The parent XML node.
     * @param collider The collider to serialize.
     * @param label The label for the collider.
     */
    void SerializeCollider(pugi::xml_node &parentNode, const std::shared_ptr<Collider> &collider, const std::string &label) const;

    /**
     * @brief Converts a Vector3 to a string representation.
     * @param vec The vector to convert.
     * @return The string representation of the vector.
     */
    std::string ToString(const Vector3 &vec) const;

  public:
    /**
     * @brief Default constructor.
     */
    XmlSerializer() = default;

    /**
     * @brief Serializes a scene to XML format.
     * @param scene The scene to serialize.
     */
    void SerializeScene(LumidiGui::Scene &scene) const override;
  };
}

#endif