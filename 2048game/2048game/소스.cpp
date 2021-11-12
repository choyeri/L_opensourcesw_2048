#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>		//exit �Լ� ���
#include <conio.h>		//_kbhit, _getch �Լ� ���

//����Ű ����
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int score = 0;	// ����
int board[4][4] = { 0 };
int buffer[4][4] = { 0 };		//board�� ���� ��Ȳ ���� ����

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

void init_Board()		//���� ����
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
	printf("���� : %d\n", score);
}

void print_board()			//������ ������ ���� ���� ��� �Լ�
{
	
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
	if (cnt != 0) {
		*p0[rand() % (cnt)] = ((rand() % 100) < 80) ? 2 : 4;			// 2 �Ǵ� 4�� ����
	}
}

void check_Gameover()	//���ӿ��� üũ�ϴ� �Լ�
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

void check_Inputkey()		//����Ű �Է¹޴� �Լ�
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

void slide_Board(char inputkey)		//����Ű�� ���� �����̴� �Լ�
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