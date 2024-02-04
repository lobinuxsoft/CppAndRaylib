#include "raylib.h"

class Character
{
public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime);
    void undoMovement();

private:
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