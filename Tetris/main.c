#pragma warning(disable:4996)
#pragma warning(disable: 4819)

#include <stdio.h>
#include "Function.h"

int main(void) {

	CursorView(false, 1);
	blockform = CreateRandomForm();
	blockform_next = CreateRandomForm();
	bool Gameover = true;
	while (Gameover == true) {

		BoardPrint();
		system("cls");
		BlockPrint();
		DropBlock();
		removeline();
		KeyInput();
		Gameover = Check_Gameover();
	}

	BoardPrint();
	Sleep(200);
	system("cls");
	printf("GameOver!");
	Sleep(2000);
	return 0;
}