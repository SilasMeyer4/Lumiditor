#include "uiElement2D.h"

namespace LumidiGui
{
  UIElement2D::UIElement2D(Vector2 position, Vector2 size) : position(position), size(size)
  {
  }

  void UIElement2D::Update(Vector2 mousePosition, bool mousePressed)
  {
    for (auto &behavior : behaviors_)
    {
      behavior->Update(mousePosition, mousePressed);
    }
  }

  void UIElement2D::Render()
  {
    for (auto &behavior : behaviors_)
    {
      behavior->Render();
    }
  }
  void UIElement2D::SetCollider(std::shared_ptr<UICollider> collider)
  {
    collider_ = std::move(collider);
  }

  bool UIElement2D::ContainsPoint(Vector2 point) const
  {
    return collider_ ? collider_->Contains(point) : false;
  }

  std::shared_ptr<UICollider> UIElement2D::GetCollider() const
  {
    return collider_;
  }

  std::shared_ptr<UIElement2D> UIElement2D::GetSharedPtr()
  {
    return shared_from_this();
  }

  std::vector<std::shared_ptr<UIElement2D>> UIElement2D::GetChildren() const
  {
    return children_;
  }

  std::vector<std::shared_ptr<Events::UIBehavior>> UIElement2D::GetBehaviors() const
  {
    return behaviors_;
  }
}
