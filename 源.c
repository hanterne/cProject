#include <stdio.h>
#include "raylib.h"

int main(void)
{
    // 1. ��ʼ������
    InitWindow(3200, 2000, u8"ɭ�ֱ�����");

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
    Texture2D iceBottomRIght = LoadTexture("Resource/��������.png");
    Texture2D iceBottomLeft = LoadTexture("Resource/��������.png");
    Texture2D* iceTex = &iceIdel;

    Vector2 pos = { 250, 250 };   //����
    Vector2 vec = { 0, 0 };  //����

    // 2. ��Ϸ��ѭ��������)
    while (!WindowShouldClose())
    {

        BeginDrawing();           // ��ʼ����
        ClearBackground(WHITE);   // ����

        
        DrawTexture(bgTex, 0, 0, WHITE); // ����ͼƬ
        DrawFPS(0, 0);

        DrawTexturev(*iceTex, pos, WHITE);

        EndDrawing();             // ��������

        //��������
        //�жϰ���
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            vec.y = -1;
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            vec.y = 1;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            vec.x = -1;
        }

        //

        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            vec.x = 1;
        }
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            vec.y = -1;
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            vec.y = 1;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            vec.x = -1;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            vec.x = 1;
        }

        pos.x += vec.x;
        pos.y += vec.y;
        //�ǰ�������ԭ
        if (vec.y == 0 && vec.x == 0)
        {
            iceTex = &iceIdel;
        }
    }

    // �رմ���ǰж������
    UnloadTexture(bgTex);
    CloseWindow();

    return 0;
}