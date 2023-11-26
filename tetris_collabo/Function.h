#pragma once
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include "Blocks.h"
#include "Board.h"
#include <stdlib.h> //srand, rand를 사용하기 위한 헤더파일
#include <time.h> // time을 사용하기 위한 헤더파일
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
void title(void); //게임시작화면 
void BlockPrint();
void BoardPrint();
void gameover(void); //게임종료화면
void textcolor(int);
bool BottomCollide_Check(int, int);
bool SideCollide_Check(int, int);
void ChangeToFixedBlock(int, int);
int CreateRandomForm();
void Board_Blink(int);
bool Check_Gameover();


int x = BoardX + 2 * 5;   // 커서 x값 전역변수
int y = BoardY;   // 커서 y값 전역변수
int x_start = BoardX + 2 * 5;
int y_start = BoardY;
int blockform = 0;
int blockform_next = 0;
int block_rotation = 0;
int currentScore = 0;

clock_t end_T, startDropT, startGroundT;

// Console창의 원하는 x,y위치로 이동하게 하는 함수
void gotoxy(int x, int y) {
	COORD Pos;	//COORD는 x,y값 저장하는 구조체 자료형(windows.h에 포함)
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //원하는 x,y위치로 이동 Pos는 x,y 주소 저장
}

// Cursor의 Visible 여부와 Size 결정하는 함수
void CursorView(bool Visibility, int CursorSize) {
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = Visibility;
	ConsoleCursor.dwSize = CursorSize;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);  //ConsoleCursor의 주소값 자체를 전달
}

void title(void) {
	gotoxy(x + 20, y + 0); textcolor(13); printf("■■■■■■■"); textcolor(9); printf(" ■■■■■■"); textcolor(10); printf(" ■■■■■■■"); textcolor(12); printf(" ■■■■■ "); textcolor(14); printf(" ■■■■■"); textcolor(15); printf("  ■■■■■ "); Sleep(100);
	gotoxy(x + 20, y + 1); textcolor(13); printf("   ■   "); textcolor(9); printf(" ■     "); textcolor(10); printf("    ■   "); textcolor(12); printf(" ■    ■  "); textcolor(14); printf(" ■ "); textcolor(15); printf("  ■       "); Sleep(100);
	gotoxy(x + 20, y + 2); textcolor(13); printf("   ■   "); textcolor(9); printf(" ■■■■■■"); textcolor(10); printf("    ■   "); textcolor(12); printf(" ■■■■■  "); textcolor(14); printf("  ■  "); textcolor(15); printf("  ■■■■■ "); Sleep(100);
	gotoxy(x + 20, y + 3); textcolor(13); printf("   ■   "); textcolor(9); printf(" ■     "); textcolor(10); printf("    ■   "); textcolor(12); printf(" ■   ■  "); textcolor(14); printf("  ■  "); textcolor(15); printf("       ■"); Sleep(100);
	gotoxy(x + 20, y + 4); textcolor(13); printf("   ■   "); textcolor(9); printf(" ■■■■■■"); textcolor(10); printf("    ■   "); textcolor(12); printf(" ■    ■"); textcolor(14); printf(" ■■■■■"); textcolor(15); printf("  ■■■■■ "); Sleep(100);
	gotoxy(x + 20, y + 7); printf("Please Enter Any Key to Start..."); Sleep(120);
	gotoxy(x + 20, y + 8); printf("Made By: MINIGAME_interface");

	while (1) {
		if (kbhit()) break; //키입력이 있으면 무한루프 종료 
	}

	getch(); //버퍼에 기록된 키값을 버림 
}

void KeyInput(void) {
	int KeyNow;
	bool B, S;
	// _kbhit는 키를 누른 경우 0이 아닌 값을 반환한다.

	if (_kbhit()) {
		KeyNow = _getch();

		if (KeyNow == SPACEBAR) {

			int rot_temp = block_rotation;
			block_rotation = (block_rotation + 1) % 4;

			if (SideCollide_Check(x, y) == true || BottomCollide_Check(x, y) == true) {
				block_rotation = rot_temp;
			}

		}
		// 방향키는 아스키코드 상 확장키이다. 2바이트의 두개의 값을 받고 첫번째 224, 두번째는 Up,Down,Left,Right에 따라 다른 정수를 받아온다.  
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
				// 한칸아래 y값에서 충돌하는지 검사
				B = BottomCollide_Check(x, ++y);
				--y;
				if (B == true) {
					//아래쪽 장애물과 충돌하는 경우 고정블럭이 됨
					ChangeToFixedBlock(x, y);
					x = x_start;
					y = y_start;
					blockform = blockform_next;
					blockform_next = CreateRandomForm();
					block_rotation = 0;

				}
				else {
					// 충돌 X-> 아래로 이동
					gotoxy(x, ++y);
				}
				break;

			case LEFT:
				S = SideCollide_Check(x -= 2, y);
				x += 2;
				if (S == false) {
					//아래쪽 장애물과 충돌하는 경우 고정블럭이 됨
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
					//아래쪽 장애물과 충돌하는 경우 고정블럭이 됨
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

				printf("▣");
			}

		}
	}

}

