#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() {}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRect()
{
    return Rectangle{getScreenPos().x, getScreenPos().y, width * scale, height * scale};
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    if (Vector2Length(velocity) != 0.0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        rightLeft = velocity.x < 0.f ? -1.f : 1.f;

        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};


    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = runningTime - updateTime;
        if (frame > maxFrames)
            frame = 0;
    }

    // Draw character
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}
