#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "Blocks.h"
#include "Board.h"
#include "KeyBoard.h"

void draw_block() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Block[blockform][blockRotation][i][j] == 2) {
				Console_GoToXY(x + j * 2, y + i);
				printf("");
			}
		}
	}
}
