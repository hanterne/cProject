#include <stdio.h>
#include "raylib.h"

// 定义重力加速度
#define GRAVITY 0.5f
// 定义跳跃速度
#define JUMP_VELOCITY -10.0f

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
void UpdatePlayer(Player* player, Texture2D* idleTexture, Texture2D* upTexture, Texture2D* downTexture, Texture2D* leftTexture, Texture2D* rightTexture, int upKey, int downKey, int leftKey, int rightKey, int jumpKey) {
    player->velocity = (Vector2){ 0, 0 };

    // 判断按键
    if (IsKeyDown(upKey)) {
        player->velocity.y = -1;
        player->currentTexture = upTexture;
        printf("Up key pressed\n");
    }
    if (IsKeyDown(downKey)) {
        player->velocity.y = 1;
        player->currentTexture = downTexture;
        printf("Down key pressed\n");
    }
    if (IsKeyDown(leftKey)) {
        player->velocity.x = -1;
        player->currentTexture = leftTexture;
        printf("Left key pressed\n");
    }
    if (IsKeyDown(rightKey)) {
        player->velocity.x = 1;
        player->currentTexture = rightTexture;
        printf("Right key pressed\n");
    }

    // 处理跳跃
    if (IsKeyPressed(jumpKey) && player->velocity.y == 0) {
        player->velocity.y = JUMP_VELOCITY;
    }

    // 应用重力
    player->velocity.y += GRAVITY;

    // 非按键，还原
    if (player->velocity.y == 0 && player->velocity.x == 0) {
        player->currentTexture = idleTexture;
    }

    // 更新位置
    player->position.x += player->velocity.x * player->speed;
    player->position.y += player->velocity.y * player->speed;

    // 调试信息
    printf("Position: (%f, %f), Velocity: (%f, %f), Speed: %f\n", player->position.x, player->position.y, player->velocity.x, player->velocity.y, player->speed);
}

// 绘制角色
void DrawPlayer(Player* player) {
    DrawTextureV(*(player->currentTexture), player->position, WHITE);
}

// 定义地图元素的标识符
#define TILE_SIZE 32
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

// 地图元素标识符
#define EMPTY 0
#define WALL 1
#define MUD 2
#define RED_DIAMOND 3
#define BLUE_DIAMOND 4
#define ELEVATOR 5
#define ICE_LAVA 6
#define FIRE_LAVA 7
#define EXIT 8
#define FIRE_DOOR 9
#define ICE_DOOR 10

// 定义地图
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// 加载地图元素
Texture2D mudTex;
Texture2D redDiamondTex;
Texture2D blueDiamondTex;
Texture2D elevatorTex;
Texture2D iceLavaTex;
Texture2D fireLavaTex;
Texture2D exitTex;

// 加载火门
Texture2D fireDoorTex0;
Texture2D fireDoorTex1;
Texture2D fireDoorTex2;
Texture2D fireDoorTex3;
Texture2D fireDoorTex4;

// 加载冰门
Texture2D iceDoorTex0;
Texture2D iceDoorTex1;
Texture2D iceDoorTex2;
Texture2D iceDoorTex3;
Texture2D iceDoorTex4;

// 绘制地图元素
void DrawMapElements() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Vector2 pos = { (float)(x * TILE_SIZE), (float)(y * TILE_SIZE) };
            switch (map[y][x]) {
            case MUD:
                DrawTextureV(mudTex, pos, WHITE);
                break;
            case RED_DIAMOND:
                DrawTextureV(redDiamondTex, pos, WHITE);
                break;
            case BLUE_DIAMOND:
                DrawTextureV(blueDiamondTex, pos, WHITE);
                break;
            case ELEVATOR:
                DrawTextureV(elevatorTex, pos, WHITE);
                break;
            case ICE_LAVA:
                DrawTextureV(iceLavaTex, pos, WHITE);
                break;
            case FIRE_LAVA:
                DrawTextureV(fireLavaTex, pos, WHITE);
                break;
            case EXIT:
                DrawTextureV(exitTex, pos, WHITE);
                break;
            case FIRE_DOOR:
                // 根据状态选择火门
                int fireDoorState = 0; //看实际情况
                switch (fireDoorState) {
                case 0: DrawTextureV(fireDoorTex0, pos, WHITE); break;
                case 1: DrawTextureV(fireDoorTex1, pos, WHITE); break;
                case 2: DrawTextureV(fireDoorTex2, pos, WHITE); break;
                case 3: DrawTextureV(fireDoorTex3, pos, WHITE); break;
                case 4: DrawTextureV(fireDoorTex4, pos, WHITE); break;
                }
                break;
            case ICE_DOOR:
                // 根据状态选择冰门
                int iceDoorState = 0; //看实际情况
                switch (iceDoorState) {
                case 0: DrawTextureV(iceDoorTex0, pos, WHITE); break;
                case 1: DrawTextureV(iceDoorTex1, pos, WHITE); break;
                case 2: DrawTextureV(iceDoorTex2, pos, WHITE); break;
                case 3: DrawTextureV(iceDoorTex3, pos, WHITE); break;
                case 4: DrawTextureV(iceDoorTex4, pos, WHITE); break;
                }
                break;
            }
        }
    }
}

