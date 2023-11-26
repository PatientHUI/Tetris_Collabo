#pragma once
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include "Blocks.h"
#include "Board.h"
#include <stdlib.h> //srand, rand�� ����ϱ� ���� �������
#include <time.h> // time�� ����ϱ� ���� �������
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define ARROW 224
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACEBAR 32

void BlockPrint();
void BoardPrint();
void textcolor(int);
bool BottomCollide_Check(int, int);
bool SideCollide_Check(int, int);
void ChangeToFixedBlock(int, int);
int CreateRandomForm();
void Board_Blink(int);
bool Check_Gameover();
void title(void); //���ӽ���ȭ�� 
void BlockPrint();
void BoardPrint();
void gameover(void); //��������ȭ��
void textcolor(int);
bool BottomCollide_Check(int, int);
bool SideCollide_Check(int, int);
void ChangeToFixedBlock(int, int);
int CreateRandomForm();
void Board_Blink(int);
bool Check_Gameover();


int x = BoardX + 2 * 5;   // Ŀ�� x�� ��������
int y = BoardY;   // Ŀ�� y�� ��������
int x_start = BoardX + 2 * 5;
int y_start = BoardY;
int blockform = 0;
int blockform_next = 0;
int block_rotation = 0;
int currentScore = 0;

clock_t end_T, startDropT, startGroundT;

// Consoleâ�� ���ϴ� x,y��ġ�� �̵��ϰ� �ϴ� �Լ�
void gotoxy(int x, int y) {
	COORD Pos;	//COORD�� x,y�� �����ϴ� ����ü �ڷ���(windows.h�� ����)
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //���ϴ� x,y��ġ�� �̵� Pos�� x,y �ּ� ����
}

// Cursor�� Visible ���ο� Size �����ϴ� �Լ�
void CursorView(bool Visibility, int CursorSize) {
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = Visibility;
	ConsoleCursor.dwSize = CursorSize;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);  //ConsoleCursor�� �ּҰ� ��ü�� ����
}

void title(void) {
	gotoxy(x + 20, y + 0); textcolor(13); printf("��������"); textcolor(9); printf(" �������"); textcolor(10); printf(" ��������"); textcolor(12); printf(" ������ "); textcolor(14); printf(" ������"); textcolor(15); printf("  ������ "); Sleep(100);
	gotoxy(x + 20, y + 1); textcolor(13); printf("   ��   "); textcolor(9); printf(" ��     "); textcolor(10); printf("    ��   "); textcolor(12); printf(" ��    ��  "); textcolor(14); printf(" �� "); textcolor(15); printf("  ��       "); Sleep(100);
	gotoxy(x + 20, y + 2); textcolor(13); printf("   ��   "); textcolor(9); printf(" �������"); textcolor(10); printf("    ��   "); textcolor(12); printf(" ������  "); textcolor(14); printf("  ��  "); textcolor(15); printf("  ������ "); Sleep(100);
	gotoxy(x + 20, y + 3); textcolor(13); printf("   ��   "); textcolor(9); printf(" ��     "); textcolor(10); printf("    ��   "); textcolor(12); printf(" ��   ��  "); textcolor(14); printf("  ��  "); textcolor(15); printf("       ��"); Sleep(100);
	gotoxy(x + 20, y + 4); textcolor(13); printf("   ��   "); textcolor(9); printf(" �������"); textcolor(10); printf("    ��   "); textcolor(12); printf(" ��    ��"); textcolor(14); printf(" ������"); textcolor(15); printf("  ������ "); Sleep(100);
	gotoxy(x + 20, y + 7); printf("Please Enter Any Key to Start..."); Sleep(120);
	gotoxy(x + 20, y + 8); printf("Made By: MINIGAME_interface");

	while (1) {
		if (kbhit()) break; //Ű�Է��� ������ ���ѷ��� ���� 
	}

	getch(); //���ۿ� ��ϵ� Ű���� ���� 
}

