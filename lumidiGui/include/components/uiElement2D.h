#ifndef LUMIDITOR_UIELEMENT2D_H
#define LUMIDITOR_UIELEMENT2D_H

#include "raylib.h"
#include "uiCollider.h"
#include "uiBehavior.h"
#include <functional>
#include <memory>

namespace LumidiGui
{
  class UIElement2D : public std::enable_shared_from_this<UIElement2D>
  {
  private:
    std::shared_ptr<UICollider> collider_;                       // collider UI elements
    std::vector<std::shared_ptr<Events::UIBehavior>> behaviors_; // behaviors for UI elements
    std::vector<std::shared_ptr<UIElement2D>> children_;         // Children UI elements
  public:
    UIElement2D() = default;
    UIElement2D(Vector2 position, Vector2 size);
    ~UIElement2D() = default;
    virtual void Draw() const = 0;                                 // Function to draw the UI element, to be implemented in derived classes
    virtual void Update(Vector2 mousePosition, bool mousePressed); // Function to update the UI element, can be overridden in derived classes
    virtual void Render();
    void SetCollider(std::shared_ptr<UICollider> collider);

    template <typename BehaviorType, typename... Args>
    void AddBehavior(Args &&...args)
    {
      behaviors_.push_back(std::make_shared<BehaviorType>(std::forward<Args>(args)...));
    }

    bool ContainsPoint(Vector2 point) const;
    std::shared_ptr<UICollider> GetCollider() const;
    std::shared_ptr<UIElement2D> GetSharedPtr();
    std::vector<std::shared_ptr<UIElement2D>> GetChildren() const;
    std::vector<std::shared_ptr<Events::UIBehavior>> GetBehaviors() const;

    Vector2 position; // Position of the UI element
    Vector2 size;     // Size of the UI element
  };
}

#endif // LUMIDITOR_UIELEMENT2D_H