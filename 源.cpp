//2022/5/3
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<windows.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;
#define BLOCK_A 27
#define WIDTH 648
#define HIGTH 648

//#define A1 -4.500158825082766
//#define A2 3.4181268101392694
//#define A3 -3.2178882868487753
//#define A4 -9.348695305445199
//#define A5 -7.899265427351652
//#define A6 -3.3855972247263626

#define A1 -4.500158825082766
#define A2 3.4181268101392694
#define A3 -3.2178882868487753
#define A4 -9.348695305445199
#define A5 -7.899265427351652
#define A6 -3.3855972247263626

class blocks
{
public:
	int block[4][4];

};

void InitInterface();
void HideCursor();
void CursorJump();
void Rotate(int m, int n);
void InitTypes();
void drawblocks(int x, int y, int type1, int type2);
void GetType();
void Move();
void Cover(int x, int y, int type1, int type2);
void MoveDown();
void RenewType();
void JudgeScore();
void drawlatts();
void coverlatts(int m);
bool JudgeGG();
void DrawNext(int x, int y, int type1, int type2);
void JudgeReplay();
void ReadMax();
void WriteMax();
int Play();
void AIMove();
void AIMoveDown();
void AITry();
void FindHigh();
double Variance();
void FindHollow(int i, int j);
void VirtualEliminate();

void CalLandingHeight(int virtualnowy, int virtualnowtype2, int i1, int j1);
void CalEnrodedPieceCells(int virtualnowy, int virtualnowtype2, int i1, int j1);
void CalRowTransitions(int virtualnowy, int virtualnowtype2, int i1, int j1);
void CalColumnTransitions(int virtualnowy, int virtualnowtype2, int i1, int j1);
void CalNumberofHoles(int virtualnowy, int virtualnowtype2, int i1, int j1);
void CalWellSum(int virtualnowy, int virtualnowtype2, int i1, int j1);
void CalTot(int virtualnowy, int virtualnowtype2, int i1, int j1);
void InirPriority();

int AIPlay();





int latt[28][12];
int virtuallatt[28][12];
blocks types[7][4];
int newtype1, newtype2;
int nowtype1, nowtype2, nowx = 4, nowy;
int sleeptime;
int nowscore;
char Score[100];
int Max;
char Maxonscreen[100];
int Hollow[4][15];

double LandingHeight[4][15];
int	EnrodedPieceCells[4][15];
int RowTransitions[4][15];
int ColumnTransitions[4][15];
int NumberofHoles[4][15];
int WellSum[4][15];

double tot[4][15];
int Priority[4][15];

int keyleft;
int keyright;
int keydown;
int keyspace;



