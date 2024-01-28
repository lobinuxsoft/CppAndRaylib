#include "raylib.h"

struct AnimData
{
    Rectangle rect;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    // Window dimensions and title
    const int windowWidth{900};
    const int windowHeight{600};
    const char *windowTitle{"Dapper Dasher!"};

    // Initialize the window
    InitWindow(windowWidth, windowHeight, windowTitle);

    // Acceleration due to gravity (pixels/frame)/frame
    const int gravity{1000};

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData nebData{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},   // Rectangle
        {windowWidth, windowHeight - nebData.rect.height}, // Position
        0,                                                 // Frame
        1.0 / 12.0,                                        // Update time
        0                                                  // Running time
    };

    int nebVel{-200};

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData{
        {0, 0, scarfy.width / 6, scarfy.height},                                              // Rectangle
        {windowWidth / 2 - scarfyData.rect.width / 2, windowHeight - scarfyData.rect.height}, // Vector2 position
        0,                                                                                    // Int frame
        1.0 / 12.0,                                                                           // float update time
        0                                                                                     // float running time
    };

    const int jumpVel{-600};
    bool isInAir{false};

    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float dT{GetFrameTime()};

        // Start drawing
        BeginDrawing();
        ClearBackground(BLACK);

        isInAir = !(scarfyData.pos.y >= windowHeight - scarfyData.rect.height);

        if (!isInAir)
            velocity = 0;
        else
            velocity += gravity * dT;

        if (!isInAir && IsKeyPressed(KEY_SPACE))
            velocity += jumpVel;

        // Update nebula position
        nebData.pos.x += nebVel * dT;

        // Update scarfy position
        scarfyData.pos.y += velocity * dT;

        // Nebula update animation
        nebData.runningTime += dT;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0;
            nebData.rect.x = nebData.frame * nebData.rect.width;
            nebData.frame++;

            if (nebData.frame > 7)
                nebData.frame = 0;
        }

        // Scarfy update animation
        scarfyData.runningTime += dT;
        if (!isInAir && scarfyData.runningTime >= scarfyData.updateTime)
        {
            scarfyData.runningTime = 0;
            scarfyData.rect.x = scarfyData.frame * scarfyData.rect.width;
            scarfyData.frame++;

            if (scarfyData.frame > 5)
                scarfyData.frame = 0;
        }

        // Draw nebula
        DrawTextureRec(nebula, nebData.rect, nebData.pos, WHITE);

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rect, scarfyData.pos, WHITE);

        // End Drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();
}