#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollisionRect();
    virtual void tick(float deltaTime);

protected:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    // 1 facing right, -1 facing left
    float rightLeft{1.f};

    // animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / (maxFrames * 2.f)};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.f};
};

#endif // BASE_CHARACTER_H