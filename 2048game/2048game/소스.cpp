#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

int score = 0;	// ����
int board[4][4] = { 0 };

void print_board();
void get_num();
void check_Gameover();
void slide_score();

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

void check_Gameover()
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

void slide_score()
{

}

int main()
{
	get_num();
	get_num();
	print_board();
}