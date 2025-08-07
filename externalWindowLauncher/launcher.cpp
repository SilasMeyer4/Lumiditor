#include "launcher.h"
#include <cstdlib>
#include <string>

namespace LumidiGui::External
{
  int CreateExternalWindow(const std::string &title, int width, int height, int x, int y)
  {
    std::string cmd = "lumidiWindows --title=\"" + title + "\" --type=\"dialog\" --width=" + std::to_string(width) +
                      " --height=" + std::to_string(height) + " --x=" + std::to_string(x) +
                      " --y=" + std::to_string(y);
    return std::system(cmd.c_str());
  }
}
