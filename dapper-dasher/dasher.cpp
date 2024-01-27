#include "raylib.h"

int main()
{
    // Window dimensions and title
    const int windowWidth{900};
    const int windowHeight{600};
    const char *windowTitle{"Dapper Dasher!"};

    // Initialize the window
    InitWindow(windowWidth, windowHeight, windowTitle);

    // Acceleration due to gravity (pixels/frame)/frame
    const int gravity{1};
    const int jumpVel{22};
    bool isInAir{false};

    // Rectangle dimensions
    const int width{50};
    const int height{80};

    int posY{windowHeight - height};
    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(BLACK);

        isInAir = !(posY >= windowHeight - height);

        if (!isInAir)
            velocity = 0;
        else
            velocity += gravity;

        if (!isInAir && IsKeyPressed(KEY_SPACE))
            velocity -= jumpVel;

        // Update position
        posY += velocity;

        DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

        // End Drawing
        EndDrawing();
    }
    CloseWindow();
}