#ifndef EXTERNAL_WINDOW_LAUNCHER_H
#define EXTERNAL_WINDOW_LAUNCHER_H

#include <string>

namespace LumidiGui::External
{
  int CreateExternalWindow(const std::string &title, int width, int height, int x, int y);
}
#endif // EXTERNAL_WINDOW_LAUNCHER_H