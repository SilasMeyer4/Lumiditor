#include <iostream>
#include <raylib.h>
#include "uiComponents.h"
#include "uiEvents.h"
#include "uiColliders.h"
#include "inputManager.h"
#include "scene.h"
#include "serializer.h"
#include <memory>
#include "xmlSerializer.h"

int main(int, char **)
{
    InitWindow(800, 600, "Lumiditor Level Editor");
    SetTargetFPS(60);

    LumidiGui::UIManager uiManager;
    const std::string btnLoad = "btnLoad";
    const std::string btnExit = "btnExit";
    const std::string btnOptions = "btnOptions";
    const std::string lblTitle = "lblTitle";

    uiManager.CreateSceneAndSetAsActive<LumidiGui::Scene>("MainMenu");

    // BUTTON

    uiManager.CreateChild<LumidiGui::Label>(lblTitle, "root", Vector2{100, 100}, Vector2{150, 300}, "Lumiditor", 70, BLACK);

    uiManager.CreateChild<LumidiGui::Button>(btnExit, "root", Vector2{350, 500}, Vector2{100, 50}, "Exit");
    uiManager.GetElementByName(btnExit).lock()->AddBehavior<LumidiGui::Events::ClickBehavior>(
        []()
        { CloseWindow(); });

    uiManager.GetElementByName(btnExit).lock()->anchors.right = true;

    uiManager.GetElementByName("btnExit").lock()->AddBehavior<LumidiGui::Events::HoverBehavior>("default", [&]()
                                                                                                { uiManager.GetElementByNameAs<LumidiGui::Button>(btnExit).lock()->backgroundColor = GREEN; }, [&]()
                                                                                                { uiManager.GetElementByNameAs<LumidiGui::Button>(btnExit).lock()->backgroundColor = DARKGRAY; });

    uiManager.CreateChild<LumidiGui::Button>(btnLoad, "root", Vector2{350, 100}, Vector2{100, 50}, "Load");
    uiManager.GetElementByName(btnLoad).lock()->AddBehavior<LumidiGui::Events::ClickBehavior>(
        [&]()
        { uiManager.ChangeWindowSize(1920, 1080); });

    uiManager.GetElementByName(btnLoad).lock()->AddBehavior<LumidiGui::Events::HoverBehavior>("default", [&]()
                                                                                              { uiManager.GetElementByNameAs<LumidiGui::Button>(btnLoad).lock()->backgroundColor = GREEN; }, [&]()
                                                                                              { uiManager.GetElementByNameAs<LumidiGui::Button>(btnLoad).lock()->backgroundColor = DARKGRAY; });

    uiManager.CreateChild<LumidiGui::Button>(btnOptions, "root", Vector2{350, 300}, Vector2{100, 50}, "Options");
    uiManager.GetElementByName(btnOptions).lock()->AddBehavior<LumidiGui::Events::ClickBehavior>([&]()
                                                                                                 { uiManager.SetScene("Options"); });

    uiManager.GetElementByName(btnOptions).lock()->AddBehavior<LumidiGui::Events::HoverBehavior>("default", [&]()
                                                                                                 { uiManager.GetElementByNameAs<LumidiGui::Button>(btnOptions).lock()->backgroundColor = GREEN; }, [&]()
                                                                                                 { uiManager.GetElementByNameAs<LumidiGui::Button>(btnOptions).lock()->backgroundColor = DARKGRAY; });

    uiManager.CreateSceneAndSetAsActive<LumidiGui::Scene>("Options");

    uiManager.CreateChild<LumidiGui::Button>(btnExit, "root", Vector2{350, 400}, Vector2{100, 50}, "Back");

    uiManager.GetElementByName(btnExit).lock()->AddBehavior<LumidiGui::Events::ClickBehavior>([&]()
                                                                                              { uiManager.SetScene("MainMenu"); });

    uiManager.GetElementByName(btnExit).lock()->AddBehavior<LumidiGui::Events::HoverBehavior>("default", [&]()
                                                                                              { uiManager.GetElementByNameAs<LumidiGui::Button>(btnExit).lock()->backgroundColor = GREEN; }, [&]()
                                                                                              { uiManager.GetElementByNameAs<LumidiGui::Button>(btnExit).lock()->backgroundColor = DARKGRAY; });

    uiManager.CreateChild<LumidiGui::Checkbox>("checkbox", "root", Vector2{100, 100}, Vector2{30, 30}, true);
    const std::string lblStatus = "lblStatus";

    uiManager.GetElementByName(btnExit).lock()->anchors.right = true;
    uiManager.GetElementByName(btnExit).lock()->anchors.left = false;

    uiManager.GetElementByName("checkbox").lock()->anchors.right = true;
    uiManager.GetElementByName("checkbox").lock()->anchors.left = false;

    uiManager.CreateChild<LumidiGui::Label>(lblStatus, "root", Vector2{200, 100}, Vector2{100, 50}, "Back", 40, BLACK);
    uiManager.GetElementByName("checkbox").lock()->AddBehavior<LumidiGui::Events::ClickBehavior>([&]()
                                                                                                 { (uiManager.GetElementByNameAs<LumidiGui::Checkbox>("checkbox").lock()->isChecked) ? uiManager.ChangeWindowSize(1920, 1080) : uiManager.ChangeWindowSize(800, 1080); });

    uiManager.InitSerializer<LumidiGui::Data::XmlSerializer>();
    uiManager.SaveActiveScene();
    uiManager.SaveAllScenes();

    while (!WindowShouldClose())
    {
        LumidiGui::InputManager::GetInstance().HandleInput();
        uiManager.Update(LumidiGui::InputManager::GetInstance());

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawFPS(10, 10);

        uiManager.Draw();

        EndDrawing();
    }
}
