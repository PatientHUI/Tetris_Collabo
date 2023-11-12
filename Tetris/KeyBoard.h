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


int KeyInput(void) {
	int KeyNow;
	
	int x = BoardX + 2 * 5;
	int y = BoardY;
	gotoxy(x,y);
	//BlockPrint();

	while (1) {
		// _kbhit�� Ű�� ���� ��� 0�� �ƴ� ���� ��ȯ�Ѵ�.
		BoardPrint();

		if (_kbhit()) {
			KeyNow = _getch();

			if (KeyNow == SPACEBAR) {
				gotoxy(x, y);
				printf("x:%d y:%d", x, y);

			}
			// ����Ű�� �ƽ�Ű�ڵ� �� Ȯ��Ű�̴�. 2����Ʈ�� �ΰ��� ���� �ް� ù��° 224, �ι�°�� Up,Down,Left,Right�� ���� �ٸ� ������ �޾ƿ´�.  
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
				printf("��");
			}
		}
	}

}

void BoardPrint() {

	// ���� ����� �Ѱ輱 
	for (int x = 1; x < 13; x++) {
		//�ܼ�â�� x*2�� ��ĭ
		gotoxy(BoardX + x * 2, BoardY + 1);
		
		//printf("~");
		
	}

	// ���� �׵θ� ����
		
	for (int y = 0; y < B_HEIGHT; y++) {

		// ���� �׵θ�
		gotoxy(BoardX, BoardY + y-1);
		if (board[y][0] == 1) {
			textcolor(2);
			printf("��");
		}

		// ������ �׵θ�
		gotoxy(BoardX + B_WIDTH * 2 - 3, BoardY + y-1);
		if (board[y][B_WIDTH - 1] == 1) {
			textcolor(2);
			printf("��");
		}

	}

	// �Ʒ��� �׵θ�
	for (int x = 0; x < B_WIDTH; x++) {
		gotoxy(BoardX + x, BoardY +  B_HEIGHT -1 );
		
		if (board[B_HEIGHT - 1][x] == 1) {
			textcolor(2);
			printf("��");
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