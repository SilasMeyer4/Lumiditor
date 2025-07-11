#include "inputManager.h"

namespace LumidiGui
{
  int InputManager::exitKey_ = KEY_ESCAPE;
  std::vector<int> InputManager::pressedKeysThisFrame_;
  MouseInput InputManager::mouseInput_;
}