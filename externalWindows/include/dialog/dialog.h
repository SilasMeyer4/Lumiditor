#ifndef LUMIDIGUI_DIALOG_H
#define LUMIDIGUI_DIALOG_H

#include <string>
#include "raylib.h"
#include "uiManager.h"
#include "button.h"

namespace LumidiGui
{
  class Dialog
  {
  public:
    virtual ~Dialog() = default;
    virtual void Show() = 0;
    virtual void Hide() = 0;
  };

  int CreateDialogWindow(const std::string &label, const std::string &type)
  {
    int returnVal = 0;
    InitWindow(800, 600, label.c_str());
    SetTargetFPS(60);

    LumidiGui::UIManager uiManager;
    uiManager.CreateSceneAndSetAsActive<LumidiGui::Scene>("DialogScene");
    uiManager.CreateChild<LumidiGui::Button>("DialogLabel", "root", Vector2{100, 100}, Vector2{50, 50}, "Ok");
    uiManager.GetElementByName("DialogLabel").lock()->AddCollider<LumidiGui::RectangleCollider>("default");

    uiManager.GetElementByName("DialogLabel").lock()->AddBehavior<LumidiGui::Events::HoverBehavior>("default", [&]()
                                                                                                    { uiManager.GetElementByNameAs<LumidiGui::Button>("DialogLabel").lock()->backgroundColor = GREEN; }, [&]()
                                                                                                    { uiManager.GetElementByNameAs<LumidiGui::Button>("DialogLabel").lock()->backgroundColor = DARKGRAY; });

    uiManager.GetElementByNameAs<LumidiGui::Button>("DialogLabel").lock()->AddBehavior<LumidiGui::Events::ClickBehavior>([&]()
                                                                                                                         {
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      {
        // Handle button click
        returnVal = 1;
        CloseWindow();
      } });

    while (!WindowShouldClose())
    {

      LumidiGui::InputManager::GetInstance().HandleInput();
      uiManager.Update(LumidiGui::InputManager::GetInstance());
      BeginDrawing();
      ClearBackground(RAYWHITE);
      uiManager.Draw();
      EndDrawing();
    }

    return returnVal;
  }

}

#endif // LUMIDIGUI_DIALOG_H