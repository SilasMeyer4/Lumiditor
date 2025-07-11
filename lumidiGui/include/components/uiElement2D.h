#ifndef LUMIDITOR_UIELEMENT2D_H
#define LUMIDITOR_UIELEMENT2D_H

#include "raylib.h"
#include "uiCollider.h"
#include "uiBehavior.h"
#include "concepts.h"
#include "inputManager.h"
#include <functional>
#include <memory>
#include <string>

namespace LumidiGui
{

  class UIElement2D : public std::enable_shared_from_this<UIElement2D>
  {
  private:
    std::shared_ptr<UICollider2D> collider_;                     // collider UI elements
    std::vector<std::shared_ptr<Events::UIBehavior>> behaviors_; // behaviors for UI elements
    std::vector<std::shared_ptr<UIElement2D>> children_;         // Children UI elements

  protected:
    void DrawChildren() const;

  public:
    UIElement2D(std::string name, Vector2 position, Vector2 size);
    ~UIElement2D() = default;

    virtual void Draw() const; // Function to draw the UI element, can be overriden in derived classes
    std::weak_ptr<UIElement2D> parent;
    virtual void Update(InputManager &inputManager); // Function to update the UI element, can be overridden in derived classes
    virtual void Render();

    template <DerivedFromUICollider2D Collider2DType, typename... Args>
    void SetCollider(Args &&...args)
    {
      if constexpr (sizeof...(Args) == 0)
      {
        collider_ = std::make_shared<Collider2DType>(this->position, this->size);
      }
      else
      {
        collider_ = std::make_shared<Collider2DType>(std::forward<Args>(args)...);
      }
    }

    std::shared_ptr<UICollider2D> GetCollider() const;

    template <DerivedFromUIBehavior BehaviorType, typename... Args>
    void AddBehavior(Args &&...args)
    {
      behaviors_.push_back(std::make_unique<BehaviorType>(weak_from_this(), std::forward<Args>(args)...));
    }

    bool ContainsPoint(Vector2 point) const;

    std::shared_ptr<UIElement2D> GetSharedPtr();
    std::vector<std::shared_ptr<UIElement2D>> GetChildren() const;
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

    bool RemoveChild(std::shared_ptr<UIElement2D> child);
    bool RemoveChild(const std::string &name);

    template <StringLikeOrSharedPointerType... Children>
    bool RemoveChildren(Children &&...children)
    {
      return (RemoveChild(std::forward<Children>(children)) && ...);
    }

    bool AddChild(std::shared_ptr<UIElement2D> child);

    template <SharedPointerType... Children>
    bool AddChildren(Children &&...children)
    {
      return (AddChild(std::forward<Children>(children)) && ...);
    }

    std::shared_ptr<UIElement2D> GetChildByName(const std::string &name) const;

    void ClearAllChildren();

    Vector2 position;      // Position of the UI element
    Vector2 size;          // Size of the UI element
    bool isVisible = true; // Visibility of the UI element
    bool isEnabled = true; // Enabled state of the UI element
    int zIndex = 0;        // Z-index for rendering order
    std::string name;
  };
}

#endif // LUMIDITOR_UIELEMENT2D_H