// 检查碰撞
bool CheckCollision(Player* player, int map[MAP_HEIGHT][MAP_WIDTH], int tileSize) {
    int playerX = (int)(player->position.x / tileSize);
    int playerY = (int)(player->position.y / tileSize);

    if (map[playerY][playerX] == WALL) {
        printf("Collision detected at position: (%d, %d)\n", playerX, playerY);
        return true;
    }

    return false;
}

int main(void)
{
    // 1. 初始化窗口
    InitWindow(1100, 740, u8"森林冰火人");

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

    // 加载地图元素
    mudTex = LoadTexture("Resource/泥浆.png");
    redDiamondTex = LoadTexture("Resource/红钻.png");
    blueDiamondTex = LoadTexture("Resource/蓝钻.png");
    elevatorTex = LoadTexture("Resource/升降台.png");
    iceLavaTex = LoadTexture("Resource/冰浆.png");
    fireLavaTex = LoadTexture("Resource/火浆.png");
    exitTex = LoadTexture("Resource/出口.png");

    // 加载火门
    fireDoorTex0 = LoadTexture("Resource/火门0.png");
    fireDoorTex1 = LoadTexture("Resource/火门1.png");
    fireDoorTex2 = LoadTexture("Resource/火门2.png");
    fireDoorTex3 = LoadTexture("Resource/火门3.png");
    fireDoorTex4 = LoadTexture("Resource/火门4.png");

    // 加载冰门
    iceDoorTex0 = LoadTexture("Resource/冰门0.png");
    iceDoorTex1 = LoadTexture("Resource/冰门1.png");
    iceDoorTex2 = LoadTexture("Resource/冰门2.png");
    iceDoorTex3 = LoadTexture("Resource/冰门3.png");
    iceDoorTex4 = LoadTexture("Resource/冰门4.png");

    // 初始化冰娃
    Player icePlayer;
    InitPlayer(&icePlayer, &iceIdel, (Vector2) { 350, 350 }, 5.0f);

    // 初始化火娃
    Player firePlayer;
    InitPlayer(&firePlayer, &fireIdel, (Vector2) { 350, 350 }, 5.0f);

    // 2. 游戏主循环（键盘)
    while (!WindowShouldClose())
    {
        // 更新冰娃
        UpdatePlayer(&icePlayer, &iceIdel, &iceUp, &iceDown, &iceLeft, &iceRight, KEY_W, KEY_S, KEY_A, KEY_D, KEY_SPACE);

        // 更新火娃
        UpdatePlayer(&firePlayer, &fireIdel, &fireUp, &fireDown, &fireLeft, &fireRight, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_RIGHT_CONTROL);

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
        if (CheckCollision(&icePlayer, map, TILE_SIZE)) {
            icePlayer.position.x -= icePlayer.velocity.x * icePlayer.speed;
            icePlayer.position.y -= icePlayer.velocity.y * icePlayer.speed;
        }

        if (CheckCollision(&firePlayer, map, TILE_SIZE)) {
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

        DrawMapElements(); // 绘制地图元素

        EndDrawing();             // 结束绘制
    }

    // 关闭窗口前卸载图片
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

    UnloadTexture(mudTex);
    UnloadTexture(redDiamondTex);
    UnloadTexture(blueDiamondTex);
    UnloadTexture(elevatorTex);
    UnloadTexture(iceLavaTex);
    UnloadTexture(fireLavaTex);
    UnloadTexture(exitTex);

    UnloadTexture(fireDoorTex0);
    UnloadTexture(fireDoorTex1);
    UnloadTexture(fireDoorTex2);
    UnloadTexture(fireDoorTex3);
    UnloadTexture(fireDoorTex4);

    UnloadTexture(iceDoorTex0);
    UnloadTexture(iceDoorTex1);
    UnloadTexture(iceDoorTex2);
    UnloadTexture(iceDoorTex3);
    UnloadTexture(iceDoorTex4);

    CloseWindow();

    return 0;
}