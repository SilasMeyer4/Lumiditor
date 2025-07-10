#include <iostream>
#include <raylib.h>
#include "uiComponents.h"
#include "uiEvents.h"
#include "uiColliders.h"

int main(int, char **)
{
    InitWindow(800, 600, "Lumiditor Level Editor");
    SetTargetFPS(60);

    LumidiGui::UIManager uiManager;
    uiManager.Create<LumidiGui::Button>("su", Vector2{350, 400}, Vector2{100, 50}, "Click Me");
    uiManager.GetElementByName("su").lock()->AddBehavior<LumidiGui::Events::ClickBehavior>(
        []()
        { std::cout << "Button clicked!" << std::endl; });

    uiManager.CreateChild<LumidiGui::Button>("siii", "su", Vector2{350, 300}, Vector2{100, 50}, "Child Button siii");

    uiManager.CreateChild<LumidiGui::Button>("slll", "su", Vector2{350, 200}, Vector2{100, 50}, "Child Button seee");

    uiManager.GetElementByName("siii").lock()->AddBehavior<LumidiGui::Events::ClickBehavior>(
        []()
        { std::cout << "Button clicked wiwuw!" << std::endl; });

    uiManager.MoveChildToParent("siii", "slll");

    uiManager.RemoveElement("siii");

    while (!WindowShouldClose())
    {
        uiManager.Update(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON));

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawFPS(10, 10);

        uiManager.Draw();

        EndDrawing();
    }
}
