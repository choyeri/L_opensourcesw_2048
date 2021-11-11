#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>	//exit�Լ� ���
#include <conio.h>

//����Ű ����
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int score = 0;	// ����
int board[4][4] = { 0 };

void print_board();
void get_num();
void check_Gameover();
void slide_Board(char inputkey);
void check_Inputkey();

void print_board()			// ���带 ����� �Լ�
{
	system("cls");

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] == 0)
				printf(" .");
			else
				printf(" %d", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("���� : %d\n", score);
}

void get_num()				// ���忡 �������� 2 �Ǵ� 4�� ��Ÿ���� �ϴ� �Լ�
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
	*p0[rand() % (cnt)] = ((rand() % 100) < 80) ? 2 : 4;			// 2 �Ǵ� 4�� ����
}

void check_Gameover()	//���ӿ��� üũ�ϴ� �Լ�
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			if (board[i][j] == 0)
				return;
		}
	}

	system("cls");
	printf("Game Over");
	exit(0);
}

void check_Inputkey() {
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

void slide_Board(char inputkey)
{
	int i, j;

	switch (inputkey) {
	case LEFT:
		for (i = 0; i < 4; i++) {
			for (j = 3; j >= 1; j--) {
				if (board[i][j - 1] != 0) {
					if (board[i][j] == board[i][j - 1]) {
						board[i][j - 1] *= 2;
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
				if (board[i-1][j] != 0) {
					if (board[i][j] == board[i-1][j]) {
						board[i-1][j] *= 2;
						board[i][j] = 0;
					}
				}
				else {
					board[i-1][j] = board[i][j];
					board[i][j] = 0;
				}
			}
		}
		break;
	case DOWN:
		for (j = 0; j < 4; j++) {
			for (i = 0; i < 3; i++) {
				if (board[i+1][j] != 0) {
					if (board[i][j] == board[i+1][j]) {
						board[i+1][j] *= 2;
						board[i][j] = 0;
					}
				}
				else {
					board[i+1][j] = board[i][j];
					board[i][j] = 0;
				}
			}
		}
		break;
	}
}


int main()
{
	get_num();
	get_num();
	while(1) {
		print_board();
		check_Inputkey();
		check_Gameover();
	}
}