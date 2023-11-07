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



// Consoleâ�� ���ϴ� x,y��ġ�� �̵��ϰ� �ϴ� �Լ�
void Console_GoToXY(int x, int y) {
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


int KeyInput(void) {
	int KeyNow;
	int x = 20; //ó�� ���� ��ġ x��
	int y = 10; //ó�� ���� ��ġ y��

	Console_GoToXY(x, y);
	
	BlockPrint();
	while (1) {
		// _kbhit�� Ű�� ���� ��� 0�� �ƴ� ���� ��ȯ�Ѵ�.
		if (_kbhit()) {
			KeyNow = _getch();

			if (KeyNow == SPACEBAR) {
				printf("SPACEBAR�� �Է¹޾ҽ��ϴ�.\n");
			}
			// ����Ű�� �ƽ�Ű�ڵ� �� Ȯ��Ű�̴�. 2����Ʈ�� �ΰ��� ���� �ް� ù��° 224, �ι�°�� Up,Down,Left,Right�� ���� �ٸ� ������ �޾ƿ´�.  
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
				printf("��");
			}
		}
	}
}



