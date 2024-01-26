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

    // circle edges
    int l_circle_x{circle_x - circle_radius};
    int r_circle_x{circle_x + circle_radius};
    int u_circle_y{circle_y - circle_radius};
    int b_circle_y{circle_y + circle_radius};

    // Axe variables
    int axe_x{400};
    int axe_y{0};
    int axe_lenght{50};
    int direction{10};

    // axe edges
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + axe_lenght};
    int u_axe_y{axe_y};
    int b_axe_y{axe_x + axe_lenght};

    bool collision_with_axe{true};

    InitWindow(width, height, title);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (collision_with_axe)
        {
            DrawText("Game Over!", 400, 200, 20, RED);
        }
        else
        {
            // Game logic begins

            if (IsKeyDown(KEY_D) && (circle_x + circle_radius) < width)
                circle_x += circle_speed;

            if (IsKeyDown(KEY_A) && (circle_x - circle_radius) > 0)
                circle_x -= circle_speed;

            if (IsKeyDown(KEY_W) && (circle_y - circle_radius) > 0)
                circle_y -= circle_speed;

            if (IsKeyDown(KEY_S) && (circle_y + circle_radius) < height)
                circle_y += circle_speed;

            axe_y += direction;

            if (axe_y > height || axe_y < 0)
                direction = -direction;

            // Draw on screen
            DrawCircle(circle_x, circle_y, circle_radius, BLUE);

            DrawRectangle(axe_x, axe_y, axe_lenght, axe_lenght, RED);
        }

        // Game logic ends
        EndDrawing();
    }
}