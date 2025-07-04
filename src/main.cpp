#include <iostream>
#include <raylib.h>
#include "button.h"
#include "uiManager.h"

int main(int, char **)
{
    InitWindow(800, 600, "RayLib Level Editor");
    SetTargetFPS(60);
    auto button = std::make_shared<Lumiditor::Button>(Vector2{350, 300}, Vector2{100, 50}, "Click Me");
    Lumiditor::UIManager uiManager;
    button->onClick = [](MouseButton button)
    {
        std::cout << "Button wurde geklickt!" << button << std::endl;
    };

    uiManager.AddElement(button);

    while (!WindowShouldClose())
    {

        uiManager.Update();
        Vector2 mousePosition = GetMousePosition();
        uiManager.OnMouseMove(mousePosition);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            uiManager.OnMouseDown(MOUSE_LEFT_BUTTON);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Welcome to RayLib Level Editor!", 190, 200, 20, DARKGRAY);
        DrawFPS(10, 10);

        uiManager.Draw();

        EndDrawing();
    }

    std::cout << "Hello, from RayLibLevelEditor!\n";
}
