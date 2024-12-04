#include <stdio.h>
#include "raylib.h"

// �����������ٶ�
#define GRAVITY 0.5f
// ������Ծ�ٶ�
#define JUMP_VELOCITY -10.0f

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

// �����ͼԪ�صı�ʶ��
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

// �����ͼ
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

// ���ص�ͼԪ��
Texture2D mudTex;
Texture2D redDiamondTex;
Texture2D blueDiamondTex;
Texture2D elevatorTex;
Texture2D iceLavaTex;
Texture2D fireLavaTex;
Texture2D exitTex;

// ���ػ���
Texture2D fireDoorTex0;
Texture2D fireDoorTex1;
Texture2D fireDoorTex2;
Texture2D fireDoorTex3;
Texture2D fireDoorTex4;

// ���ر���
Texture2D iceDoorTex0;
Texture2D iceDoorTex1;
Texture2D iceDoorTex2;
Texture2D iceDoorTex3;
Texture2D iceDoorTex4;

// ���Ƶ�ͼԪ��
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
                // ����״̬ѡ�����
                int fireDoorState = 0; //��ʵ�����
                switch (fireDoorState) {
                case 0: DrawTextureV(fireDoorTex0, pos, WHITE); break;
                case 1: DrawTextureV(fireDoorTex1, pos, WHITE); break;
                case 2: DrawTextureV(fireDoorTex2, pos, WHITE); break;
                case 3: DrawTextureV(fireDoorTex3, pos, WHITE); break;
                case 4: DrawTextureV(fireDoorTex4, pos, WHITE); break;
                }
                break;
            case ICE_DOOR:
                // ����״̬ѡ�����
                int iceDoorState = 0; //��ʵ�����
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

// �����ײ
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

    // ���ص�ͼԪ��
    mudTex = LoadTexture("Resource/�ཬ.png");
    redDiamondTex = LoadTexture("Resource/����.png");
    blueDiamondTex = LoadTexture("Resource/����.png");
    elevatorTex = LoadTexture("Resource/����̨.png");
    iceLavaTex = LoadTexture("Resource/����.png");
    fireLavaTex = LoadTexture("Resource/��.png");
    exitTex = LoadTexture("Resource/����.png");

    // ���ػ���
    fireDoorTex0 = LoadTexture("Resource/����0.png");
    fireDoorTex1 = LoadTexture("Resource/����1.png");
    fireDoorTex2 = LoadTexture("Resource/����2.png");
    fireDoorTex3 = LoadTexture("Resource/����3.png");
    fireDoorTex4 = LoadTexture("Resource/����4.png");

    // ���ر���
    iceDoorTex0 = LoadTexture("Resource/����0.png");
    iceDoorTex1 = LoadTexture("Resource/����1.png");
    iceDoorTex2 = LoadTexture("Resource/����2.png");
    iceDoorTex3 = LoadTexture("Resource/����3.png");
    iceDoorTex4 = LoadTexture("Resource/����4.png");

    // ��ʼ������
    Player icePlayer;
    InitPlayer(&icePlayer, &iceIdel, (Vector2) { 350, 350 }, 5.0f);

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
        if (CheckCollision(&icePlayer, map, TILE_SIZE)) {
            icePlayer.position.x -= icePlayer.velocity.x * icePlayer.speed;
            icePlayer.position.y -= icePlayer.velocity.y * icePlayer.speed;
        }

        if (CheckCollision(&firePlayer, map, TILE_SIZE)) {
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

        DrawMapElements(); // ���Ƶ�ͼԪ��

        EndDrawing();             // ��������
    }

    // �رմ���ǰж��ͼƬ
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