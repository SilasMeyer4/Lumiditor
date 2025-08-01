#ifndef LUMIDIGUI_ELEMENT_H
#define LUMIDIGUI_ELEMENT_H

#include "raylib.h"
#include "collider.h"
#include "uiBehavior.h"
#include "concepts.h"
#include "inputManager.h"
#include "anchors.h"

#include <functional>
#include <memory>
#include <string>

namespace LumidiGui
{

  enum class ElementType
  {
    Base,
    Button,
    Slider,
    Label,
    Checkbox,
    Rectangle,
    Panel,
    Line
  };

  class Element : public std::enable_shared_from_this<Element>
  {
    friend class UIManager;

  private:
    std::unordered_map<std::string, std::shared_ptr<Collider>> colliders_; // collider UI elements
    std::vector<std::shared_ptr<Events::UIBehavior>> behaviors_;           // behaviors for UI elements
    std::vector<std::shared_ptr<Element>> children_;                       // Children UI elements
    Element &SetName(const std::string &name);

  protected:
    void DrawChildren() const;
    Vector3 position_;
    Vector3 size_; // Size of the UI element
    bool isVisible_ = true;
    bool isEnabled_ = true;
    std::string name_;
    bool offsetWasCalulcated = false;

  public:
    Element(std::string name, Vector3 position, Vector3 size);
    ~Element() = default;

    Anchors anchors;
    Offsets offsets;

    virtual void Draw() const; // Function to draw the UI element, can be overriden in derived classes
    std::weak_ptr<Element> parent;
    virtual void Update(InputManager &inputManager); // Function to update the UI element, can be overridden in derived classes
    virtual void Render();
    virtual ElementType GetType() const = 0;

    template <DerivedFromCollider ColliderType, typename... Args>
    void AddCollider(std::string label, Args &&...args)
    {
      if constexpr (sizeof...(Args) == 0)
      {
        colliders_[label] = std::make_shared<ColliderType>(this->position_, this->size_);
      }
      else
      {
        colliders_[label] = std::make_shared<ColliderType>(std::forward<Args>(args)...);
      }
    }

    std::shared_ptr<Collider> GetCollider(const std::string &label) const;
    std::unordered_map<std::string, std::shared_ptr<Collider>> &GetColliders();
    Element &RenameCollider(const std::string &oldLabel, const std::string &newLabel);

    template <DerivedFromUIBehavior BehaviorType, typename... Args>
    Element &AddBehavior(Args &&...args)
    {
      behaviors_.push_back(std::make_shared<BehaviorType>(weak_from_this(), std::forward<Args>(args)...));
      return *this;
    }

    bool ContainsPoint(std::string label, Vector2 point) const;

    std::shared_ptr<Element> GetSharedPtr();
    std::vector<std::shared_ptr<Element>> GetChildren() const;
    std::vector<std::shared_ptr<Events::UIBehavior>> GetBehaviors() const;

    template <DerivedFromUIBehavior BehaviorType>
    std::shared_ptr<BehaviorType> GetBehavior() const
    {
      for (const auto &behavior : behaviors_)
      {
        if (auto specificBehavior = std::dynamic_pointer_cast<BehaviorType>(behavior))
        {
          return specificBehavior;
        }
      }
      return nullptr; // Return nullptr if no behavior of the specified type is found
    }

    Element &RemoveChild(std::shared_ptr<Element> child);
    Element &RemoveChild(const std::string &name);

    template <StringLikeOrSharedPointerType... Children>
    Element &RemoveChildren(Children &&...children)
    {
      return (RemoveChild(std::forward<Children>(children)) && ...);
    }

    Element &AddChild(std::shared_ptr<Element> child);

    template <SharedPointerType... Children>
    Element &AddChildren(Children &&...children)
    {
      return (AddChild(std::forward<Children>(children)) && ...);
    }

    void UpdateLayout(int newWindowWidth, int newWindowHeight);
    void CalculateOffsets();

    std::shared_ptr<Element> GetChildByName(const std::string &name) const;

    Element &ClearAllChildren();

    Element &SetPosition(Vector3 position);
    Element &SetSize(Vector3 size);

    Element &SetEnabled(bool isEnabled);
    Element &SetVisible(bool isVisible);

    Vector3 GetSize() const;
    Vector3 GetRelativePosition() const;
    Vector3 GetAbsolutePosition() const;
    std::string GetName() const;
    bool IsVisible() const;
    bool IsEnabled() const;
  };
}

#endif // LUMIDIGUI_ELEMENT_H