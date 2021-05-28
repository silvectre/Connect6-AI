#include <cmath>
#include <vector>
#include <ctime>
using namespace std;
unsigned short int is_white;
pair<pair<short int, short int>, pair<short int, short int>> other = make_pair(make_pair(9, 9), make_pair(9, 9));
short int board[19][19];
int get_score(short int board[19][19], unsigned short int color) {
	int score_enemy[7] = { 0, 0, 20, 200, 10000, 10000, 100000 };
	int score_self[7] = { 0, 0, 10, 100, 350, 350, 10000000 };
	int ans = 0, cnt1 = 0, cnt2 = 0;
	for (int k = 0; k < 4; ++k) {
		int movey, movex;
		switch (k) {
		case 0:movey = 0; movex = 1; break;
		case 1:movey = 1; movex = 0; break;
		case 2:movey = -1; movex = 1; break;
		case 3:movey = 1; movex = 1; break;
		default: break;
		}
		for (int y = 0; y <= 18; ++y) {
			for (int x = 0; x <= 18; ++x) {
				for (int n = 0; n < 6; ++n) {
					if (y + movey * n < 0 || y + movey * n > 18 || x + movex * n < 0 || x + movex * n > 18)
						break;
					else if (board[y + movey * n][x + movex * n] == -1)
						continue;
					else if (board[y + movey * n][x + movex * n] == color)
						++cnt1;
					else {
						cnt1 = 0;
						break;
					}
				}
				ans += score_self[cnt1];
				cnt1 = 0;
				for (int n = 0; n < 6; ++n) {
					if (y + movey * n < 0 || y + movey * n > 18 || x + movex * n < 0 || x + movex * n > 18)
						break;
					else if (board[y + movey * n][x + movex * n] == -1)
						continue;
					else if (board[y + movey * n][x + movex * n] != color)
						++cnt2;
					else {
						cnt2 = 0;
						break;
					}
				}
				ans -= score_enemy[cnt2];
				cnt2 = 0;
				if (board[y][x] == color) {
					ans -= abs(9 - x);
					ans -= abs(9 - y);
				}
			}
		}
	}
	return ans;
}


bool if_in_two(short int board[19][19], unsigned short int y, unsigned short int x) {
	for (int j = -2; j < 3; ++j)
		for (int i = -2; i < 3; ++i) {
			if (j + y < 0 || j + y > 18 || x + i < 0 || x + i > 18)
				continue;
			if (board[y + j][x + i] != -1)
				return true;
		}
	return false;
}



pair<pair<short int, short int>, pair<short int, short int>>Greedy(unsigned short int IsAI) {
	pair<pair<short int, short int>, pair<short int, short int>> ans;
	short int Sign = IsAI ? 1 : -1;
	bool Color = IsAI ? is_white : !is_white;
	int score = -99999999;
	int k = 1;
	for (int y1 = 0; y1 < 19; ++y1)
		for (int x1 = 0; x1 < 19; ++x1)
			for (int y2 = 0; y2 < 19; ++y2)
				for (int x2 = 0; x2 < 19; ++x2) {
					if (!(y1 == y2 && x1 == x2)
						&& board[y1][x1] == -1
						&& board[y2][x2] == -1
						&& if_in_two(board, y1, x1)
						&& if_in_two(board, y2, x2)) {
						board[y1][x1] = Color;
						board[y2][x2] = Color;
						int the_score = Sign * get_score(board, Color);
						//int the_score = get_score(board, is_white);
						if (the_score > score) {
							ans.first.first = y1;
							ans.first.second = x1;
							ans.second.first = y2;
							ans.second.second = x2;
							score = the_score;
						}
						else if (the_score == score) {
							if (rand() % 1000 * k <= 1000) {
								ans.first.first = y1;
								ans.first.second = x1;
								ans.second.first = y2;
								ans.second.second = x2;
								score = the_score;
							}
							++k;
						}
						board[y1][x1] = -1;
						board[y2][x2] = -1;
					}
				}
	return ans;
}


bool is_gameover(const short int board[19][19], pair<pair<short int, short int>, pair<short int, short int>> just, unsigned short int the_color) {
	int y, x, n = 1;
	for (int k = 0; k <= 1; ++k) {
		if (k == 0)
			y = just.first.first, x = just.first.second;
		else if (k == 1)
			y = just.second.first, x = just.second.second;
		for (int y2 = y + 1, x2 = x + 1;
			y2 <= 18 && x2 <= 18 && board[y2][x2] == the_color;
			++y2, ++x2, ++n);
		for (int y2 = y - 1, x2 = x - 1;
			y2 >= 0 && x2 >= 0 && board[y2][x2] == the_color;
			--y2, --x2, ++n);
		if (n >= 6) return true;
		n = 1;
		for (int y2 = y + 1, x2 = x - 1;
			y2 <= 18 && x2 >= 0 && board[y2][x2] == the_color;
			++y2, --x2, ++n);
		for (int y2 = y - 1, x2 = x + 1;
			y2 >= 0 && x2 <= 18 && board[y2][x2] == the_color;
			--y2, ++x2, ++n);
		if (n >= 6) return true;
		n = 1;
		for (int y2 = y + 1, x2 = x;
			y2 <= 18 && board[y2][x2] == the_color;
			++y2, ++n);
		for (int y2 = y - 1, x2 = x;
			y2 >= 0 && board[y2][x2] == the_color;
			--y2, ++n);
		if (n >= 6) return true;
		n = 1;
		for (int y2 = y, x2 = x - 1;
			x2 >= 0 && board[y2][x2] == the_color;
			--x2, ++n);
		for (int y2 = y, x2 = x + 1;
			x2 <= 18 && board[y2][x2] == the_color;
			++x2, ++n);
		if (n >= 6) return true;
		n = 1;
	}
	return false;
}


bool is_gameover_char(unsigned const char board[29][29], register char y1, register char x1, register char y2, register char x2, register unsigned char the_color) {
	register char y, x, n = 1;
	for (int k = 0; k <= 1; ++k) {
		if (k == 0)
			y = y1, x = x1;
		else if (k == 1)
			y = y2, x = x2;
		for (register int y2 = y + 1, x2 = x + 1; board[y2][x2] == the_color; ++y2, ++x2, ++n);
		for (register int y2 = y - 1, x2 = x - 1; board[y2][x2] == the_color; --y2, --x2, ++n);
		if (n >= 6) return true;
		n = 1;
		for (register int y2 = y + 1, x2 = x - 1; board[y2][x2] == the_color; ++y2, --x2, ++n);
		for (register int y2 = y - 1, x2 = x + 1; board[y2][x2] == the_color; --y2, ++x2, ++n);
		if (n >= 6) return true;
		n = 1;
		for (register int y2 = y + 1, x2 = x; board[y2][x2] == the_color; ++y2, ++n);
		for (register int y2 = y - 1, x2 = x; board[y2][x2] == the_color; --y2, ++n);
		if (n >= 6) return true;
		n = 1;
		for (register int y2 = y, x2 = x - 1; board[y2][x2] == the_color; --x2, ++n);
		for (register int y2 = y, x2 = x + 1; board[y2][x2] == the_color; ++x2, ++n);
		if (n >= 6) return true;
		n = 1;
	}
	return false;
}