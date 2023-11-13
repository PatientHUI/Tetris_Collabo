#pragma once
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include "Blocks.h"
#include "Board.h"
#include <stdlib.h> //srand, rand�� ����ϱ� ���� �������
#include <time.h> // time�� ����ϱ� ���� �������

#define ARROW 224
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACEBAR 32

void BlockPrint();
void BoardPrint();
void textcolor(int);
bool BottomCollide_Check(int,int);
bool SideCollide_Check(int,int);
void ChangeToFixedBlock(int, int);
int CreateRandomForm();

int x = BoardX + 2 * 5;	// Ŀ�� x�� ��������
int y = BoardY;	// Ŀ�� y�� ��������
int x_start = BoardX + 2 * 5;
int y_start = BoardY;
int blockform = 0;
int blockform_next = 0;
int block_rotation = 0;
// Consoleâ�� ���ϴ� x,y��ġ�� �̵��ϰ� �ϴ� �Լ�
void gotoxy(int x, int y) {
	COORD Pos;	//COORD�� x,y�� �����ϴ� ����ü �ڷ���(windows.h�� ����)
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //���ϴ� x,y��ġ�� �̵� Pos�� x,y �ּ� ����
}

// Cursor�� Visible ���ο� Size �����ϴ� �Լ�
void CursorView(bool Visibility,int CursorSize) {
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = Visibility;
	ConsoleCursor.dwSize = CursorSize;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);  //ConsoleCursor�� �ּҰ� ��ü�� ����
}


void KeyInput(void) {
	int KeyNow;
	bool B,S;
		// _kbhit�� Ű�� ���� ��� 0�� �ƴ� ���� ��ȯ�Ѵ�.

		if (_kbhit()) {
			KeyNow = _getch();

			if (KeyNow == SPACEBAR) {
				bool B, S;
				int rot_temp = block_rotation;
				block_rotation = (block_rotation + 1) % 4;

				if(SideCollide_Check(x,y) == true || BottomCollide_Check(x, y) == true){
					block_rotation = rot_temp;
				}
				
			}
			// ����Ű�� �ƽ�Ű�ڵ� �� Ȯ��Ű�̴�. 2����Ʈ�� �ΰ��� ���� �ް� ù��° 224, �ι�°�� Up,Down,Left,Right�� ���� �ٸ� ������ �޾ƿ´�.  
			if (KeyNow == ARROW) {
				KeyNow = _getch();
				switch (KeyNow) {

				case UP:	
					gotoxy(x,--y);
					BlockPrint();
					
					break;

				case DOWN:	
					// ��ĭ�Ʒ� y������ �浹�ϴ��� �˻�
					B = BottomCollide_Check(x, ++y);
					--y;
					if (B == true) {
						//�Ʒ��� ��ֹ��� �浹�ϴ� ��� �������� ��
						ChangeToFixedBlock(x,y);
						x = x_start;
						y = y_start;
						blockform = blockform_next;
						blockform_next = CreateRandomForm();
						block_rotation = 0;
						
					}
					else {
						// �浹 X-> �Ʒ��� �̵�
						gotoxy(x, ++y);
					}
					break;

				case LEFT:
					S = SideCollide_Check(x -= 2, y);
					x += 2;
					if (S == false) {
						//�Ʒ��� ��ֹ��� �浹�ϴ� ��� �������� ��
						gotoxy(x -= 2, y);
						break;
					}
					else {
						break;
					}

				case RIGHT:	
					S = SideCollide_Check(x += 2, y);
					x -= 2;
					if (S == false) {
						//�Ʒ��� ��ֹ��� �浹�ϴ� ��� �������� ��
						gotoxy(x += 2, y);
						break;
					}
					else {
						break;
					}

				
				}
			}
		}
		
	}
	
	
void BlockPrint() {
	 
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {

			if (Block[blockform][block_rotation][row][col] == 2) {
				gotoxy(x + col*2, y + row);
				textcolor(7);

				printf("��");
			}
		
		}
	}

}

