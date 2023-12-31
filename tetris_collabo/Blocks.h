#pragma once
#define Block_Kinds 7
#define Block_Size 4
#define Block_Rotation 4

/*
		0000
		0220
		0220
		0000
		처럼 총 4X4 블럭 사이즈 안에서 모양정의 및 회전.
*/

// 회전은 총 4가지 경우(중복이 되더라도 복잡함을 줄이기 위해 4번 회전으로 고정 사용)

// 블럭의 모양은 총 7가지이다.


int Block[Block_Kinds][Block_Rotation][Block_Size][Block_Size] = {
	// ㅁ모양블록 
	{
	0,0,0,0,
	0,2,2,0,
	0,2,2,0,
	0,0,0,0,

	0,0,0,0,
	0,2,2,0,
	0,2,2,0,
	0,0,0,0,

	0,0,0,0,
	0,2,2,0,
	0,2,2,0,
	0,0,0,0,

	0,0,0,0,
	0,2,2,0,
	0,2,2,0,
	0,0,0,0
	},
	// ㅡ모양 블록
	{
	0,0,0,0,
	0,0,0,0,
	2,2,2,2,
	0,0,0,0,

	0,2,0,0,
	0,2,0,0,
	0,2,0,0,
	0,2,0,0,

	0,0,0,0,
	0,0,0,0,
	2,2,2,2,
	0,0,0,0,

	0,2,0,0,
	0,2,0,0,
	0,2,0,0,
	0,2,0,0
	},
	// L모양 블록 (세로가 3, 가로가 2)
	{
	0,2,0,0,
	0,2,0,0,
	0,2,2,0,
	0,0,0,0,

	0,0,2,0,
	2,2,2,0,
	0,0,0,0,
	0,0,0,0,

	2,2,0,0,
	0,2,0,0,
	0,2,0,0,
	0,0,0,0,

	0,0,0,0,
	2,2,2,0,
	2,0,0,0,
	0,0,0,0
	},
	// ㄱ 모양 블록(세로가 2, 가로가 3)
	{
	0,0,0,0,
	2,2,2,0,
	0,0,2,0,
	0,0,0,0,

	0,2,2,0,
	0,2,0,0,
	0,2,0,0,
	0,0,0,0,

	2,0,0,0,
	2,2,2,0,
	0,0,0,0,
	0,0,0,0,

	0,2,0,0,
	0,2,0,0,
	2,2,0,0,
	0,0,0,0
	},
	// Z 그대로 
	{
	0,0,0,0,
	0,2,2,0,
	0,0,2,2,
	0,0,0,0,

	0,0,0,2,
	0,0,2,2,
	0,0,2,0,
	0,0,0,0,

	0,0,0,0,
	0,2,2,0,
	0,0,2,2,
	0,0,0,0,

	0,0,0,2,
	0,0,2,2,
	0,0,2,0,
	0,0,0,0,

	},
	// Z 거울반전
	{
	0,0,0,0,
	0,2,2,0,
	2,2,0,0,
	0,0,0,0,

	0,0,0,0,
	2,0,0,0,
	2,2,0,0,
	0,2,0,0,

	0,0,0,0,
	0,2,2,0,
	2,2,0,0,
	0,0,0,0,

	0,0,0,0,
	2,0,0,0,
	2,2,0,0,
	0,2,0,0,
	},
	// ㅗ모양블록 
	{
	0, 0, 0, 0,
	0, 0, 2, 0,
	0, 2, 2, 2,
	0, 0, 0, 0,

	0, 0, 0, 0,
	0, 0, 2, 0,
	0, 2, 2, 0,
	0, 0, 2, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 2, 2, 2,
	0, 0, 2, 0,

	0, 0, 0, 0,
	0, 0, 2, 0,
	0, 0, 2, 2,
	0, 0, 2, 0
	}
};