void KeyInput(void) {
	int KeyNow;
	bool B, S;
	// _kbhit�� Ű�� ���� ��� 0�� �ƴ� ���� ��ȯ�Ѵ�.

	if (_kbhit()) {
		KeyNow = _getch();

		if (KeyNow == SPACEBAR) {

			int rot_temp = block_rotation;
			block_rotation = (block_rotation + 1) % 4;

			if (SideCollide_Check(x, y) == true || BottomCollide_Check(x, y) == true) {
				block_rotation = rot_temp;
			}

		}
		// ����Ű�� �ƽ�Ű�ڵ� �� Ȯ��Ű�̴�. 2����Ʈ�� �ΰ��� ���� �ް� ù��° 224, �ι�°�� Up,Down,Left,Right�� ���� �ٸ� ������ �޾ƿ´�.  
		if (KeyNow == ARROW) {
			KeyNow = _getch();
			switch (KeyNow) {

				/*
				*
				case UP:
					gotoxy(x, --y);
					BlockPrint();

					break;

				*/

			case DOWN:
				// ��ĭ�Ʒ� y������ �浹�ϴ��� �˻�
				B = BottomCollide_Check(x, ++y);
				--y;
				if (B == true) {
					//�Ʒ��� ��ֹ��� �浹�ϴ� ��� �������� ��
					ChangeToFixedBlock(x, y);
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
				gotoxy(x + col * 2, y + row);
				textcolor(7);

				printf("��");
			}

		}
	}

}

void BoardPrint() {

	//���� ����� �Ѱ輱 

	for (int x = 1; x < 13; x++) {
		//�ܼ�â�� x*2�� ��ĭ
		gotoxy(BoardX + x * 2, BoardY + 1);

		printf("-");

	}

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
		gotoxy(BoardX + i * 2, BoardY + B_HEIGHT - 1);

		if (board[B_HEIGHT - 1][i] == 1) {
			textcolor(2);
			printf("��");
		}


	}

	// ���� ���� ����


	for (int j = 0; j < B_HEIGHT - 1; j++) {
		for (int i = 1; i < B_WIDTH - 1; i++) {
			gotoxy(BoardX + i * 2, BoardY + j);
			if (board[j][i] == 3) {
				textcolor(8);
				printf("��");
			}

		}
	}


}

void Board_Blink(int blink_line) {

	//���� ����� �Ѱ輱 

	for (int x = 1; x < 13; x++) {
		//�ܼ�â�� x*2�� ��ĭ
		gotoxy(BoardX + x * 2, BoardY + 1);

		printf("-");

	}

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
		gotoxy(BoardX + i * 2, BoardY + B_HEIGHT - 1);

		if (board[B_HEIGHT - 1][i] == 1) {
			textcolor(2);
			printf("��");
		}


	}

	// ���� ���� ����


	for (int j = 0; j < B_HEIGHT - 1; j++) {
		for (int i = 1; i < B_WIDTH - 1; i++) {
			gotoxy(BoardX + i * 2, BoardY + j);
			if (board[j][i] == 3) {
				if (j == blink_line) {
					textcolor(3);
					printf("��");
				}
				else {
					textcolor(8);
					printf("��");
				}

			}

		}
	}

	Sleep(200);

}


//�Ʒ��� ��ֹ��� ���� �浹���θ� Ȯ���ϴ� �Լ�(Bottom Check)
bool BottomCollide_Check(int x, int y) {
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
void ChangeToFixedBlock(int x, int y) {
	//x,y�� 4X4���� ���� ���� �� ��ǥ����.
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (Block[blockform][block_rotation][row][col] == 2) {
				board[y + row - 3][(x - 4) / 2 + col] = 3;

			}
		}
	}
}




int CreateRandomForm() {
	srand((int)time(NULL));
	return (rand() % 7);
}



void removeline() {
	// ����!! �ٸ� �Լ��� j<->i ����� �ݴ��̴�. (Ư���� ������ �ִ°��� �ƴ�)
	for (int i = 21; i >= 0; i--) {
		int cnt = 0;
		// ���� ������ ���ٿ� ���� ����� �˻�
		for (int j = 1; j < 13; j++) {
			if (board[i][j] >= 2) {
				cnt++; // ��� ���� ����
			}
		}
		// ����� ���� ������ ä��� ���
		if (cnt >= 12) {

			Board_Blink(i);

			currentScore += 100;

			for (int k = 0; i - k >= 0; k++) {
				for (int a = 1; a < 13; a++) {



					if (i - k >= 1) // �� �� ���� �ƴ϶��
					{
						board[i - k][a] = board[i - k - 1][a]; // �� ���� �Ʒ��� �̵� (���� �� ����)
					}
					else {
						board[i - k][a] = 0; // �� �� ��� �� �� ����(���� �� ���� ������ ��� ���� �Ʒ��� ���پ� �� �̵��� ����)
					}
				}
			}
			// ��� ����� ó���� �� ������ ���� 0���� ����

		}
	}
}



void DropBlock()
{
	end_T = clock();
	if ((float)(end_T - startDropT) >= 700)//0.7�ʵ��� ������ ������ ������
	{
		if (BottomCollide_Check(x, y + 1) == true) {
			ChangeToFixedBlock(x, y);

			x = x_start;
			y = y_start;
			blockform = blockform_next;
			blockform_next = CreateRandomForm();
			block_rotation = 0;

			//���� �浹�ϸ� �Լ� ����
		}
		else {
			y++;//�ƴϸ� ��ĭ �Ʒ��� �̵�
			startDropT = clock();//�� �����ð��� ���Ӱ� ����
			startGroundT = clock();
		}

		//system("cls");
	}
}


