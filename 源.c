#include <stdio.h>
#include "raylib.h"

// �����ɫ�ṹ��
typedef struct {
    Texture2D* currentTexture;
    Vector2 position;
    Vector2 velocity;
    float speed;
} Player;

// ��ʼ����ɫ
void InitPlayer(Player* player, Texture2D* idleTexture, Vector2 startPos, float speed) {
    player->currentTexture = idleTexture;
    player->position = startPos;
    player->velocity = (Vector2){ 0, 0 };
    player->speed = speed;
}

// ���½�ɫ
void UpdatePlayer(Player* player, Texture2D* idleTexture, Texture2D* upTexture, Texture2D* downTexture, Texture2D* leftTexture, Texture2D* rightTexture) {
    player->velocity = (Vector2){ 0, 0 };

    // �жϰ���
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

    // �ǰ�������ԭ
    if (player->velocity.y == 0 && player->velocity.x == 0) {
        player->currentTexture = idleTexture;
    }
}

// ���ƽ�ɫ
void DrawPlayer(Player* player) {
    DrawTextureV(*(player->currentTexture), player->position, WHITE);
}

// �����ͼ
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

// �����ײ
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
    // 1. ��ʼ������
    InitWindow(740, 1100, u8"ɭ�ֱ�����");

    // ֡�� 60
    SetTargetFPS(60);

    // ����ͼƬ
    Texture2D bgTex = LoadTexture("Resource/��Ϸ�ؿ�1.png");
    if (!IsTextureReady(bgTex)) {
        printf("ͼƬ����ʧ��\n");
    }

    Texture2D iceIdel = LoadTexture("Resource/���޾�.png");
    Texture2D iceUp = LoadTexture("Resource/������.png");
    Texture2D iceDown = LoadTexture("Resource/������.png");
    Texture2D iceRight = LoadTexture("Resource/������.png");
    Texture2D iceLeft = LoadTexture("Resource/������.png");
    Texture2D iceTopRight = LoadTexture("Resource/��������.png");
    Texture2D iceTopLeft = LoadTexture("Resource/��������.png");
    Texture2D iceBottomRight = LoadTexture("Resource/��������.png");
    Texture2D iceBottomLeft = LoadTexture("Resource/��������.png");

    Texture2D fireIdel = LoadTexture("Resource/���޾�.png");
    Texture2D fireUp = LoadTexture("Resource/������.png");
    Texture2D fireDown = LoadTexture("Resource/������.png");
    Texture2D fireRight = LoadTexture("Resource/������.png");
    Texture2D fireLeft = LoadTexture("Resource/������.png");
    Texture2D fireTopRight = LoadTexture("Resource/��������.png");
    Texture2D fireTopLeft = LoadTexture("Resource/��������.png");
    Texture2D fireBottomRight = LoadTexture("Resource/��������.png");
    Texture2D fireBottomLeft = LoadTexture("Resource/��������.png");

    // ��ʼ������
    Player icePlayer;
    InitPlayer(&icePlayer, &iceIdel, (Vector2) { 250, 250 }, 5.0f);

    // ��ʼ������
    Player firePlayer;
    InitPlayer(&firePlayer, &fireIdel, (Vector2) { 350, 350 }, 5.0f);

    // 2. ��Ϸ��ѭ��������)
    while (!WindowShouldClose())
    {
        // ���±���
        UpdatePlayer(&icePlayer, &iceIdel, &iceUp, &iceDown, &iceLeft, &iceRight);

        // ���»���
        UpdatePlayer(&firePlayer, &fireIdel, &fireUp, &fireDown, &fireLeft, &fireRight);

        // �򵥵���ײ��⣨��ֹ��ɫ�Ƴ���Ļ��
        if (icePlayer.position.x < 0) icePlayer.position.x = 0;
        if (icePlayer.position.x > GetScreenWidth() - icePlayer.currentTexture->width) icePlayer.position.x = GetScreenWidth() - icePlayer.currentTexture->width;
        if (icePlayer.position.y < 0) icePlayer.position.y = 0;
        if (icePlayer.position.y > GetScreenHeight() - icePlayer.currentTexture->height) icePlayer.position.y = GetScreenHeight() - icePlayer.currentTexture->height;

        if (firePlayer.position.x < 0) firePlayer.position.x = 0;
        if (firePlayer.position.x > GetScreenWidth() - firePlayer.currentTexture->width) firePlayer.position.x = GetScreenWidth() - firePlayer.currentTexture->width;
        if (firePlayer.position.y < 0) firePlayer.position.y = 0;
        if (firePlayer.position.y > GetScreenHeight() - firePlayer.currentTexture->height) firePlayer.position.y = GetScreenHeight() - firePlayer.currentTexture->height;

        // ���ͼ����ײ���
        if (CheckCollision(&icePlayer, map, 32)) {
            icePlayer.position.x -= icePlayer.velocity.x * icePlayer.speed;
            icePlayer.position.y -= icePlayer.velocity.y * icePlayer.speed;
        }

        if (CheckCollision(&firePlayer, map, 32)) {
            firePlayer.position.x -= firePlayer.velocity.x * firePlayer.speed;
            firePlayer.position.y -= firePlayer.velocity.y * firePlayer.speed;
        }

        // ����
        BeginDrawing();           // ��ʼ����
        ClearBackground(WHITE);   // ����

        DrawTexture(bgTex, 0, 0, WHITE); // ���Ʊ���ͼƬ
        DrawFPS(0, 0);

        DrawPlayer(&icePlayer); // ���Ʊ���
        DrawPlayer(&firePlayer); // ���ƻ���

        EndDrawing();             // ��������
    }

    // �رմ���ǰж������
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