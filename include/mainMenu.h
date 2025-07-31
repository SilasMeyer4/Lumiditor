
#include "scene.h"

class MainMenu : public LumidiGui::Scene
{
public:
  MainMenu(std::string name, std::string rootName) : Scene(name, rootName) {}
  MainMenu(std::string name) : Scene(name, "root") {}
  ~MainMenu() = default;
};
