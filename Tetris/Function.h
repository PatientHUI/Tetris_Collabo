#pragma once
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include "Blocks.h"
#include "Board.h"
#include <stdlib.h> //srand, rand를 사용하기 위한 헤더파일
#include <time.h> // time을 사용하기 위한 헤더파일

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

int x = BoardX + 2 * 5;	// 커서 x값 전역변수
int y = BoardY;	// 커서 y값 전역변수
int x_start = BoardX + 2 * 5;
int y_start = BoardY;
int blockform = 0;
int blockform_next = 0;
int block_rotation = 0;
// Console창의 원하는 x,y위치로 이동하게 하는 함수
void gotoxy(int x, int y) {
	COORD Pos;	//COORD는 x,y값 저장하는 구조체 자료형(windows.h에 포함)
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //원하는 x,y위치로 이동 Pos는 x,y 주소 저장
}

// Cursor의 Visible 여부와 Size 결정하는 함수
void CursorView(bool Visibility,int CursorSize) {
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = Visibility;
	ConsoleCursor.dwSize = CursorSize;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);  //ConsoleCursor의 주소값 자체를 전달
}


void KeyInput(void) {
	int KeyNow;
	bool B,S;
		// _kbhit는 키를 누른 경우 0이 아닌 값을 반환한다.

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
			// 방향키는 아스키코드 상 확장키이다. 2바이트의 두개의 값을 받고 첫번째 224, 두번째는 Up,Down,Left,Right에 따라 다른 정수를 받아온다.  
			if (KeyNow == ARROW) {
				KeyNow = _getch();
				switch (KeyNow) {

				case UP:	
					gotoxy(x,--y);
					BlockPrint();
					
					break;

				case DOWN:	
					// 한칸아래 y값에서 충돌하는지 검사
					B = BottomCollide_Check(x, ++y);
					--y;
					if (B == true) {
						//아래쪽 장애물과 충돌하는 경우 고정블럭이 됨
						ChangeToFixedBlock(x,y);
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
				gotoxy(x + col*2, y + row);
				textcolor(7);

				printf("▣");
			}
		
		}
	}

}

void BoardPrint() {

	// 보드 상단의 한계선 
	// 
	//for (int x = 1; x < 13; x++) {
	//	//콘솔창상 x*2가 한칸
	//	gotoxy(BoardX + x * 2, BoardY );
	//	
	//	printf("~");
	//	
	//}

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
		gotoxy(BoardX + i*2, BoardY +  B_HEIGHT -1 );
		
		if (board[B_HEIGHT - 1][i] == 1) {
			textcolor(2);
			printf("▣");
		}


	}

	// 보드 내부 구현


	for (int j = 0; j< B_HEIGHT -1; j++) {
		for (int i = 1; i < B_WIDTH - 1; i++) {
			gotoxy(BoardX + i * 2, BoardY + j);
			if (board[j][i] == 3) {
				textcolor(3);
				printf("◈");
			}
			
		}
	}


}



//아래쪽 장애물과 블럭의 충돌여부를 확인하는 함수(Bottom Check)
bool BottomCollide_Check(int x,int y) {
	for(int row = 0; row < 4 ;row++){
		for (int col = 0; col < 4; col++) {
			gotoxy(x+col*2, y+row);
			// 블럭이 있는 위치에
			if (Block[blockform][block_rotation][row][col] == 2) {
				// 보드와 충돌하는지 확인
				if (board[y+ row - 3][(x - 4) / 2 + col] == 1 || board[y + row - 3][(x - 4) / 2 + col] == 3) {
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
void ChangeToFixedBlock(int x,int y) {
	//x,y는 4X4블럭의 가장 왼쪽 위 좌표값임.
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (Block[blockform][block_rotation][row][col] == 2) {
				board[y + row - 3 ][(x - 4) / 2 + col] = 3;
				
			}
		}
	}
}
void removeline() {
	for (int i = 21; i >= 0; i--) {
		int cnt = 0;
		for (int j = 1; j < 13; j++) {
			if (board[i][j] >= 2) {
				cnt++; // 블록 개수 증가
			}
		}
		// 블록이 줄을 완전히 채우는 경우
		if (cnt >= 12) {
			for (int j = 0; i - j >= 0; j++) {
				for (int a = 1; a < 13; a++) {
					if (i - j >= 1) // 맨 위 줄이 아니라면
					{
						board[i - j][a] = board[i - j - 1][a]; // 윗 줄을 아래로 이동 (원래 줄 삭제)
					}
					else {
						board[i - j][a] = 0; // 맨 위면 블록 한 줄만 삭제
					}
				}
			}
			// 모든 블록을 처리한 후 삭제된 줄을 0으로 설정
			
		}
	}
}


int CreateRandomForm() {
	srand(time(NULL));
	return rand() % 7;

}
void DropBlock()
{
	end_T = clock();
	if ((float)(end_T - startDropT) >= 700)//0.7초동안 반응이 없으면 내려옴
	{
		if (BottomCollide_Check(x, y + 1) == true) {
			ChangeToFixedBlock(x, y);
			x = 11;
			y = 0;
			CreateRandomForm();
			
			return;//블럭이 충돌하면 함수 종료
		}
		y++;//아니면 한칸 아래로 이동
		startDropT = clock();//블럭 생성시간을 새롭게 저장
		startGroundT = clock();
		system("cls");
	}
}



void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}
