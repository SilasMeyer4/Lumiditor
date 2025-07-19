#include "hoverBehavior.h"

void LumidiGui::Events::HoverBehavior::Update(InputManager &inputManager)
{
  Vector2 mousePosition = inputManager.GetMouseInput().position;
  if (auto p = parent_.lock(); p && p->ContainsPoint("default", mousePosition))
  {
    if (!isHovering_)
    {
      isHovering_ = true;
      if (onHoverEnter_)
      {
        onHoverEnter_();
      }
    }
  }
  else
  {
    if (isHovering_)
    {
      isHovering_ = false;
      if (onHoverLeave_)
      {
        onHoverLeave_();
      }
    }
  }
}