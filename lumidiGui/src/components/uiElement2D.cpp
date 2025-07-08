#include "uiElement2D.h"

namespace LumidiGui
{
  UIElement2D::UIElement2D(std::string name, Vector2 position, Vector2 size) : name(name), position(position), size(size)
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

  bool UIElement2D::RemoveChild(std::shared_ptr<UIElement2D> child)
  {
    auto it = std::remove(children_.begin(), children_.end(), child);
    if (it != children_.end())
    {
      children_.erase(it, children_.end());
      return true;
    }
    return false;
  }

  bool UIElement2D::RemoveChild(const std::string &name)
  {
    auto child = GetChildByName(name);
    if (child)
    {
      return RemoveChild(child);
    }
    return false; // Return false if no child with the given name is found
  }

  std::shared_ptr<UIElement2D> UIElement2D::GetChildByName(const std::string &name) const
  {
    for (const auto &child : children_)
    {
      if (child->name == name)
      {
        return child;
      }
    }
    return nullptr; // Return nullptr if no child with the given name is found
  }

  bool UIElement2D::AddChild(std::shared_ptr<UIElement2D> child)
  {
    children_.push_back(child);
    return true;
  }
  void UIElement2D::ClearAllChildren()
  {
    children_.clear();
  }
}
