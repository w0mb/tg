#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Моя игра на Raylib");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Привет, Raylib!", screenWidth/2 - MeasureText("Привет, Raylib!", 20)/2, screenHeight/2 - 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
