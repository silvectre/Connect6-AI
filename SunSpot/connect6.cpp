#include<easyx.h>
#include<future>      
#include<utility> 
#include<windows.h>
#include<Mmsystem.h>
#include<graphics.h>
#include<ostream>
#include "Data.cpp"
#pragma comment(lib,"winmm.lib")
using namespace std;
extern unsigned short int is_white;
extern pair<pair<short int, short int>, pair<short int, short int>> other;
extern short int board[19][19];
extern unsigned char CharBoard[29][29];
extern const int(* ScoreHash)[2][2][256];
static IMAGE img[7];
static MOUSEMSG m;
static int Round = 1;
void InitBoard();
pair<pair<short int, short int>, pair<short int, short int>> AI;
bool is_gameover(const short int board[19][19], pair<pair<short int, short int>, pair<short int, short int>> just, unsigned short int the_color);
pair<pair<short int, short int>, pair<short int, short int>>Greedy(unsigned short int IsAI);
pair<pair<short int, short int>, pair<short int, short int>>GreedyPlus(unsigned short int IsAI);
pair<pair<short int, short int>, pair<short int, short int>>GreedyPlusCut(unsigned short int IsAI);
pair<pair<short int, short int>, pair<short int, short int>>Plugin(unsigned short int IsAI);
//pair<position, position> AlphaBate();
void SetWindows() {
	// 加载pic
	loadimage(&img[0], L"pic\\Blank.bmp");
	loadimage(&img[1], L"pic\\black_chess.png");
	loadimage(&img[2], L"pic\\white_chess.png");
	loadimage(&img[3], L"pic\\black_cross.png");
	loadimage(&img[4], L"pic\\white_cross.png");
	loadimage(&img[5], L"pic\\tip_box.png");
	//初始化棋盘
	initgraph(650, 650);
	IMAGE of_board;
	loadimage(&img[6], L"pic\\chess_map.png");
	putimage(0, 0, &img[6]);
//	setorigin(30, 30);
	SetWindowText(GetHWnd(), L"Connect6");
	int scrWidth, scrHeight;
	RECT rect;
	//获得屏幕尺寸
	scrWidth = GetSystemMetrics(SM_CXSCREEN);
	scrHeight = GetSystemMetrics(SM_CYSCREEN);
	//取得窗口尺寸
	GetWindowRect(GetHWnd(), &rect);
	//重新设置rect里的值
	rect.left = (scrWidth - rect.right) / 2;
	rect.top = (scrHeight - rect.bottom) / 2;
	SetWindowPos(GetHWnd(), HWND_TOP, rect.left, rect.top, 630, 650, SWP_SHOWWINDOW);
}


void drawAlpha(IMAGE* picture, int  picture_y, int picture_x) //x为载入图片的X坐标，y为Y坐标
{

	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}


void MarkLastMove(pair<pair<short int, short int>, pair<short int, short int>> Pos, bool Color) {
	drawAlpha(&img[1 + Color], Pos.first.first * 30 + 22, Pos.first.second * 30 + 22);
	drawAlpha(&img[1 + Color], Pos.second.first * 30 + 22, Pos.second.second * 30 + 22);
	drawAlpha(&img[4 - Color], Pos.first.first * 30 + 27, Pos.first.second * 30 + 27);
	drawAlpha(&img[4 - Color], Pos.second.first * 30 + 27, Pos.second.second * 30 + 27);
}


pair<pair<short int, short int>, pair<short int, short int>> HumanChoice(short int board[19][19]) {
	bool isFind;
	pair<pair<short int, short int>, pair<short int, short int>> ans;
	FILE* fp1 = fopen("test.txt", "a");
	while (true) {
		isFind = false;
		while (true) {
			m = GetMouseMsg();// 获取鼠标消息
			if (m.uMsg == WM_LBUTTONDOWN && m.x - 22 < 30 * 19 && m.y - 22 < 30 * 19)
				break;// 如果左键点击
		}
		int row = (m.y - 22) / 30, col = (m.x - 22) / 30;
		fprintf(fp1, "%d %d ", row, col);
		if (board[row][col] == -1) {
			fprintf(fp1, "\n");
			fprintf(fp1, "%d %d ", row, col);
			ans.first = make_pair(row, col);
			board[row][col] = !is_white;
			MarkLastMove(make_pair(ans.first, ans.first), !is_white);
			break;
		}
	}
	PlaySound(TEXT("pic\\002.wav"), NULL, SND_FILENAME | SND_ASYNC);
	fprintf(fp1, "\n");


	while (true) {
		isFind = false;
		while (true) {
			m = GetMouseMsg();// 获取鼠标消息
			if (m.uMsg == WM_LBUTTONDOWN && m.x - 22 < 30 * 19 && m.y - 22 < 30 * 19)
				break;// 如果左键点击
		}
		int row = (m.y - 22) / 30, col = (m.x - 22) / 30;
		fprintf(fp1, "%d %d ", row, col);
		if (board[row][col] == -1) {
			fprintf(fp1, "\n");
			fprintf(fp1, "%d %d ", row, col);
			ans.second = make_pair(row, col);
			board[row][col] = !is_white;
			MarkLastMove(make_pair(ans.second, ans.second), !is_white);
			break;
		}
	}
	PlaySound(TEXT("pic\\002.wav"), NULL, SND_FILENAME | SND_ASYNC);
	other.first = make_pair(ans.first.first, ans.first.second);
	other.second = make_pair(ans.second.first, ans.second.second);
	fclose(fp1);
	return ans;
}


void PrintBoard(short int board[19][19])
{
	for (int Row = 0; Row < 19; ++Row)
		for (int Col = 0; Col < 19; ++Col)
			switch (board[Row][Col]) {
			case 0:
				drawAlpha(&img[1], 30 * Row + 22, 30 * Col + 22);
				break;
			case 1:
				drawAlpha(&img[2], 30 * Row + 22, 30 * Col + 22);
				break;
			}
	PlaySound(TEXT("pic\\002.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

bool UCT_GamePlay() {
	InitBoard();
	is_white = MessageBox(GetHWnd(), L"是否使用黑子?", L"Game Start", MB_YESNO + 48) - 7 == 0 ? 0 : 1;
	if (is_white) {
		CharBoard[14][14] = 7;
		ScoreHash = ScoreHash2;
	}
	else {
		CharBoard[14][14] = 1;
		ScoreHash = ScoreHash1;
	}
	memset(board, -1, sizeof(board));
	board[9][9] = 1;
	putimage(0, 0, &img[6]);
	PrintBoard(board);
	while (true) {
		if (is_white) {//指AI
			HumanChoice(board);
			PrintBoard(board);
			if (is_gameover(board, other, !is_white))
				break;
			AI = Plugin(true);
			MarkLastMove(AI, is_white);
			if (is_gameover(board, AI, is_white))
				break;
		}		
		else {		
			PrintBoard(board);
			AI = Plugin(true);
			MarkLastMove(AI, is_white);
			if (is_gameover(board, AI, is_white))
				break;
			HumanChoice(board);
			if (is_gameover(board, other, !is_white))
				break;
		}
	}
	memset(board, -1, sizeof(board));
	IDYES == MessageBox(GetHWnd(), L"游戏结束", L"Game over", MB_YESNO | MB_ICONQUESTION);
	return 0;
}