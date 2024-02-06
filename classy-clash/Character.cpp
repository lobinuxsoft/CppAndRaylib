#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    texture = LoadTexture("characters/knight_idle_spritesheet.png");
    idle = LoadTexture("characters/knight_idle_spritesheet.png");
    run = LoadTexture("characters/knight_run_spritesheet.png");

    width = texture.width / maxFrames;
    height = texture.height;
    screenPos = {static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
                 static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);
    
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
}