bool Check_Gameover() {
	for (int i = 1; i < 13; i++) {
		if (board[1][i] == 3) {

			return false;
		}
	}
	return true;

}

void DrawScreen()   // ȭ�� ��ü�� �׸���.
{
	//   ���ӿ� ���� ���� ���
	gotoxy(45, 7); printf("!! INTERFACE TETRIS GAME !!");
	gotoxy(45, 10);   printf("Current score: %10d", currentScore);
	gotoxy(45, 13); printf("��   �� :  Left / Right");
	gotoxy(45, 14); printf("  ��   :  Drop");
	gotoxy(45, 16); printf("SPACE : block rotation");

}

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}


#define NextBlockX 80
#define NextBlockY 13

void ShowNextBlock();
void DeleteNextBlock();
int NextBlock[6][6];

void ShowNextBlock() {
	int frameX = NextBlockX - 2;
	int frameY = NextBlockY - 1;
	int frameWidth = 6;
	int frameHeight = 6;

	gotoxy(frameX, frameY - 1); textcolor(13); printf("NEXT  BLOCK");
	for (int i = 0; i < frameHeight; i++) {
		for (int j = 0; j < frameWidth; j++) {
			gotoxy(frameX + j * 2, frameY + i);
			if (i == 0 || i == frameHeight - 1 || j == 0 || j == frameWidth - 1) {
				textcolor(9);
				printf("��");
			}
			else {
				printf("  ");
			}
		}
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			gotoxy(NextBlockX + j * 2, NextBlockY + i);
			printf("  ");
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			NextBlock[i][j] = Block[blockform_next][0][i][j];
			if (NextBlock[i][j] == 2) {
				gotoxy(NextBlockX + j * 2, NextBlockY + i);
				textcolor(7);
				printf("��");
			}
		}
	}
}

void DeleteNextBlock() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			gotoxy(NextBlockX + j * 2, NextBlockY + i);
			printf("  ");
		}
	}
}



#pragma comment(lib, "winmm.lib") // bgm ���� 

#define SOUND_FILE_NAME "C:\\msc\\BGM Tetris Bradinsky" // �������� 

void gameover(void)
{
	textcolor(9);

	gotoxy(x + 20, y + 0); textcolor(13); printf(" ����� "); textcolor(9); printf("  ����� "); textcolor(10); printf(" ��    ��"); textcolor(12); printf(" �������"); Sleep(100);
	gotoxy(x + 20, y + 1); textcolor(13); printf("��     "); textcolor(9); printf(" ��    ��"); textcolor(10); printf(" ���  ���"); textcolor(12); printf(" ��     "); Sleep(100);
	gotoxy(x + 20, y + 2); textcolor(13); printf("��  ����"); textcolor(9); printf(" �������"); textcolor(10); printf(" �� ��� ��"); textcolor(12); printf(" �������"); Sleep(100);
	gotoxy(x + 20, y + 3); textcolor(13); printf("��    ��"); textcolor(9); printf(" ��    ��"); textcolor(10); printf(" ��    ��"); textcolor(12); printf(" ��     "); Sleep(100);
	gotoxy(x + 20, y + 4); textcolor(13); printf(" ����� "); textcolor(9); printf(" ��    ��"); textcolor(10); printf(" ��    ��"); textcolor(12); printf(" �������"); Sleep(100);

	gotoxy(x + 20, y + 6); textcolor(13); printf(" ����� "); textcolor(9); printf(" ��    ��"); textcolor(10); printf(" �������"); textcolor(12); printf(" ������ "); Sleep(100);
	gotoxy(x + 20, y + 7); textcolor(13); printf("��    ��"); textcolor(9); printf(" ��    ��"); textcolor(10); printf(" ��     "); textcolor(12); printf(" ��    ��"); Sleep(100);
	gotoxy(x + 20, y + 8); textcolor(13); printf("��    ��"); textcolor(9); printf(" ��    ��"); textcolor(10); printf(" �������"); textcolor(12); printf(" ������ "); Sleep(100);
	gotoxy(x + 20, y + 9); textcolor(13); printf("��    ��"); textcolor(9); printf("  ��  �� "); textcolor(10); printf(" ��     "); textcolor(12); printf(" ��   �� "); Sleep(100);
	gotoxy(x + 20, y + 10); textcolor(13); printf(" ����� "); textcolor(9); printf("   ���  "); textcolor(10); printf(" �������"); textcolor(12); printf(" ��    ��"); Sleep(100);
}