#ifndef LUMIDITOR_UIELEMENT2D_H
#define LUMIDITOR_UIELEMENT2D_H

#include "raylib.h"
#include "uiCollider.h"
#include "uiBehavior.h"
#include "concepts.h"
#include <functional>
#include <memory>
#include <string>

namespace LumidiGui
{

  class UIElement2D : public std::enable_shared_from_this<UIElement2D>
  {
  private:
    std::shared_ptr<UICollider> collider_;                       // collider UI elements
    std::vector<std::shared_ptr<Events::UIBehavior>> behaviors_; // behaviors for UI elements
    std::vector<std::shared_ptr<UIElement2D>> children_;         // Children UI elements
  public:
    UIElement2D(std::string name, Vector2 position, Vector2 size);
    ~UIElement2D() = default;

    template <DerivedFromUIElement2D T, typename... Args>
    static std::shared_ptr<T> Create(Args &&...args)
    {
      return std::make_shared<T>(std::forward<Args>(args)...);
    }

    virtual void Draw() const = 0;                                 // Function to draw the UI element, to be implemented in derived classes
    virtual void Update(Vector2 mousePosition, bool mousePressed); // Function to update the UI element, can be overridden in derived classes
    virtual void Render();
    void SetCollider(std::shared_ptr<UICollider> collider);

    template <DerivedFromUIBehavior BehaviorType, typename... Args>
    void AddBehavior(Args &&...args)
    {
      behaviors_.push_back(std::make_shared<BehaviorType>(std::forward<Args>(args)...));
    }

    bool ContainsPoint(Vector2 point) const;

    std::shared_ptr<UICollider> GetCollider() const;
    std::shared_ptr<UIElement2D> GetSharedPtr();
    std::vector<std::shared_ptr<UIElement2D>> GetChildren() const;
    std::vector<std::shared_ptr<Events::UIBehavior>> GetBehaviors() const;

    bool RemoveChild(std::shared_ptr<UIElement2D> child);
    bool RemoveChild(const std::string &name);

    template <StringLikeOrSharedPointerType... Children>
    bool RemoveChildren(Children &&...children)
    {
      return (RemoveChild(std::forward<Children>(children)) && ...);
    }

    std::shared_ptr<UIElement2D> GetChildByName(const std::string &name) const;

    bool AddChild(std::shared_ptr<UIElement2D> child);

    template <SharedPointerType... Children>
    bool AddChildren(Children &&...children)
    {
      return (AddChild(std::forward<Children>(children)) && ...);
    }

    void ClearAllChildren();

    std::weak_ptr<UIElement2D> parent;

    Vector2 position;      // Position of the UI element
    Vector2 size;          // Size of the UI element
    bool isVisible = true; // Visibility of the UI element
    bool isEnabled = true; // Enabled state of the UI element
    int zIndex = 0;        // Z-index for rendering order
    std::string name;
  };
}

#endif // LUMIDITOR_UIELEMENT2D_H