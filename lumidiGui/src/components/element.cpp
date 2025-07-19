#include "element.h"

namespace LumidiGui
{
  void Element::DrawChildren() const
  {
    for (const auto &child : children_)
    {
      if (child->isVisible)
      {
        child->Draw();
      }
    }
  }

  Element::Element(std::string name, Vector3 position, Vector3 size) : name(name), position(position), size(size)
  {
  }

  void Element::Update(InputManager &inputManager)
  {
    for (auto &behavior : behaviors_)
    {
      if (behavior->isEnabled)
      {
        behavior->Update(inputManager);
      }
    }

    for (auto &child : children_)
    {
      if (child->isEnabled)
      {
        child->Update(inputManager);
      }
    }
  }

  void Element::Render()
  {
    for (auto &behavior : behaviors_)
    {
      if (behavior->isEnabled)
      {
        behavior->Render();
      }
    }

    for (auto &child : children_)
    {
      if (child->isEnabled)
      {
        child->Render();
      }
    }
  }

  // bool Element::ContainsPoint(Vector2 point) const
  // {
  //   return collider_ ? collider_->Contains(point) : false;
  // }

  // std::shared_ptr<UICollider2D> Element::GetCollider() const
  // {
  //   return collider_;
  // }

  bool Element::ContainsPoint(std::string label, Vector2 point) const
  {
    auto collider = colliders_.find(label);
    if (collider != colliders_.end())
    {
      return collider->second->Contains(point);
    }

    return false;
  }

  std::shared_ptr<Element> Element::GetSharedPtr()
  {
    return shared_from_this();
  }

  std::vector<std::shared_ptr<Element>> Element::GetChildren() const
  {
    return children_;
  }

  std::vector<std::shared_ptr<Events::UIBehavior>> Element::GetBehaviors() const
  {
    return behaviors_;
  }

  void Element::Draw() const
  {
    DrawChildren();
  }

  bool Element::RemoveChild(std::shared_ptr<Element> child)
  {
    auto it = std::remove(children_.begin(), children_.end(), child);
    if (it != children_.end())
    {
      children_.erase(it, children_.end());
      child->parent.reset();
      return true;
    }
    return false;
  }

  bool Element::RemoveChild(const std::string &name)
  {
    auto child = GetChildByName(name);
    if (child)
    {
      return RemoveChild(child);
    }
    return false; // Return false if no child with the given name is found
  }

  std::shared_ptr<Collider> Element::GetCollider(const std::string &label) const
  {
    auto it = colliders_.find(label);
    if (it != colliders_.end())
    {
      return it->second;
    }

    return nullptr;
  }

  std::shared_ptr<Element> Element::GetChildByName(const std::string &name) const
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

  bool Element::AddChild(std::shared_ptr<Element> child)
  {
    if (!child)
    {
      return false;
    }

    if (auto existingParent = child->parent.lock())
    {
      if (existingParent.get() == this)
      {
        return false; // Child already has this element as a parent
      }

      existingParent->RemoveChild(child); // Remove from previous parent
    }

    child->parent = weak_from_this(); // Set this element as the new parent
    children_.push_back(child);
    return true;
  }
  void Element::ClearAllChildren()
  {
    for (auto &child : children_)
    {
      child->parent.reset(); // Clear the parent reference for each child
    }
    children_.clear();
  }
}
