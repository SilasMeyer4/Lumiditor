#ifndef LUMIDITOR_CHECKBOX_H
#define LUMIDITOR_CHECKBOX_H

#include "raylib.h"
#include "element2D.h"
#include "concepts.h"
#include "rectangle.h"
#include "uiEvents.h"
#include "uiColliders.h"
#include <memory>
#include <iostream>

namespace LumidiGui
{
  class Checkbox : public Element2D
  {
  private:
    // TODO
    std::unique_ptr<LumidiGui::Rectangle> rectangle_;

  public:
    Checkbox(std::string name, Vector2 position, Vector2 size)
        : Element2D(name, position, size)
    {
      this->AddCollider<LumidiGui::RectangleCollider>("default");
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