#ifndef LUMIDITOR_CHECKBOX_H
#define LUMIDITOR_CHECKBOX_H

#include "raylib.h"
#include "uiElement2D.h"
#include "concepts.h"
#include "rectangle.h"
#include "uiEvents.h"
#include "uiColliders.h"
#include <memory>
#include <iostream>

namespace LumidiGui
{
  class Checkbox : public UIElement2D
  {
  private:
    // TODO
    std::unique_ptr<LumidiGui::Rectangle> rectangle_;

  public:
    Checkbox(std::string name, Vector2 position, Vector2 size)
        : UIElement2D(name, position, size)
    {
      this->SetCollider<LumidiGui::RectangleCollider>();
      SetBox<LumidiGui::Rectangle>("checkbox", position, size, GRAY, Border{.isRounded = false, .width = 2.0f, .roundness = 0.0f, .segments = 0, .color = BLACK});
      std::cout << "Created Checkbox" << std::endl;
    }

    Checkbox(std::string name, Vector2 position, Vector2 size, bool isChecked)
        : Checkbox(name, position, size)
    {
      this->isChecked = isChecked;
    }

    ~Checkbox() = default;

    void Draw() const override;

    bool isChecked = false;

    template <RectangleType T, typename... Args>
    void SetBox(Args &&...args)
    {
      rectangle_ = std::make_unique<T>(std::forward<Args>(args)...);
    }

    Color backgroundColor = GRAY;
  };
}

#endif // LUMIDITOR_CHECKBOX_H