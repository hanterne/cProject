#include <stdio.h>
#include <easyx.h>


int main(void)
{
	//1,��ʼ������
	InitWindow(640, 480, u8"ɭ�ֱ�����");

	//֡�� 60
	SetTargetFPS(120);

	//����ͼƬ
	Texture2D bgTex = LoadTexture("Resource/��Ϸ�ؿ�1.png");
	if (!IsTextureValid(bgTex)) {
		printf("ͼƬ����ʧ��\n");
	}

	int cnt = 0;
	//2,��Ϸ��ѭ�������̡���ꡢ�ֱ�...)
	while (!WindowShouldClose())
	{
		cnt++;
		printf("%d\n", cnt);
		BeginDrawing();           //��ʼ����
		ClearBackground(WHITE);   //����
		printf("fps:%d\n", GetFPS()); //����֡��
		EndDrawing();             //��������
	}
}