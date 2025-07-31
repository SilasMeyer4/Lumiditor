#include "serializer.h"

void LumidiGui::Data::Serializer::SetVersion(int a, int b, int c)
{
  version_ = std::to_string(a) + "." + std::to_string(b) + "." + std::to_string(c);
}

std::string LumidiGui::Data::Serializer::GetVersion()
{
  return version_;
}

void LumidiGui::Data::Serializer::SetFormat(std::string format)
{
  format_ = format;
}

std::string LumidiGui::Data::Serializer::GetFormat()
{
  return format_;
}

void LumidiGui::Data::Serializer::SetFilePath(const std::string &filePath)
{
  filePath_ = filePath;
}

std::string LumidiGui::Data::Serializer::GetFilePath()
{
  return filePath_;
}