void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; //????????????????????????
	curInfo.dwSize = 1; //????????????????????????????
	curInfo.bVisible = FALSE; //??????????????????
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //??????????????
	SetConsoleCursorInfo(handle, &curInfo); //????????????
}
void CursorJump(int x, int y)
{
	COORD pos; //????????????????????????
	pos.X = x; //??????
	pos.Y = y; //??????
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //??????????????
	SetConsoleCursorPosition(handle, pos); //????????????
}
void InitInterface() {
	initgraph(WIDTH, HIGTH);
	int a = 12 * BLOCK_A;
	int b = a + 12;
	int c = HIGTH * (1.0 / 3);
	solidrectangle(a, 0, b, 648);
	solidrectangle(a, c, 648, c + 12);
	TCHAR s[] = _T("??????");
	outtextxy(a + (WIDTH - a) / 2 - 18, 12, s);
	TCHAR a1[] = _T("????????");
	outtextxy(a + (WIDTH - a) / 2 - 18, c + 15 + 12, a1);
	TCHAR a2[] = _T("????????");
	outtextxy(a + (WIDTH - a) / 2 - 18, c + 15 + 12 + 45, a2);
	TCHAR a3[] = _T("????????");
	outtextxy(a + (WIDTH - a) / 2 - 18, c + 15 + 12 + 45 * 2, a3);
	TCHAR a4[] = _T("??????????");
	outtextxy(a + (WIDTH - a) / 2 - 18, c + 15 + 12 + 45 * 3, a4);
	TCHAR a5[] = _T("????: S");
	outtextxy(a + (WIDTH - a) / 2 - 18, c + 15 + 12 + 45 * 4, a5);
	TCHAR a6[] = _T("????: Esc");
	outtextxy(a + (WIDTH - a) / 2 - 18, c + 15 + 12 + 45 * 5, a6);
	TCHAR a7[] = _T("????????:R");
	outtextxy(a + (WIDTH - a) / 2 - 18, c + 15 + 12 + 45 * 6, a7);
	TCHAR a8[] = _T("????????:");
	outtextxy(a + (WIDTH - a) / 2 - 18, c + 15 + 12 + 45 * 7, a8);
	TCHAR a9[] = _T("????????:");
	outtextxy(a + (WIDTH - a) / 2 - 18, c + 15 + 12 + 45 * 8, a9);

	setfillcolor(RGB(125, 46, 65));
	for (int i = 0; i < 24; i++)
		for (int j = 0; j < 12; j++)
			fillrectangle(j * BLOCK_A, i * BLOCK_A, (j + 1) * BLOCK_A, (i + 1) * BLOCK_A);
	ReadMax();
	sprintf(Maxonscreen, "????????:%d", Max);
	outtextxy(a + (WIDTH - a) / 2 - 18, c + 15 + 12 + 45 * 7, Maxonscreen);


}
void drawblocks(int x, int y, int type1, int type2) {

	setfillcolor(RGB(151, 255, 255));
	for (int i = y; i < y + 4; i++)
		for (int j = x; j < x + 4; j++)
		{
			if ((latt[i][j] == 0) && (types[type1][type2].block[i - y][j - x] == 2))
			{
				fillrectangle(j * BLOCK_A, (i - 4) * BLOCK_A, (j + 1) * BLOCK_A, (i - 3) * BLOCK_A);
				latt[i][j] = 2;
			}
		}
}
void InitTypes() {
	for (int j = 0; j < 3; j++)
		types[0][0].block[1][j] = 2;
	types[0][0].block[2][1] = 2;//0

	for (int i = 1; i < 4; i++)
		types[1][0].block[i][1] = 2;
	types[1][0].block[3][2] = 2;//L

	for (int i = 1; i < 4; i++)
		types[2][0].block[i][2] = 2;
	types[2][0].block[3][1] = 2;//??L

	for (int j = 0; j < 2; j++)
		types[3][0].block[1][j] = 2;
	for (int j = 1; j < 3; j++)
		types[3][0].block[2][j] = 2;

	for (int j = 1; j < 3; j++)
		types[4][0].block[1][j] = 2;
	for (int j = 0; j < 2; j++)
		types[4][0].block[2][j] = 2;

	for (int j = 1; j < 3; j++)
		types[5][0].block[1][j] = 2;
	for (int j = 1; j < 3; j++)
		types[5][0].block[2][j] = 2;

	for (int i = 0; i < 4; i++)
		types[6][0].block[i][1] = 2;


	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 3; j++)
			Rotate(i, j);
}
void Rotate(int m, int n)
{
	blocks temp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			temp.block[j][3 - i] = types[m][n].block[i][j];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			types[m][n + 1].block[i][j] = temp.block[i][j];
}
void GetType() {
	//srand((unsigned)time(NULL));
	newtype1 = rand() % 7;
	//srand((unsigned)time(NULL));
	newtype2 = rand() % 4;
}
void Move() {
	if ((GetAsyncKeyState(VK_LEFT) && 0x8000))
	{
		int count = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if ((types[nowtype1][nowtype2].block[i][j] == 2) && (nowx + j - 1 >= 0) && (latt[nowy + i][nowx + j - 1] != 1))
					count++;
		if (count == 4) {
			Cover(nowx, nowy, nowtype1, nowtype2);
			nowx--;
			drawblocks(nowx, nowy, nowtype1, nowtype2);
		}

	}

	if ((GetAsyncKeyState(VK_RIGHT) && 0x8000))
	{
		int count = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if ((types[nowtype1][nowtype2].block[i][j] == 2) && (nowx + j + 1 <= 11) && (latt[nowy + i][nowx + j + 1] != 1))
					count++;
		if (count == 4) {
			Cover(nowx, nowy, nowtype1, nowtype2);
			nowx++;
			drawblocks(nowx, nowy, nowtype1, nowtype2);
		}

	}
	if ((GetAsyncKeyState(VK_SPACE) && 0x8000)) {
		int count = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if ((types[nowtype1][(nowtype2 + 1) % 4].block[i][j] == 2) && (nowx + j <= 11) && (latt[nowy + i][nowx + j] != 1)
					&& (nowx + j >= 0) && (nowy + i <= 27) && (nowy + i >= 0))
					count++;
		if (count == 4) {
			Cover(nowx, nowy, nowtype1, nowtype2);
			nowtype2 = (nowtype2 + 1) % 4;
			drawblocks(nowx, nowy, nowtype1, nowtype2);
		}

	}
	if ((GetAsyncKeyState(VK_DOWN) && 0x8000)) {
		sleeptime = 50;

	}





}
void Cover(int x, int y, int type1, int type2) {
	setfillcolor(RGB(125, 46, 65));
	for (int i = y; i < y + 4; i++)
		for (int j = x; j < x + 4; j++)
		{
			if ((latt[i][j] == 2) && (types[type1][type2].block[i - y][j - x] == 2))
			{
				fillrectangle(j * BLOCK_A, (i - 4) * BLOCK_A, (j + 1) * BLOCK_A, (i - 3) * BLOCK_A);
				latt[i][j] = 0;
			}
		}
}
void MoveDown() {
	int count = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if ((types[nowtype1][nowtype2].block[i][j] == 2) && (nowy + i + 1 <= 27) && (latt[nowy + i + 1][nowx + j] != 1))
				count++;
	if (count == 4) {
		Cover(nowx, nowy, nowtype1, nowtype2);
		nowy++;
		drawblocks(nowx, nowy, nowtype1, nowtype2);
	}
	//??????????????
	int flag = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if ((types[nowtype1][nowtype2].block[i][j] == 2) && ((nowy + i == 27) || (latt[nowy + i + 1][nowx + j] == 1)))
				flag = 1;//?????????????????????? end
	Move();//?????????? ????????????????????????
	if (flag == 1) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (types[nowtype1][nowtype2].block[i][j] == 2) latt[nowy + i][nowx + j] = 1;
		RenewType();
		GetType();
		setfillcolor(RGB(151, 255, 255));
		DrawNext(12 * BLOCK_A + (WIDTH - 12 * BLOCK_A) / 2 - 18 - 28, 12 + 6 + 24, newtype1, newtype2);
		nowx = 4;
		nowy = 0;
	}
}
void RenewType() {
	nowtype1 = newtype1;
	nowtype2 = newtype2;
}
void JudgeScore() {
	for (int i = 27; i >= 4; i--) {
		int count = 0;
		for (int j = 0; j <= 11; j++)
			if (latt[i][j] == 1) count++;
		if (count == 12) {
			nowscore += 10;
			coverlatts(i);
			for (int j = 0; j <= 11; j++)
				latt[i][j] = 0;
			for (int k = i - 1; k >= 4; k--)
				for (int j = 0; j <= 11; j++)
					latt[k + 1][j] = latt[k][j];

			//????????????????????????????????????????
			drawlatts();
		}
	}
	sprintf(Score, "??????????%d", nowscore);
	outtextxy(12 * BLOCK_A + (WIDTH - 12 * BLOCK_A) / 2 - 18, HIGTH * (1.0 / 3) + 15 + 12 + 45 * 8, Score);

}
void drawlatts() {
	for (int i = 4; i <= 27; i++)
		for (int j = 0; j <= 11; j++)
			if (latt[i][j] == 1) {
				setfillcolor(RGB(151, 255, 255));
				fillrectangle(j * BLOCK_A, (i - 4) * BLOCK_A, (j + 1) * BLOCK_A, (i - 3) * BLOCK_A);
			}
}
void coverlatts(int m) {
	for (int i = m; i >= 4; i--)
		for (int j = 0; j <= 11; j++) {
			/*if (latt[i][j] == 1) {
				setfillcolor(RGB(125, 46, 65));
				fillrectangle(j * BLOCK_A, i * BLOCK_A, (j + 1) * BLOCK_A, (i + 1) * BLOCK_A);
			}*/
			setfillcolor(RGB(125, 46, 65));
			fillrectangle(j * BLOCK_A, (i - 4) * BLOCK_A, (j + 1) * BLOCK_A, (i - 3) * BLOCK_A);
		}
}//cover ??draw??????????????latt??i????????????????i-4??????????????
bool JudgeGG() {
	for (int j = 0; j <= 11; j++)
	{
		if (latt[4][j] == 1) return TRUE;
	}
	return FALSE;
}
void DrawNext(int x, int y, int type1, int type2) {
	setfillcolor(RGB(0, 0, 0));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			fillrectangle(x + j * BLOCK_A, y + i * BLOCK_A, x + (j + 1) * BLOCK_A, y + (i + 1) * BLOCK_A);
		}
	setfillcolor(RGB(151, 255, 255));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (types[type1][type2].block[i][j] == 2)
				fillrectangle(x + j * BLOCK_A, y + i * BLOCK_A, x + (j + 1) * BLOCK_A, y + (i + 1) * BLOCK_A);
		}
}//????????????????????????????????ij????????
void JudgeReplay() {
	if (GetAsyncKeyState(82) && 0X8000) {
		nowx = 4; nowy = 0;
		setfillcolor(RGB(125, 46, 65));
		for (int i = 0; i < 24; i++)
			for (int j = 0; j < 12; j++)
				fillrectangle(j * BLOCK_A, i * BLOCK_A, (j + 1) * BLOCK_A, (i + 1) * BLOCK_A);
		for (int i = 0; i < 28; i++)
			for (int j = 0; j < 12; j++)
				latt[i][j] = 0;
		nowscore = 0;
		sprintf(Score, "??????????%d", nowscore);
		outtextxy(12 * BLOCK_A + (WIDTH - 12 * BLOCK_A) / 2 - 18, HIGTH * (1.0 / 3) + 15 + 12 + 45 * 8, Score);

		ReadMax();
		sprintf(Maxonscreen, "????????:%d", Max);
		outtextxy(12 * BLOCK_A + (WIDTH - 12 * BLOCK_A) / 2 - 18, HIGTH * (1.0 / 3) + 15 + 12 + 45 * 7, Maxonscreen);

		GetType();
		RenewType();
		GetType();
		DrawNext(12 * BLOCK_A + (WIDTH - 12 * BLOCK_A) / 2 - 18 - 28, 12 + 6 + 24, newtype1, newtype2);
	}
}
void ReadMax() {
	FILE* pf = fopen("??????????????????.txt", "r");
	if (pf == NULL) {
		pf = fopen("??????????????????.txt", "w");
		fwrite(&nowscore, sizeof(int), 1, pf);
	}
	fseek(pf, 0, SEEK_SET);
	fread(&Max, sizeof(int), 1, pf);
	fclose(pf);
	pf = NULL;
}
void WriteMax() {
	FILE* pf = fopen("??????????????????.txt", "w");
	if (pf == NULL) {
		printf("??????????????????\n");
		exit(0);
	}
	fwrite(&nowscore, sizeof(int), 1, pf);
	fclose(pf);
	pf = NULL;
}
int Play() {
	srand((unsigned)time(NULL));
	system("TITLE ??????????");
	HideCursor();
	InitInterface();
	InitTypes();
	GetType();
	RenewType();
	GetType();
	setfillcolor(RGB(151, 255, 255));
	DrawNext(12 * BLOCK_A + (WIDTH - 12 * BLOCK_A) / 2 - 18 - 28, 12 + 6 + 24, newtype1, newtype2);
	while (1) {
		JudgeReplay();
		if (GetAsyncKeyState(VK_ESCAPE) && 0X8000) return 0;
		if (GetAsyncKeyState(83) && 0X8000) system("pause>nul");
		sleeptime = 150;
		MoveDown();
		//Move();
		JudgeScore();
		drawblocks(nowx, nowy, nowtype1, nowtype2);

		if (JudgeGG()) {
			//system("pause");
			cleardevice();
			printf("YOU LOSE!\n");
			printf("????????????%d\n", nowscore);
			WriteMax();
			//??????????
			return 0;
		}

		Sleep(sleeptime);

	}

	system("pause");
	return 0;
}
void AIMove() {
	if ((keyspace > 0)) {
		int count = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if ((types[nowtype1][(nowtype2 + 1) % 4].block[i][j] == 2) && (nowx + j <= 11) && (latt[nowy + i][nowx + j] != 1)
					&& (nowx + j >= 0) && (nowy + i <= 27) && (nowy + i >= 0))
					count++;
		if (count == 4) {
			Cover(nowx, nowy, nowtype1, nowtype2);
			nowtype2 = (nowtype2 + 1) % 4;
			drawblocks(nowx, nowy, nowtype1, nowtype2);
		}
		keyspace--;
	}
	if ((keyleft > 0))
	{
		int count = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if ((types[nowtype1][nowtype2].block[i][j] == 2) && (nowx + j - 1 >= 0) && (latt[nowy + i][nowx + j - 1] != 1))
					count++;
		if (count == 4) {
			Cover(nowx, nowy, nowtype1, nowtype2);
			nowx--;
			drawblocks(nowx, nowy, nowtype1, nowtype2);
		}
		keyleft--;
	}

	if ((keyright > 0))
	{
		int count = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if ((types[nowtype1][nowtype2].block[i][j] == 2) && (nowx + j + 1 <= 11) && (latt[nowy + i][nowx + j + 1] != 1))
					count++;
		if (count == 4) {
			Cover(nowx, nowy, nowtype1, nowtype2);
			nowx++;
			drawblocks(nowx, nowy, nowtype1, nowtype2);
		}
		keyright--;
	}

	if ((keydown == 1)) {
		sleeptime = 50;
		keydown = 0;
	}
}
void AIMoveDown() {
	int count = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if ((types[nowtype1][nowtype2].block[i][j] == 2) && (nowy + i + 1 <= 27) && (latt[nowy + i + 1][nowx + j] != 1))
				count++;
	if (count == 4) {
		Cover(nowx, nowy, nowtype1, nowtype2);
		nowy++;
		drawblocks(nowx, nowy, nowtype1, nowtype2);
	}
	//??????????????
	int flag = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if ((types[nowtype1][nowtype2].block[i][j] == 2) && ((nowy + i == 27) || (latt[nowy + i + 1][nowx + j] == 1)))
				flag = 1;//?????????????????????? end
	AIMove();//?????????? ????????????????????????
	if (flag == 1) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (types[nowtype1][nowtype2].block[i][j] == 2) latt[nowy + i][nowx + j] = 1;
		RenewType();
		GetType();
		setfillcolor(RGB(151, 255, 255));
		DrawNext(12 * BLOCK_A + (WIDTH - 12 * BLOCK_A) / 2 - 18 - 28, 12 + 6 + 24, newtype1, newtype2);
		nowx = 4;
		nowy = 0;
	}
}
double Variance() {
	double ave = 0;
	int max[12];
	for (int i = 0; i < 12; i++) max[i] = 24;
	for (int i = 0; i < 12; i++)
		for (int j = 4; j < 28; j++)
		{
			if (virtuallatt[j][i] == 1 || latt[j][i] == 1) {
				max[i] = j - 4; break;//??????????????????
			}
		}
	for (int i = 0; i < 12; i++)
	{
		ave += max[i];
	}
	ave = ave / 12.0;
	double var = 0.0;
	for (int i = 0; i < 12; i++)
	{
		var += (max[i] - ave) * (max[i] - ave);
	}
	var = var / 12.0;
	return var;
}
void FindHollow(int i, int j) {
	int count = 0;
	for (int m = 5; m < 28; m++)
		for (int n = 0; n < 12; n++)
		{
			if ((latt[m][n] == 0 && virtuallatt[m][n] == 0) && (virtuallatt[m - 1][n] == 1)) {
				count++;
			}
		}
	Hollow[i][j] = count;
}

