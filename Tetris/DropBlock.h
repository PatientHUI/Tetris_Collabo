#include <stdlib.h> //srand, rand를 사용하기 위한 헤더파일
#include <time.h> // time을 사용하기 위한 헤더파일

int CreateRandomForm() {
	srand(time(NULL));
	int blockform = rand() % 7;
	return blockform;
}

bool CheckCrash(int x, int y) {
	for (int i = 0; i < 4; i++) //블럭의 행
	{
		for (int j = 0; j < 4; j++) //블럭의 열
		{
			if (Block[blockform][blockRotation][i][j] == 2) {
				int t = board[i + y][j + x / 2];
				if (t == 1 || t == 2) { // 1=벽일 때, 2=블럭일 때
					return true;//충돌
				}
			}
		}
	}
	return false;
}

void DropBlock()
{
	endT = clock();
	if ((float)(endT - startDropT) >= 700)//0.7초동안 반응이 없으면 내려옴
	{
		if (CheckCrash(x, y + 1) == true) return;//블럭이 충돌하면 함수 종료
		y++;//아니면 한칸 아래로 이동
		startDropT = clock();//블럭 생성시간을 새롭게 저장
		system("cls");
	}
}
void BlockToGround() //충돌이후
{
	if (CheckCrash(x, y + 1) == true) {
		if ((float)(endT - startGroundT) > 1500)//충돌 후 1.5초가 지나면
		{
			// 현재 블록 저장
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (Block[blockform][0][i][j] == 1) {
						board[i + y][j + x / 2] = 2;//고정된 블럭으로 입력
					}
				}
			}
			x = 8;
			y = 0;//다음 생성 블럭의 위치
			CreateRandomForm();
		}
	}
}