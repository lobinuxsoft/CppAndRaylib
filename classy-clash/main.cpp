#include "raylib.h"
#include "raymath.h"

int main()
{
    const int windowWith{384};
    const int windowHeight{384};

    InitWindow(windowWith, windowHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    float speed{4.0};

    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = knight_idle;

    Vector2 knightPos{
        windowWith / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
        (float)windowHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)};
    float rightLeft{1.f};

    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrame{6};
    const float updateTime{1.f / (maxFrame * 2.f)};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        Vector2 direction{};

        if (IsKeyDown(KEY_A))
            direction.x -= 1.0;
        if (IsKeyDown(KEY_D))
            direction.x += 1.0;
        if (IsKeyDown(KEY_W))
            direction.y -= 1.0;
        if (IsKeyDown(KEY_S))
            direction.y += 1.0;

        if (Vector2Length(direction) != 0.0)
        {
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));

            rightLeft = direction.x < 0.f ? -1.f : 1.f;
        }

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // Update animation frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = runningTime - updateTime;
            if (frame > maxFrame)
                frame = 0;
        }

        knight = Vector2Length(direction) > 0.f ? knight_run : knight_idle;

        Rectangle source{frame * (float)knight.width / 6, 0.f, rightLeft * (float)knight.width / 6, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};

        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
    UnloadTexture(knight_idle);
    UnloadTexture(knight_run);
    UnloadTexture(knight);
    CloseWindow();
}