void CalLandingHeight(int virtualnowy, int virtualnowtype2, int i1, int j1) {
	int up = 0, down = 0;
	int  flag1 = 0, flag2 = 0;
	for (int i = 24 - virtualnowy; i > 24 - virtualnowy - 4; i--) {
		for (int j = 0; j < 4; j++)
		{
			if (types[nowtype1][virtualnowtype2].block[24 - virtualnowy - i][j] == 2)
			{
				up = i;
				flag1 = 1;
				break;
			}

		}
		if (flag1 == 1) break;
	}
	for (int i = 27; i > 3; i--) {
		for (int j = 0; j < 12; j++)
		{
			if (virtuallatt[i][j] == 1)
			{
				down = 28 - i;
				flag2 = 1;
				break;
			}
		}
		if (flag2 == 1)break;;
	}
	LandingHeight[i1][j1] = (up + down) / 2.0;
}
//??????????????????????
void CalEnrodedPieceCells(int virtualnowy, int virtualnowtype2, int i1, int j1) {
	int ans[24];
	int row = 0;
	int block = 0;
	int j = 0, count = 0;
	for (int i = 4; i < 28; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (latt[i][j] != 1 && virtuallatt[i][j] != 1) {
				break;
			}
		}
		if (j == 12) { row++; ans[count++] = i; }
	}
	for (int i = 0; i < count; i++)
	{
		for (int m = 0; m < 12; m++)
		{
			if (virtuallatt[ans[i]][m] == 1)block++;
		}
	}
	EnrodedPieceCells[i1][j1] = row * block;
}
void VirtualEliminate() {
	for (int i = 4; i < 28; i++)
		for (int j = 0; j < 12; j++)
		{
			if (latt[i][j] == 1) virtuallatt[i][j] = 1;
		}

	for (int i = 27; i >= 4; i--) {
		int count = 0;
		for (int j = 0; j <= 11; j++)
			if (virtuallatt[i][j] == 1) count++;
		if (count == 12) {
			for (int j = 0; j <= 11; j++)
				virtuallatt[i][j] = 0;
			for (int k = i - 1; k >= 4; k--)
				for (int j = 0; j <= 11; j++)
					virtuallatt[k + 1][j] = virtuallatt[k][j];

		}
	}
}
void CalRowTransitions(int virtualnowy, int virtualnowtype2, int i1, int j1) {
	int trans[24];
	memset(trans, 0, sizeof(trans));
	for (int i = 4; i < 28; i++)
	{
		if (virtuallatt[i][0] == 0) trans[i - 4]++;
		if (virtuallatt[i][11] == 0) trans[i - 4]++;
		for (int j = 0; j < 11; j++) {
			if ((virtuallatt[i][j] == 1) && (virtuallatt[i][j + 1] == 0))trans[i - 4]++;
			if ((virtuallatt[i][j] == 0) && (virtuallatt[i][j + 1] == 1))trans[i - 4]++;
		}
	}
	for (int i = 0; i < 24; i++)
	{
		RowTransitions[i1][j1] += trans[i];
	}
}
void CalColumnTransitions(int virtualnowy, int virtualnowtype2, int i1, int j1) {
	int trans[12];
	memset(trans, 0, sizeof(trans));
	for (int i = 0; i < 12; i++)
	{
		trans[i]++;
		if (virtuallatt[27][i] == 0)trans[i]++;
		for (int j = 0; j < 27; j++)
		{
			if ((virtuallatt[j][i] == 1) && (virtuallatt[j + 1][i] == 0))trans[i]++;
			if ((virtuallatt[j][i] == 0) && (virtuallatt[j + 1][i] == 1))trans[i]++;
		}

	}
	for (int i = 0; i < 12; i++)
	{
		ColumnTransitions[i1][j1] += trans[i];
	}
}
void CalNumberofHoles(int virtualnowy, int virtualnowtype2, int i1, int j1) {
	int hole[12];
	memset(hole, 0, sizeof(hole));
	for (int i = 0; i < 12; i++)
	{
		for (int j = 4; j < 27; j++)
		{
			if ((virtuallatt[j][i] == 1) && (virtuallatt[j + 1][i] != 0))
				hole[i]++;
		}
	}
	for (int i = 0; i < 12; i++)
	{
		NumberofHoles[i1][j1] += hole[i];
	}
}
void CalWellSum(int virtualnowy, int virtualnowtype2, int i1, int j1) {
	int well[12];
	int sum[24];//????????????????
	memset(well, 0, sizeof(well));

	memset(sum, 0, sizeof(sum));
	for (int j = 4; j < 28; j++)
	{
		if ((virtuallatt[j][0] == 0) && (virtuallatt[j][1] == 1))
		{
			if (j == 4) sum[0] = 1;
			if (j > 4) { sum[j - 4] += sum[j - 5]; }
		}
	}
	for (int j = 4; j < 28; j++)
		well[0] += sum[j - 4];

	memset(sum, 0, sizeof(sum));
	for (int j = 4; j < 28; j++)
	{
		if ((virtuallatt[j][11] == 0) && (virtuallatt[j][10] == 1))
		{
			if (j == 4) sum[0] = 1;
			if (j > 4) { sum[j - 4] += sum[j - 5]; }
		}
	}
	for (int j = 4; j < 28; j++)
		well[11] += sum[j - 4];

	for (int i = 1; i < 11; i++) {
		memset(sum, 0, sizeof(sum));
		for (int j = 4; j < 28; j++)
		{
			if ((virtuallatt[j][i] == 0) && (virtuallatt[j][i + 1] == 1)
				&& (virtuallatt[j][i - 1] == 1))
			{
				if (j == 4) sum[0] = 1;
				if (j > 4) { sum[j - 4] += sum[j - 5]; }
			}
		}
		for (int j = 4; j < 28; j++)
			well[i] += sum[j - 4];
	}
	for (int i = 0; i < 12; i++)
		WellSum[i1][j1] += well[i];
}
void CalTot(int virtualnowy, int virtualnowtype2, int i1, int j1) {
	tot[i1][j1] = A1 * LandingHeight[i1][j1] + A2 * EnrodedPieceCells[i1][j1] + A3 * RowTransitions[i1][j1]
		+ A4 * ColumnTransitions[i1][j1] + A5 * NumberofHoles[i1][j1] + A6 * WellSum[i1][j1];
}

