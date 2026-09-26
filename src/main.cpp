#include "raylib.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Duel");

    ToggleFullscreen();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Fullscreen", 50, 50, 30, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
}
