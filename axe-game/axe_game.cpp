#include "raylib.h"

int main()
{
    int width = 920;
    int height = 640;
    const char *title = "Axe Game";

    InitWindow(width, height, title);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircle(width / 2, height / 2, 25.0f, BLUE);
        EndDrawing();
    }
}