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
int buffer_Score = 0;
int board[4][4] = { 0 };
int buffer[4][4] = { 0 };		//board의 이전 상황 저장 변수

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
				printf(" .   ");
			else
				printf(" %d   ", board[i][j]);
		}
		printf("\n");
	}
	gotoxy(0,15);
	printf("점수 : %d\n", score);
}

void print_Board()			//깜빡임 방지를 위한 보드 출력 함수
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
	printf("점수 : %d\n", score);
	buffer_Score = score;
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
	int dir[4][2] = {		//같은 숫자가 있는지 검사할 방향을 저장한 배열
		0,-1,
		0,1,
		1,0,
		-1,0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++) {
				int dy = i + dir[k][0];	//배열의 x좌표
				int dx = j + dir[k][1];	//배열의 y좌표

				if (dy < 0 || dy > 3 || dx < 0 || dx > 3)	//0<=dx<=3, 0<=dy<=3이 아닐 때
					continue;		//아래 코드 건너뜀

				if (board[dy][dx] == 0 || board[dy][dx] == board[i][j])	//0이 남아있거나 아직 움직일 수 있을 때
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

	if (_kbhit()) {		//현재 키보드 입력을 받은 상태이면
		c = _getch();		//방향키는 2byte로 이루어져 있는데 하나만 먼저 받아옴
		if (c == -32) {			//방향키의 아스키코드 값이면
			c = _getch();		//다시 방향키의 아스키코드값 받아옴
			slide_Board(c);
			get_num();
		}
	}
}

void slide_Board(char inputkey)		//방향키에 따라 움직이는 함수
{
	int i, j, k;

	switch (inputkey) {
	case LEFT:
		for (i = 0; i < 4; i++) {		//0-3행
			for (j = 1; j <=3; j++) {		//1-3열
				for (k = j; k > 0; k--) {	//k값에 j값 복사하여 넣고 값을 끝까지 밀어줌
					if (board[i][k] == 0)	//현재 값이 0이라면
						break;
					if (board[i][k - 1] != 0 && board[i][k] != board[i][k - 1])	//왼쪽 값과 현재 값이 다르다면
						break;
					if (board[i][k - 1] == 0)	//왼쪽값이 0이라면
						board[i][k - 1] = board[i][k];
					else if (board[i][k] == board[i][k - 1]) {	//왼쪽값과 현재 값이 같다면
						board[i][k - 1] *= 2;
						score += 2 * board[i][k];
					}
					board[i][k] = 0;	//현재 값에 0 넣음
				}
			}
		}break;
	case RIGHT:
		for (i = 0; i < 4; i++) {		//0-3행
			for (j = 2; j >=0; j--) {		//0-2열
				for (k = j; k < 3; k++) {	//k값에 j값 복사하여 넣고 배열 안의 값을 끝까지 밀어줌
					if (board[i][k] == 0)	//현재 값이 0이라면
						break;
					if (board[i][k + 1] != 0 && board[i][k] != board[i][k + 1])	//오른쪽 값과 현재 값이 다르다면
						break;
					if (board[i][k + 1] == 0)	//오른쪽 값이 0이라면
						board[i][k + 1] = board[i][k];
					else if (board[i][k] == board[i][k + 1]) {	//오른쪽 값과 현재 값이 같다면
						board[i][k + 1] *= 2;
						score += 2 * board[i][k];
					}
					board[i][k] = 0;	//현재 값에 0 넣음
				}
			}
		}break;
	case UP:
		for (j = 0; j < 4; j++) {		//0-3열
			for (i = 1; i <=3; i++) {		//1-3행
				for (k = i; k > 0; k--) {	//k값에 j값 복사하여 넣고 배열 안의 값을 끝까지 밀어줌
					if (board[k][j] == 0)	//현재 값이 0이라면
						break;
					if (board[k-1][j] != 0 && board[k][j] != board[k - 1][j])	//아래쪽 값과 현재 값이 다르다면
						break;
					if (board[k - 1][j] == 0)	//아래쪽 값이 0이라면
						board[k - 1][j] = board[k][j];
					else if (board[k][j] == board[k - 1][j]) {	//아래쪽 값과 현재 값이 같다면
						board[k - 1][j] *= 2;
						score += 2 * board[k][j];
					}
					board[k][j] = 0;	//현재값에 0 넣음
				}
			}
		}break;
	case DOWN:
		for (j = 0; j < 4; j++) {		//0-3열
			for (i = 2; i >=0; i--) {		//0-2행
				for (k = i; k < 3; k++) {	//k값에 j값 복사하여 넣고 값을 끝까지 밀어줌
					if (board[k][j] == 0)	//현재 값이 0이라면
						break;
					if (board[k + 1][j] != 0 && board[k][j] != board[k + 1][j])		//위쪽 값과 현재 값이 다르다면
						break;
					if (board[k + 1][j] == 0)	//위쪽 값이 0이라면
						board[k + 1][j] = board[k][j];
					else if (board[k][j] == board[k + 1][j]) {	//위쪽 값과 현재 값이 같다면
						board[k + 1][j] *= 2;
						score += 2 * board[k][j];
					}
					board[k][j] = 0;	//현재 값에 0 넣음
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