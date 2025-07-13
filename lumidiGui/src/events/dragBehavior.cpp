#include "dragBehavior.h"
#include "operatorOverloads.h"

void LumidiGui::Events::DragBehavior::Update(InputManager &inputManager)
{
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
  {
    Vector2 mousePosition = inputManager.GetMouseInput().position;

    if (!isDragging_)
    {
      if (auto p = parent_.lock(); p && p->ContainsPoint(mousePosition))
      {

        isDragging_ = true;
      }
    }
    else
    {
      Vector2 offset = GetMouseDelta();

      if (auto p = parent_.lock())
      {
        p->position += offset;
        p->GetCollider()->position += offset;
      }
    }
  }
  else
  {
    isDragging_ = false;
  }
}
