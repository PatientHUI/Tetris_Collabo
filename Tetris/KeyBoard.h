#pragma once
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include "Blocks.h"

#define ARROW 224
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACEBAR 32

void BlockPrint();



// Console창의 원하는 x,y위치로 이동하게 하는 함수
void Console_GoToXY(int x, int y) {
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
	int x = 20; //처음 시작 위치 x값
	int y = 10; //처음 시작 위치 y값

	Console_GoToXY(x, y);
	
	BlockPrint();
	while (1) {
		// _kbhit는 키를 누른 경우 0이 아닌 값을 반환한다.
		if (_kbhit()) {
			KeyNow = _getch();

			if (KeyNow == SPACEBAR) {
				printf("SPACEBAR을 입력받았습니다.\n");
			}
			// 방향키는 아스키코드 상 확장키이다. 2바이트의 두개의 값을 받고 첫번째 224, 두번째는 Up,Down,Left,Right에 따라 다른 정수를 받아온다.  
			if (KeyNow == ARROW) {
				KeyNow = _getch();
				switch (KeyNow) {

				case UP:	
					system("cls");
					Console_GoToXY(x,--y);
					BlockPrint();

					break;
				case DOWN:	
					system("cls");
					Console_GoToXY(x, ++y);
					BlockPrint();

					break;
				case LEFT:	
					system("cls");
					Console_GoToXY(x-2, y);
					BlockPrint();

					break;
				case RIGHT:	
					system("cls");
					Console_GoToXY(x+2, y);
					BlockPrint();

					break;
				default: break;
				}
			}
		}
		
	}
	
}

void BlockPrint() {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (Block[1][0][row][col] == 2) {
				printf("■");
			}
		}
	}
}



