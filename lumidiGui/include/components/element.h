#ifndef LUMIDIGUI_ELEMENT_H
#define LUMIDIGUI_ELEMENT_H

#include "raylib.h"
#include "collider.h"
#include "uiBehavior.h"
#include "concepts.h"
#include "inputManager.h"
#include <functional>
#include <memory>
#include <string>

namespace LumidiGui
{

  class Element : public std::enable_shared_from_this<Element>
  {
  private:
    std::unordered_map<std::string, std::shared_ptr<Collider>> colliders_; // collider UI elements
    std::vector<std::shared_ptr<Events::UIBehavior>> behaviors_;           // behaviors for UI elements
    std::vector<std::shared_ptr<Element>> children_;                       // Children UI elements

  protected:
    void DrawChildren() const;

  public:
    Element(std::string name, Vector3 position, Vector3 size);
    ~Element() = default;

    virtual void Draw() const; // Function to draw the UI element, can be overriden in derived classes
    std::weak_ptr<Element> parent;
    virtual void Update(InputManager &inputManager); // Function to update the UI element, can be overridden in derived classes
    virtual void Render();

    template <DerivedFromCollider ColliderType, typename... Args>
    void AddCollider(std::string label, Args &&...args)
    {
      if constexpr (sizeof...(Args) == 0)
      {
        colliders_[label] = std::make_shared<ColliderType>(this->position, this->size);
      }
      else
      {
        colliders_[label] = std::make_shared<ColliderType>(std::forward<Args>(args)...);
      }
    }

    std::shared_ptr<Collider> GetCollider(const std::string &label) const;
    bool RenameCollider(const std::string &oldLabel, const std::string &newLabel);

    template <DerivedFromUIBehavior BehaviorType, typename... Args>
    void AddBehavior(Args &&...args)
    {
      behaviors_.push_back(std::make_shared<BehaviorType>(weak_from_this(), std::forward<Args>(args)...));
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

    bool RemoveChild(std::shared_ptr<Element> child);
    bool RemoveChild(const std::string &name);

    template <StringLikeOrSharedPointerType... Children>
    bool RemoveChildren(Children &&...children)
    {
      return (RemoveChild(std::forward<Children>(children)) && ...);
    }

    bool AddChild(std::shared_ptr<Element> child);

    template <SharedPointerType... Children>
    bool AddChildren(Children &&...children)
    {
      return (AddChild(std::forward<Children>(children)) && ...);
    }

    std::shared_ptr<Element> GetChildByName(const std::string &name) const;

    void ClearAllChildren();

    Vector3 position;      // Position of the UI element
    Vector3 size;          // Size of the UI element
    bool isVisible = true; // Visibility of the UI element
    bool isEnabled = true; // Enabled state of the UI element
    int zIndex = 0;        // Z-index for rendering order
    std::string name;
  };
}

#endif // LUMIDIGUI_ELEMENT_H