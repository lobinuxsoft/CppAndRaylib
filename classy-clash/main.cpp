#include "raylib.h"

int main()
{
    const int windowWith{384};
    const int windowHeight{384};

    InitWindow(windowWith, windowHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        Vector2 mapPos{0.0, 0.0};
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}