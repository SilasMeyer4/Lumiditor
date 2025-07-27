#include "hoverBehavior.h"

void LumidiGui::Events::HoverBehavior::Update(InputManager &inputManager)
{
  Vector2 mousePosition = inputManager.GetMouseInput().position;
  if (auto p = parent_.lock(); p && p->ContainsPoint(colliderLabel_, mousePosition))
  {
    if (!isHovering_)
    {
      isHovering_ = true;
      if (luaOnHoverEnter_.valid())
      {
        luaOnHoverEnter_();
      }
    }
  }
  else
  {
    if (isHovering_)
    {
      isHovering_ = false;
      if (luaOnHoverLeave_.valid())
      {
        luaOnHoverLeave_();
      }
    }
  }
}