#include <stdio.h>
#include "raylib.h"

int main(void)
{
    // 1. 初始化窗口
    InitWindow(3200, 2000, u8"森林冰火人");

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
    Texture2D iceBottomRIght = LoadTexture("Resource/冰娃左上.png");
    Texture2D iceBottomLeft = LoadTexture("Resource/冰娃左下.png");
    Texture2D* iceTex = &iceIdel;

    Vector2 pos = { 250, 250 };   //坐标
    Vector2 vec = { 0, 0 };  //速率

    // 2. 游戏主循环（键盘)
    while (!WindowShouldClose())
    {

        BeginDrawing();           // 开始绘制
        ClearBackground(WHITE);   // 清屏

        
        DrawTexture(bgTex, 0, 0, WHITE); // 绘制图片
        DrawFPS(0, 0);

        DrawTexturev(*iceTex, pos, WHITE);

        EndDrawing();             // 结束绘制

        //更新数据
        //判断按键
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
        //非按键，还原
        if (vec.y == 0 && vec.x == 0)
        {
            iceTex = &iceIdel;
        }
    }

    // 关闭窗口前卸载纹理
    UnloadTexture(bgTex);
    CloseWindow();

    return 0;
}