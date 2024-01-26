#include "raylib.h"

int main()
{
    int width{920};
    int height{640};
    const char *title{"Axe Game"};

    // Circle variables
    int circle_x{width / 2};
    int circle_y{height / 2};
    float circle_radius{25.0f};
    float circle_speed{10};

    // Axe variables
    int axe_x{400};
    int axe_y{0};

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

        axe_y += 10;

        // Draw on screen
        DrawCircle(circle_x, circle_y, circle_radius, BLUE);

        DrawRectangle(axe_x, axe_y, 50, 50, RED);

        // Game logic ends
        EndDrawing();
    }
}