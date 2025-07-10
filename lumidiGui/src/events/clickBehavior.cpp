#include "clickBehavior.h"

void LumidiGui::Events::ClickBehavior::Update(Vector2 mousePosition, bool mousePressed)
{
  if (mousePressed)
  {
    if (auto p = parent_.lock(); p && p->ContainsPoint(mousePosition))
    {
      if (onClick_)
      {
        onClick_();
        this->isClicked_ = true;
      }
    }
    else
    {
      this->isClicked_ = false;
    }
  }
}