void InirPriority() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 15; j++)
		{
			Priority[i][j] = 100 * abs(j - 3 - nowx) + 10 * i;
		}
}

void FindHigh() {
	if (nowy != 0) return;
	if (keyleft != 0 || keyright != 0 || keyspace != 0) return;
	/*int high;
	int flag=0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (types[nowtype1][nowtype2].block[i][j] == 2)
			{
				high = i;
				flag = 1;
				break;
			}
		}
		if (flag == 1) break;
	}*/
	//for(int i=0;i<4;i++)
	//	for (int j = 0; j < 15; j++)
	//	{
	//		Hollow[i][j] = 500;
	//	}
	memset(Hollow, 500, sizeof(Hollow));
	double var[4][15];
	double temp[60];
	int temp2[60];
	memset(var, 100.0, sizeof(var));
	int virtualnowx = nowx;
	int virtualnowy = nowy;
	int virtualnowtype2 = nowtype2;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 15; j++)
		{
			virtualnowtype2 = (nowtype2 + i) % 4;
			virtualnowx = j;//????????????????????????????????????
			int flag = 0;
			for (int a = 0; a < 4; a++) {
				for (int b = 0; b < 4; b++)
				{
					if (types[nowtype1][virtualnowtype2].block[a][b] == 2 && j - 3 + b < 0) {
						flag = 1; break;
					}
					if (types[nowtype1][virtualnowtype2].block[a][b] == 2 && j - 3 + b > 11) {
						flag = 1; break;
					}
				}
				if (flag == 1) break;
			}
			if (flag == 1) continue;
			int down[4], up[4], delta[4];
			for (int k = 0; k < 4; k++)
			{
				down[k] = 24; up[k] = 0; delta[k] = 24;
			}

			for (int k = virtualnowx - 3; k < virtualnowx - 3 + 4; k++)
			{
				if (k < 0 || k>11) continue;
				for (int m = 4; m < 28; m++)
				{
					if (latt[m][k] == 1)
					{
						down[k - virtualnowx + 3] = m - 4; break;
					}
				}
				for (int m = 3; m >= 0; m--)
				{
					if (types[nowtype1][virtualnowtype2].block[m][k - virtualnowx + 3] == 2)
					{
						up[k - virtualnowx + 3] = m;
						break;
					}
				}
				delta[k - virtualnowx + 3] = down[k - virtualnowx + 3] - up[k - virtualnowx + 3];
			}
			sort(delta, delta + 4);
			virtualnowy = 0 + delta[0] - 1;
			for (int m = virtualnowy; m < virtualnowy + 4; m++)
				for (int n = virtualnowx - 3; n < virtualnowx - 3 + 4; n++)//??????virtualnowx-3!!!!!!
				{
					if (n < 0 || n>11) continue;
					if (types[nowtype1][virtualnowtype2].block[m - virtualnowy][n - virtualnowx + 3] == 2)
					{
						virtuallatt[m + 4][n] = 1;
					}
				}
			//????????????????????????????????????????????
			var[i][j] = Variance();
			FindHollow(i, j);

			CalLandingHeight(virtualnowy, virtualnowtype2, i, j);
			CalEnrodedPieceCells(virtualnowy, virtualnowtype2, i, j);
			VirtualEliminate();
			CalRowTransitions(virtualnowy, virtualnowtype2, i, j);
			CalColumnTransitions(virtualnowy, virtualnowtype2, i, j);
			CalNumberofHoles(virtualnowy, virtualnowtype2, i, j);
			CalWellSum(virtualnowy, virtualnowtype2, i, j);
			CalTot(virtualnowy, virtualnowtype2, i, j);

			memset(virtuallatt, 0, sizeof(virtuallatt));
		}
	int k = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 15; j++)
		{
			if (tot[i][j] != 0)
				temp[k++] = tot[i][j];//????????
		}
	sort(temp, temp + k);
	int ansi = 0, ansj = 0, MinHollow = 500, MinPriority = 1000;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 15; j++)
		{
			if (tot[i][j] == temp[k - 1])//????????
			{
				/*if (Hollow[i][j] == 0) {
					ansi = i;
					ansj = j;
					memset(Hollow, 500, 60);
					keyspace = ansi;
					if (ansj - 3 > nowx) keyright = ansj - 3 - nowx;
					if (ansj - 3 < nowx) keyleft = nowx - ansj + 3;
					memset(var, 0, sizeof(var));
					return;
				}*/

				/*if (Hollow[i][j] <MinHollow) {
					ansi = i;
					ansj = j;
					MinHollow = Hollow[i][j];
				}*/

				if (Priority[i][j] < MinPriority) {
					ansi = i;
					ansj = j;
					MinPriority = Priority[i][j];
				}

				/*keyspace = i;
				if (j - 3 > nowx) keyright = j - 3 - nowx;
				if (j - 3 < nowx) keyleft = nowx - j + 3;
				memset(var, 0, sizeof(var));
				memset(LandingHeight, 0, sizeof(LandingHeight));
				memset(EnrodedPieceCells, 0, sizeof(EnrodedPieceCells));
				memset(RowTransitions, 0, sizeof(RowTransitions));
				memset(ColumnTransitions, 0, sizeof(ColumnTransitions));
				memset(NumberofHoles, 0, sizeof(NumberofHoles));
				memset(WellSum, 0, sizeof(WellSum));
				memset(tot, 0, sizeof(tot));
				return;*/
			}
		}
	//for (int i = 0; i < 4; i++)
	//	for (int j = 0; j < 15; j++)
	//	{
	//		Hollow[i][j] = 500;
	//	}
	memset(Hollow, 500, sizeof(Hollow));
	memset(LandingHeight, 0, sizeof(LandingHeight));
	memset(EnrodedPieceCells, 0, sizeof(EnrodedPieceCells));
	memset(RowTransitions, 0, sizeof(RowTransitions));
	memset(ColumnTransitions, 0, sizeof(ColumnTransitions));
	memset(NumberofHoles, 0, sizeof(NumberofHoles));
	memset(WellSum, 0, sizeof(WellSum));
	memset(tot, 0, sizeof(tot));
	keyspace = ansi;
	if (ansj - 3 > nowx) keyright = ansj - 3 - nowx;
	if (ansj - 3 < nowx) keyleft = nowx - ansj + 3;
	memset(var, 0, sizeof(var));
	return;

}


