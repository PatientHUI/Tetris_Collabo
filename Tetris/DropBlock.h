#include <stdlib.h> //srand, rand�� ����ϱ� ���� �������
#include <time.h> // time�� ����ϱ� ���� �������

int CreateRandomForm() {
	srand(time(NULL));
	int blockform = rand() % 7;
	return blockform;
}

bool CheckCrash(int x, int y) {
	for (int i = 0; i < 4; i++) //���� ��
	{
		for (int j = 0; j < 4; j++) //���� ��
		{
			if (Block[blockform][blockRotation][i][j] == 2) {
				int t = board[i + y][j + x / 2];
				if (t == 1 || t == 2) { // 1=���� ��, 2=���� ��
					return true;//�浹
				}
			}
		}
	}
	return false;
}

void DropBlock()
{
	endT = clock();
	if ((float)(endT - startDropT) >= 700)//0.7�ʵ��� ������ ������ ������
	{
		if (CheckCrash(x, y + 1) == true) return;//���� �浹�ϸ� �Լ� ����
		y++;//�ƴϸ� ��ĭ �Ʒ��� �̵�
		startDropT = clock();//�� �����ð��� ���Ӱ� ����
		system("cls");
	}
}
void BlockToGround() //�浹����
{
	if (CheckCrash(x, y + 1) == true) {
		if ((float)(endT - startGroundT) > 1500)//�浹 �� 1.5�ʰ� ������
		{
			// ���� ��� ����
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block[blockform][0][i][j] == 1) {
						board[i + y][j + x / 2] = 2;//������ ������ �Է�
					}
				}
			}
			x = 8;
			y = 0;//���� ���� ���� ��ġ
			CreateRandomForm();
		}
	}
}