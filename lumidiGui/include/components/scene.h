#ifndef LUMIDIGUI_SCENE_H
#define LUMIDIGUI_SCENE_H

#include <memory>
#include <map>
#include <vector>
#include <element.h>
#include <string>

namespace LumidiGui
{
  /**
   * @class Scene
   * @brief Represents a UI scene containing elements and their hierarchy.
   *
   * The Scene class manages a collection of UI elements, including a root element and a map for fast lookup by name.
   * It provides methods to access and modify the scene's elements and name.
   */
  class Scene
  {
  private:
    /**
     * @brief The root element of the scene.
     */
    std::shared_ptr<Element> rootElement_;

    /**
     * @brief Map to hold UI elements by name for quick access.
     */
    std::unordered_map<std::string, std::weak_ptr<Element>> elementMap_;

    /**
     * @brief Name of the scene.
     */
    std::string name;

  public:
    /**
     * @brief Constructs a Scene with a given name and root element name.
     * @param name The name of the scene.
     * @param rootName The name of the root element.
     */
    Scene(std::string name, std::string rootName);

    /**
     * @brief Constructs a Scene with a given name and default root element name "root".
     * @param name The name of the scene.
     */
    Scene(std::string name) : Scene(name, "root") {}

    /**
     * @brief Default destructor.
     */
    ~Scene() = default;

    /**
     * @brief Returns the root element of the scene.
     * @return A weak pointer to the root element.
     */
    std::weak_ptr<Element> GetRootElement();

    /**
     * @brief Returns a reference to the element map.
     * @return Reference to the unordered_map of element names to weak pointers.
     */
    std::unordered_map<std::string, std::weak_ptr<Element>> &GetElementsMap();

    /**
     * @brief Sets the name of the scene.
     * @param name The new name for the scene.
     */
    void SetName(const std::string &name);

    /**
     * @brief Gets the name of the scene.
     * @return The name of the scene as a string.
     */
    std::string GetName() const;
  };
}

#endif
