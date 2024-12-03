#include <stdio.h>
#include "raylib.h"

// �����������ٶ�
#define GRAVITY 0.5f
// ������Ծ�ٶ�
#define JUMP_VELOCITY -10.0f

// ��������͵�ͼԪ�صı�ʶ��
#define TILE_SIZE 32
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

// ��ͼԪ�ر�ʶ��
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
void UpdatePlayer(Player* player, Texture2D* idleTexture, Texture2D* upTexture, Texture2D* downTexture, Texture2D* leftTexture, Texture2D* rightTexture, int upKey, int downKey, int leftKey, int rightKey, int jumpKey) {
    player->velocity = (Vector2){ 0, 0 };

    // �жϰ���
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

    // ������Ծ
    if (IsKeyPressed(jumpKey) && player->velocity.y == 0) {
        player->velocity.y = JUMP_VELOCITY;
    }

    // Ӧ������
    player->velocity.y += GRAVITY;

    // �ǰ�������ԭ
    if (player->velocity.y == 0 && player->velocity.x == 0) {
        player->currentTexture = idleTexture;
    }

    // ����λ��
    player->position.x += player->velocity.x * player->speed;
    player->position.y += player->velocity.y * player->speed;

    // ������Ϣ
    printf("Position: (%f, %f), Velocity: (%f, %f), Speed: %f\n", player->position.x, player->position.y, player->velocity.x, player->velocity.y, player->speed);
}

// ���ƽ�ɫ
void DrawPlayer(Player* player) {
    DrawTextureV(*(player->currentTexture), player->position, WHITE);
}


// �����ͼ
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 2, 3, 4, 0, 5, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 6, 7, 1, 1},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 8, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


// �����ײ
bool CheckCollision(Player* player, int map[MAP_HEIGHT][MAP_WIDTH], int tileSize) {
    int playerX = player->position.x / tileSize;
    int playerY = player->position.y / tileSize;

    if (map[playerY][playerX] == 1) {
        printf("Collision detected at position: (%d, %d)\n", playerX, playerY);
        return true;
    }

    return false;
}

int main(void)
{
    // 1. ��ʼ������
    InitWindow(1100, 740, u8"ɭ�ֱ�����");

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

    // ��������
    Texture2D mudTex = LoadTexture("Resource/�ཬ.png");
    Texture2D redDiamondTex = LoadTexture("Resource/����.png");
    Texture2D blueDiamondTex = LoadTexture("Resource/����.png");
    Texture2D elevatorTex = LoadTexture("Resource/����̨.png");
    Texture2D iceLavaTex = LoadTexture("Resource/����.png");
    Texture2D fireLavaTex = LoadTexture("Resource/��.png");
    Texture2D exitTex = LoadTexture("Resource/����.png");
    Texture2D fireDoorTex = LoadTexture("Resource/����.png");
    Texture2D iceDoorTex = LoadTexture("Resource/����.png");



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
        UpdatePlayer(&icePlayer, &iceIdel, &iceUp, &iceDown, &iceLeft, &iceRight, KEY_W, KEY_S, KEY_A, KEY_D, KEY_SPACE);

        // ���»���
        UpdatePlayer(&firePlayer, &fireIdel, &fireUp, &fireDown, &fireLeft, &fireRight, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_RIGHT_CONTROL);

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