void BoardPrint() {

	// ���� ����� �Ѱ輱 
	// 
	//for (int x = 1; x < 13; x++) {
	//	//�ܼ�â�� x*2�� ��ĭ
	//	gotoxy(BoardX + x * 2, BoardY );
	//	
	//	printf("~");
	//	
	//}

	// ���� �׵θ� ����
		
	for (int j = 0; j < B_HEIGHT; j++) {

		// ���� �׵θ�
		gotoxy(BoardX, BoardY + j);
		if (board[j][0] == 1) {
			textcolor(2);
			printf("��");
		}

		// ������ �׵θ�
		gotoxy(BoardX + B_WIDTH * 2 - 2, BoardY + j);
		if (board[j][B_WIDTH - 1] == 1) {
			textcolor(2);
			printf("��");
		}

	}

	// �Ʒ��� �׵θ�
	for (int i = 0; i < B_WIDTH; i++) {
		gotoxy(BoardX + i*2, BoardY +  B_HEIGHT -1 );
		
		if (board[B_HEIGHT - 1][i] == 1) {
			textcolor(2);
			printf("��");
		}


	}

	// ���� ���� ����


	for (int j = 0; j< B_HEIGHT -1; j++) {
		for (int i = 1; i < B_WIDTH - 1; i++) {
			gotoxy(BoardX + i * 2, BoardY + j);
			if (board[j][i] == 3) {
				textcolor(3);
				printf("��");
			}
			
		}
	}


}



//�Ʒ��� ��ֹ��� ���� �浹���θ� Ȯ���ϴ� �Լ�(Bottom Check)
bool BottomCollide_Check(int x,int y) {
	for(int row = 0; row < 4 ;row++){
		for (int col = 0; col < 4; col++) {
			gotoxy(x+col*2, y+row);
			// ���� �ִ� ��ġ��
			if (Block[blockform][block_rotation][row][col] == 2) {
				// ����� �浹�ϴ��� Ȯ��
				if (board[y+ row - 3][(x - 4) / 2 + col] == 1 || board[y + row - 3][(x - 4) / 2 + col] == 3) {
					return true;
				}
			}
			
		}
		     
	}
	return false;
}

// ���� ���� ��ֹ� �浹���� Ȯ���ϴ� �Լ�(Side Check)
bool SideCollide_Check(int x, int y) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			gotoxy(x + col * 2, y + row);
			// ���� �ִ� ��ġ��
			if (Block[blockform][block_rotation][row][col] == 2) {
				// ����� �浹�ϴ��� Ȯ��
				if (board[y + row - 3][(x - 4) / 2 + col] == 1 || board[y + row - 3][(x - 4) / 2 + col] == 3) {
					return true;
				}
			}

		}

	}
	return false;

}

// ���� �Ʒ��� ��ֹ��� �浹�ϸ� ���忡 '3'���� �����Ͽ� ���� ������� ���� 
void ChangeToFixedBlock(int x,int y) {
	//x,y�� 4X4���� ���� ���� �� ��ǥ����.
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (Block[blockform][block_rotation][row][col] == 2) {
				board[y + row - 3 ][(x - 4) / 2 + col] = 3;
				
			}
		}
	}
}


/*

void removeline() {
	for (int i = 21; i >= 0; i--) {
		int cnt = 0;
		for (int j = 1; j < 13; j++) {
			if (board[i][j] == 2) {
				cnt++;
			}
		}
		// ���� ���� �� �� ���
		if (cnt == 12) {

			// �ؿ� ���� �ʿ�
			for (int j = 0; i - j >= 0; j++) {
				for (int x = 1; x < 11; x++) {
					if (i - j - 1 >= 0) {
						board[i - j][x] = board[i - j - 1][x];
					}
					else {
						board[i - j][x] = 0;
					}
				}
			}
		}
	}

}

*/



int CreateRandomForm() {
	srand(time(NULL));
	return rand() % 7;
}


/*
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

*/


void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}