void BoardPrint() {

	//보드 상단의 한계선 

	for (int x = 1; x < 13; x++) {
		//콘솔창상 x*2가 한칸
		gotoxy(BoardX + x * 2, BoardY + 1);

		printf("-");

	}

	// 보드 테두리 구현

	for (int j = 0; j < B_HEIGHT; j++) {

		// 왼쪽 테두리
		gotoxy(BoardX, BoardY + j);
		if (board[j][0] == 1) {
			textcolor(2);
			printf("▣");
		}

		// 오른쪽 테두리
		gotoxy(BoardX + B_WIDTH * 2 - 2, BoardY + j);
		if (board[j][B_WIDTH - 1] == 1) {
			textcolor(2);
			printf("▣");
		}

	}

	// 아랫쪽 테두리
	for (int i = 0; i < B_WIDTH; i++) {
		gotoxy(BoardX + i * 2, BoardY + B_HEIGHT - 1);

		if (board[B_HEIGHT - 1][i] == 1) {
			textcolor(2);
			printf("▣");
		}


	}

	// 보드 내부 구현


	for (int j = 0; j < B_HEIGHT - 1; j++) {
		for (int i = 1; i < B_WIDTH - 1; i++) {
			gotoxy(BoardX + i * 2, BoardY + j);
			if (board[j][i] == 3) {
				textcolor(8);
				printf("◈");
			}

		}
	}


}

void Board_Blink(int blink_line) {

	//보드 상단의 한계선 

	for (int x = 1; x < 13; x++) {
		//콘솔창상 x*2가 한칸
		gotoxy(BoardX + x * 2, BoardY + 1);

		printf("-");

	}

	for (int j = 0; j < B_HEIGHT; j++) {

		// 왼쪽 테두리
		gotoxy(BoardX, BoardY + j);
		if (board[j][0] == 1) {
			textcolor(2);
			printf("▣");
		}

		// 오른쪽 테두리
		gotoxy(BoardX + B_WIDTH * 2 - 2, BoardY + j);
		if (board[j][B_WIDTH - 1] == 1) {
			textcolor(2);
			printf("▣");
		}

	}

	// 아랫쪽 테두리
	for (int i = 0; i < B_WIDTH; i++) {
		gotoxy(BoardX + i * 2, BoardY + B_HEIGHT - 1);

		if (board[B_HEIGHT - 1][i] == 1) {
			textcolor(2);
			printf("▣");
		}


	}

	// 보드 내부 구현


	for (int j = 0; j < B_HEIGHT - 1; j++) {
		for (int i = 1; i < B_WIDTH - 1; i++) {
			gotoxy(BoardX + i * 2, BoardY + j);
			if (board[j][i] == 3) {
				if (j == blink_line) {
					textcolor(3);
					printf("◈");
				}
				else {
					textcolor(8);
					printf("◈");
				}

			}

		}
	}

	Sleep(200);

}


//아래쪽 장애물과 블럭의 충돌여부를 확인하는 함수(Bottom Check)
bool BottomCollide_Check(int x, int y) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			gotoxy(x + col * 2, y + row);
			// 블럭이 있는 위치에
			if (Block[blockform][block_rotation][row][col] == 2) {
				// 보드와 충돌하는지 확인
				if (board[y + row - 3][(x - 4) / 2 + col] == 1 || board[y + row - 3][(x - 4) / 2 + col] == 3) {
					return true;
				}
			}

		}

	}
	return false;
}

// 블럭과 양쪽 장애물 충돌여부 확인하는 함수(Side Check)
bool SideCollide_Check(int x, int y) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			gotoxy(x + col * 2, y + row);
			// 블럭이 있는 위치에
			if (Block[blockform][block_rotation][row][col] == 2) {
				// 보드와 충돌하는지 확인
				if (board[y + row - 3][(x - 4) / 2 + col] == 1 || board[y + row - 3][(x - 4) / 2 + col] == 3) {
					return true;
				}
			}

		}

	}
	return false;

}

