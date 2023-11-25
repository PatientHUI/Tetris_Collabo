#pragma warning(disable:4996)
#pragma warning(disable: 4819)

#include <stdio.h>
#include "Function.h"

int main(void) {
	PlaySound(TEXT("C:\\TETRIS_bgm.wav"), 0, SND_ASYNC | SND_LOOP);
	CursorView(false, 1);
	title();
	blockform = CreateRandomForm();
	blockform_next = CreateRandomForm();
	bool check = true;
	while (check == true) {
		DrawScreen();
		ShowNextBlock();
		BoardPrint();
		system("cls");
		BlockPrint();
		DropBlock();
		removeline();
		KeyInput();
		check = Check_Gameover();
	}

	BoardPrint();
	Sleep(200);
	system("cls");
	gameover();
	return 0;
}