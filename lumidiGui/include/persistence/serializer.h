#ifndef LUMIDIGUI_SERIALIZER_H
#define LUMIDIGUI_SERIALIZER_H

#include "scene.h"
#include <cassert>
#include <memory>

namespace LumidiGui::Data
{

  class Serializer
  {
  private:
  protected:
    std::string version_ = "0.1.0";
    std::string format_ = "Lumiditor";
    std::string filePath_ = "data";

  public:
    Serializer() = default;
    virtual ~Serializer() = default;
    virtual void SerializeScene(LumidiGui::Scene &scene) const = 0;
    void SetVersion(int a, int b, int c);
    std::string GetVersion();
    void SetFormat(std::string format);
    std::string GetFormat();
    void SetFilePath(const std::string &filePath);
    std::string GetFilePath();
  };

}

#endif