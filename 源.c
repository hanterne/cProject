#include <stdio.h>
#include "raylib.h"

// 定义角色结构体
typedef struct {
    Texture2D* currentTexture;
    Vector2 position;
    Vector2 velocity;
    float speed;
} Player;

// 初始化角色
void InitPlayer(Player* player, Texture2D* idleTexture, Vector2 startPos, float speed) {
    player->currentTexture = idleTexture;
    player->position = startPos;
    player->velocity = (Vector2){ 0, 0 };
    player->speed = speed;
}

// 更新角色
void UpdatePlayer(Player* player, Texture2D* idleTexture, Texture2D* upTexture, Texture2D* downTexture, Texture2D* leftTexture, Texture2D* rightTexture) {
    player->velocity = (Vector2){ 0, 0 };

    // 判断按键
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        player->velocity.y = -1;
        player->currentTexture = upTexture;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        player->velocity.y = 1;
        player->currentTexture = downTexture;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        player->velocity.x = -1;
        player->currentTexture = leftTexture;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        player->velocity.x = 1;
        player->currentTexture = rightTexture;
    }

    // 非按键，还原
    if (player->velocity.y == 0 && player->velocity.x == 0) {
        player->currentTexture = idleTexture;
    }
}

// 绘制角色
void DrawPlayer(Player* player) {
    DrawTextureV(*(player->currentTexture), player->position, WHITE);
}

// 定义地图
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// 检查碰撞
bool CheckCollision(Player* player, int map[MAP_HEIGHT][MAP_WIDTH], int tileSize) {
    int playerX = player->position.x / tileSize;
    int playerY = player->position.y / tileSize;

    if (map[playerY][playerX] == 1) {
        return true;
    }

    return false;
}

int main(void)
{
    // 1. 初始化窗口
    InitWindow(740, 1100, u8"森林冰火人");

    // 帧率 60
    SetTargetFPS(60);

    // 加载图片
    Texture2D bgTex = LoadTexture("Resource/游戏关卡1.png");
    if (!IsTextureReady(bgTex)) {
        printf("图片加载失败\n");
    }

    Texture2D iceIdel = LoadTexture("Resource/冰娃静.png");
    Texture2D iceUp = LoadTexture("Resource/冰娃上.png");
    Texture2D iceDown = LoadTexture("Resource/冰娃下.png");
    Texture2D iceRight = LoadTexture("Resource/冰娃右.png");
    Texture2D iceLeft = LoadTexture("Resource/冰娃左.png");
    Texture2D iceTopRight = LoadTexture("Resource/冰娃右上.png");
    Texture2D iceTopLeft = LoadTexture("Resource/冰娃右下.png");
    Texture2D iceBottomRight = LoadTexture("Resource/冰娃左上.png");
    Texture2D iceBottomLeft = LoadTexture("Resource/冰娃左下.png");

    Texture2D fireIdel = LoadTexture("Resource/火娃静.png");
    Texture2D fireUp = LoadTexture("Resource/火娃上.png");
    Texture2D fireDown = LoadTexture("Resource/火娃下.png");
    Texture2D fireRight = LoadTexture("Resource/火娃右.png");
    Texture2D fireLeft = LoadTexture("Resource/火娃左.png");
    Texture2D fireTopRight = LoadTexture("Resource/火娃右上.png");
    Texture2D fireTopLeft = LoadTexture("Resource/火娃右下.png");
    Texture2D fireBottomRight = LoadTexture("Resource/火娃左上.png");
    Texture2D fireBottomLeft = LoadTexture("Resource/火娃左下.png");

    // 初始化冰娃
    Player icePlayer;
    InitPlayer(&icePlayer, &iceIdel, (Vector2) { 250, 250 }, 5.0f);

    // 初始化火娃
    Player firePlayer;
    InitPlayer(&firePlayer, &fireIdel, (Vector2) { 350, 350 }, 5.0f);

    // 2. 游戏主循环（键盘)
    while (!WindowShouldClose())
    {
        // 更新冰娃
        UpdatePlayer(&icePlayer, &iceIdel, &iceUp, &iceDown, &iceLeft, &iceRight);

        // 更新火娃
        UpdatePlayer(&firePlayer, &fireIdel, &fireUp, &fireDown, &fireLeft, &fireRight);

        // 简单的碰撞检测（防止角色移出屏幕）
        if (icePlayer.position.x < 0) icePlayer.position.x = 0;
        if (icePlayer.position.x > GetScreenWidth() - icePlayer.currentTexture->width) icePlayer.position.x = GetScreenWidth() - icePlayer.currentTexture->width;
        if (icePlayer.position.y < 0) icePlayer.position.y = 0;
        if (icePlayer.position.y > GetScreenHeight() - icePlayer.currentTexture->height) icePlayer.position.y = GetScreenHeight() - icePlayer.currentTexture->height;

        if (firePlayer.position.x < 0) firePlayer.position.x = 0;
        if (firePlayer.position.x > GetScreenWidth() - firePlayer.currentTexture->width) firePlayer.position.x = GetScreenWidth() - firePlayer.currentTexture->width;
        if (firePlayer.position.y < 0) firePlayer.position.y = 0;
        if (firePlayer.position.y > GetScreenHeight() - firePlayer.currentTexture->height) firePlayer.position.y = GetScreenHeight() - firePlayer.currentTexture->height;

        // 与地图的碰撞检测
        if (CheckCollision(&icePlayer, map, 32)) {
            icePlayer.position.x -= icePlayer.velocity.x * icePlayer.speed;
            icePlayer.position.y -= icePlayer.velocity.y * icePlayer.speed;
        }

        if (CheckCollision(&firePlayer, map, 32)) {
            firePlayer.position.x -= firePlayer.velocity.x * firePlayer.speed;
            firePlayer.position.y -= firePlayer.velocity.y * firePlayer.speed;
        }

        // 绘制
        BeginDrawing();           // 开始绘制
        ClearBackground(WHITE);   // 清屏

        DrawTexture(bgTex, 0, 0, WHITE); // 绘制背景图片
        DrawFPS(0, 0);

        DrawPlayer(&icePlayer); // 绘制冰娃
        DrawPlayer(&firePlayer); // 绘制火娃

        EndDrawing();             // 结束绘制
    }

    // 关闭窗口前卸载纹理
    UnloadTexture(bgTex);
    UnloadTexture(iceIdel);
    UnloadTexture(iceUp);
    UnloadTexture(iceDown);
    UnloadTexture(iceRight);
    UnloadTexture(iceLeft);
    UnloadTexture(iceTopRight);
    UnloadTexture(iceTopLeft);
    UnloadTexture(iceBottomRight);
    UnloadTexture(iceBottomLeft);

    UnloadTexture(fireIdel);
    UnloadTexture(fireUp);
    UnloadTexture(fireDown);
    UnloadTexture(fireRight);
    UnloadTexture(fireLeft);
    UnloadTexture(fireTopRight);
    UnloadTexture(fireTopLeft);
    UnloadTexture(fireBottomRight);
    UnloadTexture(fireBottomLeft);

    CloseWindow();

    return 0;
}