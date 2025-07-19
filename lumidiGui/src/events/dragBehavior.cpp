#include "dragBehavior.h"
#include "operatorOverloads.h"

void LumidiGui::Events::DragBehavior::Update(InputManager &inputManager)
{
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
  {
    Vector2 mousePosition = inputManager.GetMouseInput().position;

    if (!isDragging_)
    {
      if (auto p = parent_.lock(); p && p->ContainsPoint("default", mousePosition))
      {

        isDragging_ = true;
      }
    }
    else
    {
      Vector2 offset = GetMouseDelta();

      if (auto p = parent_.lock())
      {
        p->position += Vector3{offset.x, offset.y, 0};
        // TODO change form default to registered label
        p->GetCollider("default")->position += Vector3{offset.x, offset.y, 0};
      }
    }
  }
  else
  {
    isDragging_ = false;
  }
}
