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
int buffer_Score = 0;
int board[4][4] = { 0 };
int buffer[4][4] = { 0 };		//board�� ���� ��Ȳ ���� ����

void print_Board();
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
				printf(" .   ");
			else
				printf(" %d   ", board[i][j]);
		}
		printf("\n");
	}
	gotoxy(0,15);
	printf("���� : %d\n", score);
}

void print_Board()			//������ ������ ���� ���� ��� �Լ�
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] == buffer[i][j])
				continue;
			
			gotoxy(j * 6, (i + 1) * 3);

			if (board[i][j] == 0)
				printf(" .   ");
			else
				printf(" %d   ", board[i][j]);

				buffer[i][j] = board[i][j];
		}
	}

	if (buffer_Score == score)
		return;

	gotoxy(0, 15);
	printf("���� : %d\n", score);
	buffer_Score = score;
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
	int dir[4][2] = {		//���� ���ڰ� �ִ��� �˻��� ������ ������ �迭
		0,-1,
		0,1,
		1,0,
		-1,0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++) {
				int dy = i + dir[k][0];	//�迭�� x��ǥ
				int dx = j + dir[k][1];	//�迭�� y��ǥ

				if (dy < 0 || dy > 3 || dx < 0 || dx > 3)	//0<=dx<=3, 0<=dy<=3�� �ƴ� ��
					continue;		//�Ʒ� �ڵ� �ǳʶ�

				if (board[dy][dx] == 0 || board[dy][dx] == board[i][j])	//0�� �����ְų� ���� ������ �� ���� ��
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

	if (_kbhit()) {		//���� Ű���� �Է��� ���� �����̸�
		c = _getch();		//����Ű�� 2byte�� �̷���� �ִµ� �ϳ��� ���� �޾ƿ�
		if (c == -32) {			//����Ű�� �ƽ�Ű�ڵ� ���̸�
			c = _getch();		//�ٽ� ����Ű�� �ƽ�Ű�ڵ尪 �޾ƿ�
			slide_Board(c);
			get_num();
		}
	}
}

void slide_Board(char inputkey)		//����Ű�� ���� �����̴� �Լ�
{
	int i, j, k;

	switch (inputkey) {
	case LEFT:
		for (i = 0; i < 4; i++) {		//0-3��
			for (j = 1; j <=3; j++) {		//1-3��
				for (k = j; k > 0; k--) {	//k���� j�� �����Ͽ� �ְ� ���� ������ �о���
					if (board[i][k] == 0)	//���� ���� 0�̶��
						break;
					if (board[i][k - 1] != 0 && board[i][k] != board[i][k - 1])	//���� ���� ���� ���� �ٸ��ٸ�
						break;
					if (board[i][k - 1] == 0)	//���ʰ��� 0�̶��
						board[i][k - 1] = board[i][k];
					else if (board[i][k] == board[i][k - 1]) {	//���ʰ��� ���� ���� ���ٸ�
						board[i][k - 1] *= 2;
						score += 2 * board[i][k];
					}
					board[i][k] = 0;	//���� ���� 0 ����
				}
			}
		}break;
	case RIGHT:
		for (i = 0; i < 4; i++) {		//0-3��
			for (j = 2; j >=0; j--) {		//0-2��
				for (k = j; k < 3; k++) {	//k���� j�� �����Ͽ� �ְ� �迭 ���� ���� ������ �о���
					if (board[i][k] == 0)	//���� ���� 0�̶��
						break;
					if (board[i][k + 1] != 0 && board[i][k] != board[i][k + 1])	//������ ���� ���� ���� �ٸ��ٸ�
						break;
					if (board[i][k + 1] == 0)	//������ ���� 0�̶��
						board[i][k + 1] = board[i][k];
					else if (board[i][k] == board[i][k + 1]) {	//������ ���� ���� ���� ���ٸ�
						board[i][k + 1] *= 2;
						score += 2 * board[i][k];
					}
					board[i][k] = 0;	//���� ���� 0 ����
				}
			}
		}break;
	case UP:
		for (j = 0; j < 4; j++) {		//0-3��
			for (i = 1; i <=3; i++) {		//1-3��
				for (k = i; k > 0; k--) {	//k���� j�� �����Ͽ� �ְ� �迭 ���� ���� ������ �о���
					if (board[k][j] == 0)	//���� ���� 0�̶��
						break;
					if (board[k-1][j] != 0 && board[k][j] != board[k - 1][j])	//�Ʒ��� ���� ���� ���� �ٸ��ٸ�
						break;
					if (board[k - 1][j] == 0)	//�Ʒ��� ���� 0�̶��
						board[k - 1][j] = board[k][j];
					else if (board[k][j] == board[k - 1][j]) {	//�Ʒ��� ���� ���� ���� ���ٸ�
						board[k - 1][j] *= 2;
						score += 2 * board[k][j];
					}
					board[k][j] = 0;	//���簪�� 0 ����
				}
			}
		}break;
	case DOWN:
		for (j = 0; j < 4; j++) {		//0-3��
			for (i = 2; i >=0; i--) {		//0-2��
				for (k = i; k < 3; k++) {	//k���� j�� �����Ͽ� �ְ� ���� ������ �о���
					if (board[k][j] == 0)	//���� ���� 0�̶��
						break;
					if (board[k + 1][j] != 0 && board[k][j] != board[k + 1][j])		//���� ���� ���� ���� �ٸ��ٸ�
						break;
					if (board[k + 1][j] == 0)	//���� ���� 0�̶��
						board[k + 1][j] = board[k][j];
					else if (board[k][j] == board[k + 1][j]) {	//���� ���� ���� ���� ���ٸ�
						board[k + 1][j] *= 2;
						score += 2 * board[k][j];
					}
					board[k][j] = 0;	//���� ���� 0 ����
				}
			}
		}break;
	}
}

int main()
{
	get_num();
	get_num();
	init_Board();
	while(1) {
		check_Inputkey();
		print_Board();
		check_Gameover();
	}
}