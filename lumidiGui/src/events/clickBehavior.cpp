#include "clickBehavior.h"

void LumidiGui::Events::ClickBehavior::Update(InputManager &inputManager)
{
  if (inputManager.GetMouseInput().leftButtonPressed)
  {
    Vector2 mousePosition = inputManager.GetInstance().GetMouseInput().position;
    if (auto p = parent_.lock(); p && p->ContainsPoint("default", mousePosition))
    {
      if (luaOnClick_.valid())
      {
        luaOnClick_();
        this->isClicked_ = true;
      }
    }
    else
    {
      this->isClicked_ = false;
    }
  }
}