int AIPlay() {
	InirPriority();
	srand((unsigned)time(NULL));
	system("TITLE ??????????");
	HideCursor();
	InitInterface();
	InitTypes();
	GetType();
	RenewType();
	GetType();
	setfillcolor(RGB(151, 255, 255));
	DrawNext(12 * BLOCK_A + (WIDTH - 12 * BLOCK_A) / 2 - 18 - 28, 12 + 6 + 24, newtype1, newtype2);
	while (1) {
		JudgeReplay();
		if (GetAsyncKeyState(VK_ESCAPE) && 0X8000) return 0;
		if (GetAsyncKeyState(83) && 0X8000) system("pause>nul");
		sleeptime = 10;

		FindHigh();
		AIMoveDown();
		//Move();
		JudgeScore();
		drawblocks(nowx, nowy, nowtype1, nowtype2);

		if (JudgeGG()) {
			//system("pause");
			printf("YOU LOSE!\n");
			printf("????????????%d\n", nowscore);
			WriteMax();
			return 0;
		}

		Sleep(sleeptime);

	}

	system("pause");
	return 0;
}
void AITry() {

}










int main() {
	printf("????????PLAY??????AI??");
	string choice;
	getline(cin, choice);
	while (1) {
		if (choice != "PLAY" && choice != "AI") {
			printf("????????PLAY??????AI??");
			choice = '/0';
			getline(cin, choice);
		}
		if (choice == "PLAY") {
			Play();
			return 0;
		}
		if (choice == "AI") {
			AIPlay();
			return 0;
		}
	}



}
//GG??escape????????pause