#include <iostream>
#include <raylib.h>
#include "uiComponents.h"
#include "uiEvents.h"
#include "uiColliders.h"
#include "inputManager.h"

int main(int, char **)
{
    InitWindow(800, 600, "Lumiditor Level Editor");
    SetTargetFPS(60);

    LumidiGui::UIManager uiManager;

    // BUTTON
    uiManager.Create<LumidiGui::Button>("test", Vector2{350, 400}, Vector2{100, 50}, "Click Me");
    uiManager.GetElementByName("test").lock()->AddBehavior<LumidiGui::Events::ClickBehavior>(
        []()
        { std::cout << "Button clicked!" << std::endl; });

    uiManager.GetElementByName("test").lock()->AddBehavior<LumidiGui::Events::HoverBehavior>(
        [&]()
        { uiManager.GetElementByNameAs<LumidiGui::Button>("test").lock()->backgroundColor = GREEN; },
        [&]()
        { uiManager.GetElementByNameAs<LumidiGui::Button>("test").lock()->backgroundColor = DARKGRAY; });

    uiManager.GetElementByName("test").lock()->AddBehavior<LumidiGui::Events::DragBehavior>();

    uiManager.Create<LumidiGui::Label>("label", Vector2{500, 500}, Vector2{150, 300}, "Label Wuu", 15, BLACK);

    uiManager.GetElementByName("label").lock()->AddBehavior<LumidiGui::Events::DragBehavior>();

    uiManager.GetElementByName("label").lock()->SetCollider<LumidiGui::RectangleCollider>();

    uiManager.Create<LumidiGui::Rectangle>("rec", Vector2{350, 400}, Vector2{100, 50}, BLACK);

    uiManager.GetElementByName("rec").lock()->SetCollider<LumidiGui::RectangleCollider>();

    uiManager.GetElementByName("rec").lock()->AddBehavior<LumidiGui::Events::DragBehavior>();

    uiManager.Create<LumidiGui::Checkbox>("checkbox", Vector2{100, 100}, Vector2{30, 30}, true);

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
