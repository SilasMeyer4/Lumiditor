#include "dragBehavior.h"
#include "operatorOverloads.h"

void LumidiGui::Events::DragBehavior::Update(InputManager &inputManager)
{
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
  {
    Vector2 mousePosition = inputManager.GetMouseInput().position;

    if (!isDragging_)
    {
      if (auto p = parent_.lock(); p && p->ContainsPoint(colliderLabel_, mousePosition))
      {

        isDragging_ = true;
      }
    }
    else
    {
      Vector2 offset = GetMouseDelta();

      if (auto p = parent_.lock())
      {
        p->SetPosition(p->GetAbsolutePosition() + Vector3{offset.x, offset.y, 0});
        // TODO change form default to registered label
        p->GetCollider(colliderLabel_)->position += Vector3{offset.x, offset.y, 0};
      }
    }
  }
  else
  {
    isDragging_ = false;
  }
}