// 블럭과 아래쪽 장애물이 충돌하면 보드에 '3'으로 저장하여 정지 블록으로 변경 
void ChangeToFixedBlock(int x, int y) {
	//x,y는 4X4블럭의 가장 왼쪽 위 좌표값임.
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
	// 주의!! 다른 함수와 j<->i 사용이 반대이다. (특별한 이유가 있는것은 아님)
	for (int i = 21; i >= 0; i--) {
		int cnt = 0;
		// 보드 가로축 한줄에 블럭이 몇개인지 검사
		for (int j = 1; j < 13; j++) {
			if (board[i][j] >= 2) {
				cnt++; // 블록 개수 증가
			}
		}
		// 블록이 줄을 완전히 채우는 경우
		if (cnt >= 12) {

			Board_Blink(i);

			currentScore += 100;

			for (int k = 0; i - k >= 0; k++) {
				for (int a = 1; a < 13; a++) {



					if (i - k >= 1) // 맨 위 줄이 아니라면
					{
						board[i - k][a] = board[i - k - 1][a]; // 윗 줄을 아래로 이동 (원래 줄 삭제)
					}
					else {
						board[i - k][a] = 0; // 맨 위 블록 한 줄 삭제(제일 윗 줄을 제외한 모든 블럭을 아래로 한줄씩 다 이동한 상태)
					}
				}
			}
			// 모든 블록을 처리한 후 삭제된 줄을 0으로 설정

		}
	}
}



void DropBlock()
{
	end_T = clock();
	if ((float)(end_T - startDropT) >= 700)//0.7초동안 반응이 없으면 내려옴
	{
		if (BottomCollide_Check(x, y + 1) == true) {
			ChangeToFixedBlock(x, y);

			x = x_start;
			y = y_start;
			blockform = blockform_next;
			blockform_next = CreateRandomForm();
			block_rotation = 0;

			//블럭이 충돌하면 함수 종료
		}
		else {
			y++;//아니면 한칸 아래로 이동
			startDropT = clock();//블럭 생성시간을 새롭게 저장
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

void DrawScreen()   // 화면 전체를 그린다.
{
	//   게임에 대한 정보 출력
	gotoxy(45, 7); printf("!! INTERFACE TETRIS GAME !!");
	gotoxy(45, 10);   printf("Current score: %10d", currentScore);
	gotoxy(45, 13); printf("◁   ▷ :  Left / Right");
	gotoxy(45, 14); printf("  ▽   :  Drop");
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
				printf("■");
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
				printf("▣");
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



#pragma comment(lib, "winmm.lib") // bgm 삽입 

#define SOUND_FILE_NAME "C:\\msc\\BGM Tetris Bradinsky" // 음악파일 

void gameover(void)
{
	textcolor(9);

	gotoxy(x + 20, y + 0); textcolor(13); printf(" ■■■■ "); textcolor(9); printf("  ■■■■ "); textcolor(10); printf(" ■    ■"); textcolor(12); printf(" ■■■■■■"); Sleep(100);
	gotoxy(x + 20, y + 1); textcolor(13); printf("■     "); textcolor(9); printf(" ■    ■"); textcolor(10); printf(" ■■  ■■"); textcolor(12); printf(" ■     "); Sleep(100);
	gotoxy(x + 20, y + 2); textcolor(13); printf("■  ■■■"); textcolor(9); printf(" ■■■■■■"); textcolor(10); printf(" ■ ■■ ■"); textcolor(12); printf(" ■■■■■■"); Sleep(100);
	gotoxy(x + 20, y + 3); textcolor(13); printf("■    ■"); textcolor(9); printf(" ■    ■"); textcolor(10); printf(" ■    ■"); textcolor(12); printf(" ■     "); Sleep(100);
	gotoxy(x + 20, y + 4); textcolor(13); printf(" ■■■■ "); textcolor(9); printf(" ■    ■"); textcolor(10); printf(" ■    ■"); textcolor(12); printf(" ■■■■■■"); Sleep(100);

	gotoxy(x + 20, y + 6); textcolor(13); printf(" ■■■■ "); textcolor(9); printf(" ■    ■"); textcolor(10); printf(" ■■■■■■"); textcolor(12); printf(" ■■■■■ "); Sleep(100);
	gotoxy(x + 20, y + 7); textcolor(13); printf("■    ■"); textcolor(9); printf(" ■    ■"); textcolor(10); printf(" ■     "); textcolor(12); printf(" ■    ■"); Sleep(100);
	gotoxy(x + 20, y + 8); textcolor(13); printf("■    ■"); textcolor(9); printf(" ■    ■"); textcolor(10); printf(" ■■■■■■"); textcolor(12); printf(" ■■■■■ "); Sleep(100);
	gotoxy(x + 20, y + 9); textcolor(13); printf("■    ■"); textcolor(9); printf("  ■  ■ "); textcolor(10); printf(" ■     "); textcolor(12); printf(" ■   ■ "); Sleep(100);
	gotoxy(x + 20, y + 10); textcolor(13); printf(" ■■■■ "); textcolor(9); printf("   ■■  "); textcolor(10); printf(" ■■■■■■"); textcolor(12); printf(" ■    ■"); Sleep(100);
}