#include <string>
#include "raylib.h"
#include "../../../externalWindowLauncher/launcher.h"

namespace LumidiGui
{
  class Window
  {
  };

  int CreateExternalWindow(const std::string &title, int width, int height, Vector2 position)
  {
    return LumidiGui::External::CreateExternalWindow(title, width, height, position.x, position.y);
  }
}