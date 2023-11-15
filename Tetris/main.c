#pragma warning(disable:4996)
#include <stdio.h>
#include "Function.h"

int main() {
	CursorView(false, 1);
	blockform = CreateRandomForm();
	blockform_next = CreateRandomForm();
	startDropT = clock();
	while (true) {

		BoardPrint();
		system("cls");
		BlockPrint();
		KeyInput();


	}


}
