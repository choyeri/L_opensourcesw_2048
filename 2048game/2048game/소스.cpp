#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>		//exit 함수 사용
#include <conio.h>		//_kbhit, _getch 함수 사용

//방향키 설정
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int score = 0;	// 점수
int board[4][4] = { 0 };
int buffer[4][4] = { 0 };		//board의 이전 상황 저장 변수

void print_board();
void get_num();
void check_Gameover();
void slide_Board(char inputkey);
void check_Inputkey();
void gotoxy();
void init_Board();

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void init_Board()		//보드 생성
{
	system("cls");

	printf("play the 2048 game!\n\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			gotoxy(j * 6, (i + 1) * 3);
			if (board[i][j] == 0)
				printf(" .");
			else
				printf(" %d", board[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	printf("점수 : %d\n", score);
}

void print_board()			//깜빡임 방지를 위한 보드 출력 함수
{
	
}

void get_num()				// 보드에 랜덤으로 2 또는 4를 나타나게 하는 함수
{
	int i, j, cnt;
	int* p0[16] = { 0 };

	cnt = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
			if (board[i][j] == 0)
			{
				p0[cnt] = &board[i][j];
				cnt++;
			}
	}
	if (cnt != 0) {
		*p0[rand() % (cnt)] = ((rand() % 100) < 80) ? 2 : 4;			// 2 또는 4를 만듦
	}
}

void check_Gameover()	//게임오버 체크하는 함수
{
	int dir[4][2] = {
		0,-1,
		0,1,
		1,0,
		-1,0 };


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++) {
				int dy = i + dir[k][0];
				int dx = j + dir[k][1];

				if (dy < 0 || dy > 3 || dx < 0 || dx > 3)
					continue;

				if (board[dy][dx] == 0 || board[dy][dx] == board[i][j])
					return;
			}
		}
	}

	printf("Game Over");
	
	exit(0);

}

void check_Inputkey()		//방향키 입력받는 함수
{		
	char c;

	if (_kbhit()) {
		c = _getch();
		if (c == -32) {
			c = _getch();
			slide_Board(c);
			get_num();
		}
	}
}

void slide_Board(char inputkey)		//방향키에 따라 움직이는 함수
{
	int i, j;
	
	for (int k = 0; k < 3; k++) {		
		switch (inputkey) {
		case LEFT:
			for (i = 0; i < 4; i++) {
				for (j = 3; j >= 1; j--) {
					if (board[i][j - 1] != 0) {
						if (board[i][j] == board[i][j - 1]) {
							board[i][j - 1] *= 2;
							score += 2 * board[i][j];
							board[i][j] = 0;
						}
					}
					else {
						board[i][j - 1] = board[i][j];
						board[i][j] = 0;
					}
				}
			}

			break;
		case RIGHT:
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 3; j++) {
					if (board[i][j + 1] != 0) {
						if (board[i][j] == board[i][j + 1]) {
							board[i][j + 1] *= 2;
							score += 2 * board[i][j];
							board[i][j] = 0;
						}
					}
					else {
						board[i][j + 1] = board[i][j];
						board[i][j] = 0;
					}
				}
			}
			break;
		case UP:
			for (j = 0; j < 4; j++) {
				for (i = 3; i >= 1; i--) {
					if (board[i - 1][j] != 0) {
						if (board[i][j] == board[i - 1][j]) {
							board[i - 1][j] *= 2;
							score += 2 * board[i][j];
							board[i][j] = 0;
						}
					}
					else {
						board[i - 1][j] = board[i][j];
						board[i][j] = 0;
					}
				}
			}
			break;
		case DOWN:
			for (j = 0; j < 4; j++) {
				for (i = 0; i < 3; i++) {
					if (board[i + 1][j] != 0) {
						if (board[i][j] == board[i + 1][j]) {
							board[i + 1][j] *= 2;
							score += 2 * board[i][j];
							board[i][j] = 0;
						}
					}
					else {
						board[i + 1][j] = board[i][j];
						board[i][j] = 0;
					}
				}
			}
			break;
		}
	}
}

int main()
{
	get_num();
	get_num();
	while(1) {
		check_Inputkey();
		print_board();
		check_Gameover();
	}
}