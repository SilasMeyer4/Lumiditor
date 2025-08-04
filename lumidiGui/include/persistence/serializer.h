/**
 * @file serializer.h
 * @brief Declaration of the Serializer base class for scene persistence in LumidiGui.
 *
 * This file defines the abstract Serializer class, which provides an interface for serializing and
 * deserializing scenes, as well as managing version, format, and file path information.
 */

#ifndef LUMIDIGUI_SERIALIZER_H
#define LUMIDIGUI_SERIALIZER_H

#include "scene.h"
#include <cassert>
#include <memory>

namespace LumidiGui::Data
{

  /**
   * @class Serializer
   * @brief Abstract base class for scene serialization and persistence.
   *
   * Provides an interface for serializing scenes and managing metadata such as version, format, and file path.
   */
  class Serializer
  {
  private:
    // (No private members)
  protected:
    /** @brief The version string of the serialization format. */
    std::string version_ = "0.1.0";
    /** @brief The format identifier string. */
    std::string format_ = "Lumiditor";
    /** @brief The file path used for saving/loading. */
    std::string filePath_ = "data";

  public:
    /**
     * @brief Default constructor.
     */
    Serializer() = default;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Serializer() = default;

    /**
     * @brief Serializes the given scene.
     * @param scene The scene to serialize.
     */
    virtual void SerializeScene(LumidiGui::Scene &scene) const = 0;

    /**
     * @brief Sets the version string using three integer components.
     * @param a Major version.
     * @param b Minor version.
     * @param c Patch version.
     */
    void SetVersion(int a, int b, int c);

    /**
     * @brief Gets the current version string.
     * @return The version string.
     */
    std::string GetVersion();

    /**
     * @brief Sets the format identifier string.
     * @param format The format string to set.
     */
    void SetFormat(std::string format);

    /**
     * @brief Gets the current format identifier string.
     * @return The format string.
     */
    std::string GetFormat();

    /**
     * @brief Sets the file path for saving/loading.
     * @param filePath The file path to set.
     */
    void SetFilePath(const std::string &filePath);

    /**
     * @brief Gets the current file path.
     * @return The file path string.
     */
    std::string GetFilePath();
  };

}

#endif