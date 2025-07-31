#include "element.h"
#include "operatorOverloads.h"

namespace LumidiGui
{
  void Element::DrawChildren() const
  {
    for (const auto &child : children_)
    {
      if (child->isVisible_)
      {
        child->Draw();
      }
    }
  }

  Element::Element(std::string name, Vector3 position, Vector3 size) : name_(name), position_(position), size_(size)
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
      if (child->isEnabled_)
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
      if (child->isEnabled_)
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

  Element &Element::RemoveChild(std::shared_ptr<Element> child)
  {
    auto it = std::remove(children_.begin(), children_.end(), child);
    if (it != children_.end())
    {
      children_.erase(it, children_.end());
      child->parent.reset();
      return *this;
    }
    return *this;
  }

  Element &Element::RemoveChild(const std::string &name)
  {
    auto child = GetChildByName(name);
    if (child)
    {
      return RemoveChild(child);
    }
    std::cerr << "[Element-" << this->name_ << "]: Doesn't have a child with the name: " << name << "\n";
    return *this; // Return false if no child with the given name is found
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

  std::unordered_map<std::string, std::shared_ptr<Collider>> &Element::GetColliders()
  {
    return colliders_;
  }

  Element &Element::RenameCollider(const std::string &oldLabel, const std::string &newLabel)
  {
    auto it = colliders_.find(oldLabel);
    if (it == colliders_.end())
      return *this;
    if (colliders_.count(newLabel) > 0)
      return *this;

    auto collider = it->second;
    colliders_.erase(it);
    colliders_[newLabel] = collider;
    return *this;
  }

  void Element::UpdateLayout(int newWindowWidth, int newWindowHeight)
  {

    if (auto parentPtr = parent.lock())
    {
      if (!this->offsetWasCalulcated)
      {
        CalculateOffsets();
        offsetWasCalulcated = true;
      }

      Vector3 parentSize = parentPtr->GetSize();

      // Aktuelle Position und Größe vor Update
      Vector3 newPos = position_;
      Vector3 newSize = size_;

      // Horizontal
      if (anchors.left && anchors.right)
      {
        // Beide Seiten verankert -> Position links fix, Größe anpassen
        newPos.x = offsets.left;
        newSize.x = parentSize.x - offsets.left - offsets.right;
      }
      else if (anchors.left)
      {
        // Nur links verankert -> Position fix, Größe bleibt
        newPos.x = offsets.left;
      }
      else if (anchors.right)
      {
        // Nur rechts verankert -> Position verschieben, Größe bleibt
        newPos.x = parentSize.x - offsets.right - newSize.x;
      }
      // sonst keine horizontale Verankerung -> Position + Größe unverändert

      // Vertikal (analog)
      if (anchors.top && anchors.bottom)
      {
        newPos.y = offsets.top;
        newSize.y = parentSize.y - offsets.top - offsets.bottom;
      }
      else if (anchors.top)
      {
        newPos.y = offsets.top;
      }
      else if (anchors.bottom)
      {
        newPos.y = parentSize.y - offsets.bottom - newSize.y;
      }

      // Z-Koordinate lässt du unverändert, wenn du nur 2D-Layout machen willst
      newPos.z = position_.z;

      // Update der Position und Größe
      SetPosition(newPos);
      SetSize(newSize);
    }
    else
    {
      this->SetPosition(Vector3{0, 0, position_.z});
      this->SetSize(Vector3{(float)newWindowWidth, (float)newWindowHeight, size_.z});
    }
    std::cout << "Element " << this->name_ << " updated with new position: " << this->position_.x << " " << this->position_.y << std::endl;
    // Update auch die Kinder, damit sie neu layouten
    for (auto &child : children_)
    {
      child->UpdateLayout(newWindowWidth, newWindowHeight);
    }
  }
  void Element::CalculateOffsets()
  {
    if (auto parentPtr = parent.lock())
    {
      Vector3 parentSize = parentPtr->GetSize();

      float absPosX = this->GetAbsolutePosition().x;
      float absPosY = this->GetAbsolutePosition().y;
      float parentAbsX = parentPtr->GetAbsolutePosition().x;
      float parentAbsY = parentPtr->GetAbsolutePosition().y;

      offsets.left = absPosX - parentAbsX;
      offsets.right = parentSize.x - offsets.left - GetSize().x;

      offsets.top = absPosY - parentAbsY;
      offsets.bottom = parentSize.y - offsets.top - GetSize().y;
    }
    else
    {
      offsets.left = GetRelativePosition().x;
      offsets.right = 0.f;

      offsets.top = GetRelativePosition().y;
      offsets.bottom = 0.f;
    }
  }

  std::shared_ptr<Element> Element::GetChildByName(const std::string &name) const
  {
    for (const auto &child : children_)
    {
      if (child->name_ == name)
      {
        return child;
      }
    }
    return nullptr; // Return nullptr if no child with the given name is found
  }

  Element &Element::AddChild(std::shared_ptr<Element> child)
  {
    if (!child)
    {
      return *this;
    }

    if (auto existingParent = child->parent.lock())
    {
      if (existingParent.get() == this)
      {
        return *this; // Child already has this element as a parent
      }

      existingParent->RemoveChild(child); // Remove from previous parent
    }

    child->parent = weak_from_this(); // Set this element as the new parent
    children_.push_back(child);
    return *this;
  }
  Element &Element::ClearAllChildren()
  {
    for (auto &child : children_)
    {
      child->parent.reset(); // Clear the parent reference for each child
    }
    children_.clear();
    return *this;
  }
  Element &Element::SetPosition(Vector3 position)
  {
    Vector3 delta = position - position_;
    this->position_ = position;
    for (auto it : colliders_)
    {
      auto collider = it.second;
      collider->position += (delta);
    }
    return *this;
  }
  Element &Element::SetSize(Vector3 size)
  {
    this->size_ = size;
    return *this;
  }

  Element &Element::SetName(const std::string &name)
  {
    this->name_ = name;
    return *this;
  }
  Element &Element::SetEnabled(bool isEnabled)
  {
    this->isEnabled_ = isEnabled;
    return *this;
  }
  Element &Element::SetVisible(bool isVisible)
  {
    this->isVisible_ = isVisible;
    return *this;
  }
  Vector3 Element::GetSize() const
  {
    return this->size_;
  }

  Vector3 Element::GetRelativePosition() const
  {
    return this->position_;
  }

  Vector3 Element::GetAbsolutePosition() const
  {
    Vector3 pos = this->position_;
    std::shared_ptr<Element> currentParent = this->parent.lock();

    while (currentParent)
    {
      pos += currentParent->position_;
      currentParent = currentParent->parent.lock();
    }

    return pos;
  }
  std::string Element::GetName() const
  {
    return this->name_;
  }
  bool Element::IsVisible() const
  {
    return this->isVisible_;
  }
  bool Element::IsEnabled() const
  {
    return this->isEnabled_;
  }
}
