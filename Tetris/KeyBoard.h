#pragma once
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include "Blocks.h"
#include "Board.h"


#define ARROW 224
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACEBAR 32

void BlockPrint();
void BoardPrint();
void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}



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


int KeyInput(void) {
	int KeyNow;
	
	int x = BoardX + 2 * 5;
	int y = BoardY;
	gotoxy(x,y);
	//BlockPrint();

	while (1) {
		// _kbhit는 키를 누른 경우 0이 아닌 값을 반환한다.
		BoardPrint();

		if (_kbhit()) {
			KeyNow = _getch();

			if (KeyNow == SPACEBAR) {
				gotoxy(x, y);
				printf("x:%d y:%d", x, y);

			}
			// 방향키는 아스키코드 상 확장키이다. 2바이트의 두개의 값을 받고 첫번째 224, 두번째는 Up,Down,Left,Right에 따라 다른 정수를 받아온다.  
			if (KeyNow == ARROW) {
				KeyNow = _getch();
				switch (KeyNow) {

				case UP:	
					system("cls");
					gotoxy(x,--y);
					//printf("x: %d y: %d", x, y);
					
					BlockPrint();

					break;
				case DOWN:	
					system("cls");
					gotoxy(x, ++y);
					//printf("x: %d y: %d", x, y);

					BlockPrint();

					break;
				case LEFT:	
					system("cls");
					gotoxy(x-=2, y);
					//printf("x: %d y: %d", x, y);

					BlockPrint();

					break;
				case RIGHT:	
					system("cls");
					gotoxy(x+=2, y);
					//printf("x: %d y: %d", x, y);

					BlockPrint();

					break;

				
				}
			}
		}
		
	}
	
}
	
void BlockPrint() {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {

			if (Block[1][0][row][col] == 2) {
				//Console_GoToXY(Block_X + col, BoardY + row);
				printf("▣");
			}
		}
	}

}

void BoardPrint() {

	// 보드 상단의 한계선 
	for (int x = 1; x < 13; x++) {
		//콘솔창상 x*2가 한칸
		gotoxy(BoardX + x * 2, BoardY + 1);
		
		//printf("~");
		
	}

	// 보드 테두리 구현
		
	for (int y = 0; y < B_HEIGHT; y++) {

		// 왼쪽 테두리
		gotoxy(BoardX, BoardY + y-1);
		if (board[y][0] == 1) {
			textcolor(2);
			printf("▣");
		}

		// 오른쪽 테두리
		gotoxy(BoardX + B_WIDTH * 2 - 3, BoardY + y-1);
		if (board[y][B_WIDTH - 1] == 1) {
			textcolor(2);
			printf("▣");
		}

	}

	// 아랫쪽 테두리
	for (int x = 0; x < B_WIDTH; x++) {
		gotoxy(BoardX + x, BoardY +  B_HEIGHT -1 );
		
		if (board[B_HEIGHT - 1][x] == 1) {
			textcolor(2);
			printf("▣");
		}


	}
	textcolor(7);



}

void BoardAndBlock() {
	
}


void BlockCollide() {


}


void Move_Limit() {
	

}