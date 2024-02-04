#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    // 1 facing right, -1 facing left
    float rightLeft{1.f};

    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrame{6};
    const float updateTime{1.f / (maxFrame * 2.f)};
    const float speed{4.f};
};

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
                 (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)};
}

void Character::tick(float deltaTime)
{
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
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));

        rightLeft = direction.x < 0.f ? -1.f : 1.f;
    }

    texture = Vector2Length(direction) > 0.f ? run : idle;

    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = runningTime - updateTime;
        if (frame > maxFrame)
            frame = 0;
    }

    Rectangle source{frame * (float)texture.width / 6, 0.f, rightLeft * (float)texture.width / 6, (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.0f, 4.0f * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

int main()
{
    const int windowWith{384};
    const int windowHeight{384};

    InitWindow(windowWith, windowHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    Character knight{};
    knight.setScreenPos(windowWith, windowHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
        knight.tick(GetFrameTime());

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}