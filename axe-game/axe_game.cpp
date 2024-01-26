#include "raylib.h"

int main()
{
    int width{920};
    int height{640};
    const char *title{"Axe Game"};

    int circle_x{width / 2};
    int circle_y{height / 2};
    float circle_radius{25.0f};
    float circle_speed{10};

    InitWindow(width, height, title);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Game logic begins

        if (IsKeyDown(KEY_D) && (circle_x + circle_radius) < width)
            circle_x += circle_speed;

        if (IsKeyDown(KEY_A) && (circle_x - circle_radius) > 0)
            circle_x -= circle_speed;

        if (IsKeyDown(KEY_W) && (circle_y - circle_radius) > 0)
            circle_y -= circle_speed;

        if (IsKeyDown(KEY_S) && (circle_y + circle_radius) < height)
            circle_y += circle_speed;

        DrawCircle(circle_x, circle_y, circle_radius, BLUE);

        // Game logic ends
        EndDrawing();
    }
}