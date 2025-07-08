#include <iostream>
#include <raylib.h>
#include "uiComponents.h"
#include "uiEvents.h"
#include "uiColliders.h"

int main(int, char **)
{
    InitWindow(800, 600, "Lumiditor Level Editor");
    SetTargetFPS(60);

    auto button = std::make_shared<LumidiGui::Button>("Button2", Vector2{350, 300}, Vector2{100, 50}, "Click Me");
    LumidiGui::UIManager uiManager;

    auto buttonCrreate = LumidiGui::UIElement2D::Create<LumidiGui::Button>("Button1", Vector2{350, 400}, Vector2{100, 50}, "Click Me");

    button->AddBehavior<LumidiGui::Events::ClickBehavior>(
        button, [button]()
        { std::cout << "Button clicked!" << std::endl; });

    auto button1 = std::make_shared<LumidiGui::Button>("Button2", Vector2{350, 400}, Vector2{100, 50}, "Click Me Too");

    uiManager.AddElements(button, buttonCrreate);

    auto hallo = 4;
    uiManager.RemoveElements("su");

    while (!WindowShouldClose())
    {

        uiManager.Update(GetMousePosition(), IsMouseButtonPressed(MOUSE_LEFT_BUTTON));

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Welcome to Lumiditor, a Raylib based Level Editor", 190, 200, 20, DARKGRAY);
        DrawFPS(10, 10);

        uiManager.Draw();

        EndDrawing();
    }
}
