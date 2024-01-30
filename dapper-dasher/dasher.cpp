#include "raylib.h"

struct AnimData
{
    Rectangle rect;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rect.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0f;
        data.rect.x = data.frame * data.rect.width;
        data.frame++;
        if(data.frame > maxFrame)
            data.frame = 0;

    }
    
    return data;
}

int main()
{
    // Array with window dimensions
    int windowDimensions[2] = {900, 600};

    const char *windowTitle{"Dapper Dasher!"};

    // Initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], windowTitle);

    // Acceleration due to gravity (pixels/frame)/frame
    const int gravity{1000};

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfNebulae{100};
    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rect = {0.0, 0.0, nebula.width / 8.0f, nebula.height / 8.0f};
        nebulae[i].pos = {(float)windowDimensions[0] + i * 300, (float)windowDimensions[1] - nebulae[i].rect.height};
        nebulae[i].frame = 0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].runningTime = 0;
    }

    int nebVel{-200};

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData{
        {0, 0, scarfy.width / 6, scarfy.height},                                                             // Rectangle
        {windowDimensions[0] / 2 - scarfyData.rect.width / 2, windowDimensions[1] - scarfyData.rect.height}, // Vector2 position
        0,                                                                                                   // Int frame
        1.0 / 12.0,                                                                                          // float update time
        0                                                                                                    // float running time
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

        isInAir = !isOnGround(scarfyData, windowDimensions[1]);

        if (!isInAir)
            velocity = 0;
        else
            velocity += gravity * dT;

        if (!isInAir && IsKeyPressed(KEY_SPACE))
            velocity += jumpVel;

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // Update nebula position
            nebulae[i].pos.x += nebVel * dT;
        }

        // Update scarfy position
        scarfyData.pos.y += velocity * dT;

        // Nebula update animation
        for (int i = 0; i < sizeOfNebulae; i++)
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);

        if(!isInAir)
            scarfyData = updateAnimData(scarfyData, dT, 5);

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // Draw nebula
            DrawTextureRec(nebula, nebulae[i].rect, nebulae[i].pos, WHITE);
        }

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rect, scarfyData.pos, WHITE);

        // End Drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();
}