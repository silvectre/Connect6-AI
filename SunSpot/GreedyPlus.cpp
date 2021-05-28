#include <vector>
#include <algorithm>
#include "Data.cpp"
#include "TwoPieces.h"
//#define _CUT1_
//#define _CUT2_
//#define _TWO_
#define _TOTAL_ 35
#define _PART_
#define _EXTEND_ 5
#define _SELECT_ 121
#define _MAXWIDTH_ 7
#define _MINWIDTH_ 5
unsigned char _WIDTH_ = 11;
unsigned char _DEEPTH_ = 11;
//#define _RAND_
#define _CENTREFACTOR_ 1
void InitBoard();
//#define _TEST_
using namespace std;
extern unsigned short int is_white;
extern pair<pair<short int, short int>, pair<short int, short int>> other;
extern short int board[19][19];
unsigned char CharBoard[29][29];
int GetScorePlus(unsigned const char Board[29][29], unsigned short int PiecesNum, unsigned short int IsAI);
void TestBoard();
pair<pair<short int, short int>, pair<short int, short int>>GreedyPlus(unsigned short int IsAI);
pair<pair<short int, short int>, pair<short int, short int>>GreedyPlusCut(unsigned short int IsAI);
bool IfInTwo(unsigned char Board[29][29], unsigned char Y, unsigned char X);
bool is_gameover(const short int board[19][19], pair<pair<short int, short int>, pair<short int, short int>> just, unsigned short int the_color);
int GetScorePart(unsigned char Board[29][29], unsigned short int PiecesNum, unsigned short int IsAI,
				unsigned short int y1, unsigned short int x1, unsigned short int y2, unsigned short int x2);
void GetPos(unsigned char CharBoard[29][29], unsigned short int PiecesNum, unsigned short int IsAI,
				unsigned short Num, vector<TwoBlank>& Ans);
bool is_gameover_char(unsigned const char board[29][29], register char y1, register char x1, register char y2, register char x2, register unsigned char the_color);
void TestBoard() {
	InitBoard();
	//遇到程序没有按照自己意想落子的时候在此输入局面信息进行Debug
}

pair<pair<short int, short int>, pair<short int, short int>>GreedyPlus(unsigned short int IsAI) {
#ifdef _TEST_
	//TestBoard();
#endif
	pair<pair<short int, short int>, pair<short int, short int>> ans;
	unsigned short int Num = ColorHash[IsAI];
	bool (*vis)[19][19][19] = new bool[19][19][19][19]{};
	int score = -99999999;
	int k = 1;
	for (int y1 = 0; y1 < 19; ++y1)
		for (int x1 = 0; x1 < 19; ++x1)
			for (int y2 = 0; y2 < 19; ++y2)
				for (int x2 = 0; x2 < 19; ++x2) {
					if (!(y1 == y2 && x1 == x2)
						&& !vis[y1][x1][y2][x2] && !vis[y2][x2][y1][x1]
						&& CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] == 0
						&& CharBoard[y2 + _EXTEND_][x2 + _EXTEND_] == 0
						&& IfInTwo(CharBoard, y1 + _EXTEND_, x1 + _EXTEND_)
						&& IfInTwo(CharBoard, y2 + _EXTEND_, x2 + _EXTEND_)) {
						vis[y1][x1][y2][x2] = true;
						vis[y2][x2][y1][x1] = true;
						CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = Num;
						CharBoard[y2 + _EXTEND_][x2 + _EXTEND_] = Num;
#ifdef _PART_	
						int the_score = GetScorePart(CharBoard, false, IsAI, y1, x1, y2, x2);
#else
						int the_score = GetScorePlus(CharBoard, false, IsAI);
#endif
						the_score += CentreHash[y1][x1];
						the_score += CentreHash[y2][x2];
						//int the_score = get_score(board, is_white);
						if (the_score > score) {
							ans.first.first = y1;
							ans.first.second = x1;
							ans.second.first = y2;
							ans.second.second = x2;
							score = the_score;
						}
#ifdef _RAND_
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
#endif
						CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = 0;
						CharBoard[y2 + _EXTEND_][x2 + _EXTEND_] = 0;
					}
				}
	delete[]vis;
	return ans;
}


pair<pair<short int, short int>, pair<short int, short int>>GreedyPlusCut(unsigned short int IsAI) {
	pair<pair<short int, short int>, pair<short int, short int>> ans;
	vector<OneBlank>Pieces;
	unsigned short int Num = ColorHash[IsAI];
	bool(*vis)[19][19][19] = new bool[19][19][19][19]{};
	int score = -99999999;
	int k = 1;
	for (int y1 = 0; y1 < 19; ++y1)
		for (int x1 = 0; x1 < 19; ++x1) {
			if (CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] == 0
				&& IfInTwo(CharBoard, y1 + _EXTEND_, x1 + _EXTEND_)) {
				CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = Num;
				int the_score = GetScorePlus(CharBoard, true, IsAI);
				the_score += CentreHash[y1][x1];
				Pieces.push_back(OneBlank(the_score, make_pair(short(y1), short(x1))));
				CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = 0;
				}
			}
	sort(Pieces.begin(), Pieces.end());
	if (Pieces.size() > _SELECT_)
		Pieces.erase(Pieces.begin() + _SELECT_, Pieces.end());
	for (auto& Temp : Pieces) {
		CharBoard[Temp.Pos.first + _EXTEND_][Temp.Pos.second + _EXTEND_] = Num;
		for (int y1 = 0; y1 < 19; ++y1)
			for (int x1 = 0; x1 < 19; ++x1) {
				if (CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] == 0
					&& IfInTwo(CharBoard, y1 + _EXTEND_, x1 + _EXTEND_)
					&& !vis[y1][x1][Temp.Pos.first][Temp.Pos.second]) {
					CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = Num;
					vis[y1][x1][Temp.Pos.first][Temp.Pos.second] = true;
					vis[Temp.Pos.first][Temp.Pos.second][y1][x1] = true;
					int the_score = GetScorePlus(CharBoard, false, IsAI);
					the_score += CentreHash[y1][x1];
					the_score += CentreHash[Temp.Pos.first][Temp.Pos.second];
					if (the_score > score) {
						ans.first = Temp.Pos;
						ans.second = make_pair(y1, x1);
						score = the_score;
					}
#ifdef _RAND_
					else if (the_score == score) {
						if (rand() % 1000 * k <= 1000) {
							ans.first = Temp.Pos;
							ans.second = make_pair(y1, x1);
							score = the_score;
						}
						++k;
					}
#endif
					CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = 0;
				}
			}
		CharBoard[Temp.Pos.first + _EXTEND_][Temp.Pos.second + _EXTEND_] = 0;
	}
	delete[]vis;
	return ans;
}


pair<pair<short int, short int>, pair<short int, short int>>GreedyPlusTwo(unsigned short int IsAI) {
	pair<pair<short int, short int>, pair<short int, short int>> ans;
	short int Num = ColorHash[IsAI];
	int score = -99999999;
	int k = 1;
	for (int y1 = 0; y1 < 19; ++y1)
		for (int x1 = 0; x1 < 19; ++x1) {
			if (CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] == 0
				&& IfInTwo(CharBoard, y1 + _EXTEND_, x1 + _EXTEND_)) {
				CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = Num;
				int the_score = GetScorePlus(CharBoard, true, IsAI);
				the_score += CentreHash[y1][x1];
				if (the_score > score) {
					ans.first = make_pair(y1, x1);
					score = the_score;
				}
#ifdef _RAND_
				else if (the_score == score) {
					if (rand() % 1000 * k <= 1000) {
						ans.first = make_pair(y1, x1);
						score = the_score;
					}
					++k;
				}
#endif
				CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = 0;
			}
		}
	score = -99999999;
	CharBoard[ans.first.first + _EXTEND_][ans.first.second + _EXTEND_] = Num;
		for (int y1 = 0; y1 < 19; ++y1)
			for (int x1 = 0; x1 < 19; ++x1) {
				if (CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] == 0
					&& IfInTwo(CharBoard, y1 + _EXTEND_, x1 + _EXTEND_)) {
					CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = Num;
					int the_score = GetScorePlus(CharBoard, false, IsAI);
					the_score += CentreHash[y1][x1];
					the_score += CentreHash[ans.first.first][ans.first.second];
					if (the_score > score) {
						ans.second = make_pair(y1, x1);
						score = the_score;
					}
#ifdef _RAND_
					else if (the_score == score) {
						if (rand() % 1000 * k <= 1000) {
							ans.second = make_pair(y1, x1);
							score = the_score;
						}
						++k;
					}
#endif
					CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = 0;
				}
			}
	CharBoard[ans.first.first + _EXTEND_][ans.first.second + _EXTEND_] = 0;
	return ans;
}

pair<pair<short int, short int>, pair<short int, short int>>GreedyPlusMax(unsigned short int IsAI) {
	static char Times = 0;
	_WIDTH_ = max(_MAXWIDTH_ - Times, _MINWIDTH_);
	_DEEPTH_ = _TOTAL_ / _WIDTH_ / 2 * 2 + 1;
	Times++;
	Times++;
#ifdef _TEST_
	TestBoard();
#endif

	pair<pair<short int, short int>, pair<short int, short int>> ans1;
	pair<pair<short int, short int>, pair<short int, short int>> ans2;
	pair<pair<short int, short int>, pair<short int, short int>> ans;
	vector<OneBlank>Pieces;
	vector<TwoBlank>TwoPieces;
	int score = -99999999;
	unsigned short int Num = ColorHash[IsAI];
	unsigned char MemoryBoard[29][29];
	int Step = 9999, Step2 = -9999;
	memcpy(MemoryBoard, CharBoard, sizeof(MemoryBoard));
	int k = 1;
#ifdef _CUT2_
	bool(*vis)[19][19][19] = new bool[19][19][19][19]{};
	for (int y1 = 0; y1 < 19; ++y1)
		for (int x1 = 0; x1 < 19; ++x1) {
			if (CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] == 0
				&& IfInTwo(CharBoard, y1 + _EXTEND_, x1 + _EXTEND_)) {
				CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = Num;
				int the_score = GetScorePlus(CharBoard, true, IsAI);
				the_score += CentreHash[y1][x1] * _CENTREFACTOR_;
				Pieces.push_back(OneBlank(the_score, make_pair(short(y1), short(x1))));
				CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = 0;
			}
		}
	sort(Pieces.begin(), Pieces.end());
	if (Pieces.size() > _SELECT_)
		Pieces.erase(Pieces.begin() + _SELECT_, Pieces.end());
	for (auto& Temp : Pieces) {
		CharBoard[Temp.Pos.first + _EXTEND_][Temp.Pos.second + _EXTEND_] = Num;
		for (int y1 = 0; y1 < 19; ++y1)
			for (int x1 = 0; x1 < 19; ++x1) {
				if (CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] == 0
					&& IfInTwo(CharBoard, y1 + _EXTEND_, x1 + _EXTEND_)
					&& !vis[y1][x1][Temp.Pos.first][Temp.Pos.second]) {
					vis[y1][x1][Temp.Pos.first][Temp.Pos.second] = true;
					vis[Temp.Pos.first][Temp.Pos.second][y1][x1] = true;
					CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = Num;
					int the_score = GetScorePlus(CharBoard, false, IsAI);
					the_score += CentreHash[y1][x1] * _CENTREFACTOR_;
					the_score += CentreHash[Temp.Pos.first][Temp.Pos.second] * _CENTREFACTOR_;
					TwoPieces.push_back(TwoBlank(the_score, make_pair(Temp.Pos, make_pair(y1, x1))));
					CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = 0;
				}
			}
		CharBoard[Temp.Pos.first + _EXTEND_][Temp.Pos.second + _EXTEND_] = 0;
		score = -99999999;
	}
	sort(TwoPieces.begin(), TwoPieces.end());
	delete[]vis;
#else
	bool(*vis)[19][19][19] = new bool[19][19][19][19]{};
	for (int y1 = 0; y1 < 19; ++y1)
		for (int x1 = 0; x1 < 19; ++x1)
			for (int y2 = 0; y2 < 19; ++y2)
				for (int x2 = 0; x2 < 19; ++x2) {
					if (!(y1 == y2 && x1 == x2)
						&& !vis[y1][x1][y2][x2] && !vis[y2][x2][y1][x1]
						&& CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] == 0
						&& CharBoard[y2 + _EXTEND_][x2 + _EXTEND_] == 0
						&& IfInTwo(CharBoard, y1 + _EXTEND_, x1 + _EXTEND_)
						&& IfInTwo(CharBoard, y2 + _EXTEND_, x2 + _EXTEND_)) {
						vis[y1][x1][y2][x2] = true;
						vis[y2][x2][y1][x1] = true;
						CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = Num;
						CharBoard[y2 + _EXTEND_][x2 + _EXTEND_] = Num;
						int the_score = GetScorePlus(CharBoard, false, IsAI);
						the_score += CentreHash[y1][x1];
						the_score += CentreHash[y2][x2];
						TwoPieces.push_back(TwoBlank(the_score, make_pair(make_pair(short(y1), short(x1)), make_pair(short(y2), short(x2)))));
						CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = 0;
						CharBoard[y2 + _EXTEND_][x2 + _EXTEND_] = 0;
					}
				}
	delete[]vis;
	sort(TwoPieces.begin(), TwoPieces.end());
#endif
	if (!TwoPieces.size())
		return make_pair(make_pair(-1, -1), make_pair(-1, -1));
	if (TwoPieces.begin()->Score > 50000000)
		return TwoPieces.begin()->Pos;
	if (TwoPieces.size() > _WIDTH_)
		TwoPieces.erase(TwoPieces.begin() + _WIDTH_, TwoPieces.end());
	for (auto& Temp : TwoPieces) {
		short int AI = 1;
		auto Coor = Temp.Pos;
		for (int D = 0; D < _DEEPTH_; ++D) {
			CharBoard[Coor.first.first + _EXTEND_][Coor.first.second + _EXTEND_] = ColorHash[AI];
			CharBoard[Coor.second.first + _EXTEND_][Coor.second.second + _EXTEND_] = ColorHash[AI];
			if (is_gameover_char(CharBoard, Coor.first.first + _EXTEND_, Coor.first.second + _EXTEND_, Coor.second.first + _EXTEND_, Coor.second.second + _EXTEND_,ColorHash[AI])) {
				if (AI != 0 && Step > D) {
					ans1 = Temp.Pos;
					Step = D;
					break;
				}
				else {
					Temp.Score = -99999999;
					if (D > Step2) {
						ans2 = Temp.Pos;
						Step2 = D;
					}
					break;
				}
			}
			AI = !AI;
#ifdef _CUT1_
			Coor = GreedyPlusCut(AI);
#else

#ifdef _TWO_
			Coor = GreedyPlusTwo(AI);
#else
			Coor = GreedyPlus(AI);
#endif

#endif
		}
		if(Temp.Score != -99999999)
		Temp.Score = GetScorePlus(CharBoard, 0, IsAI) + 
			CentreHash[Temp.Pos.first.first][Temp.Pos.first.second] +
			CentreHash[Temp.Pos.second.first][Temp.Pos.second.second];
		if (Temp.Score > score) {
			ans = Temp.Pos;
			score = Temp.Score;
		}
#ifdef _RAND_

		else if (Temp.Score == score) {
			if (rand() % 1000 * k <= 1000) {
				ans = Temp.Pos;
				score = Temp.Score;
			}
			++k;
		}
#endif
		memcpy(CharBoard, MemoryBoard, sizeof(MemoryBoard));
	}
	if (Step != 9999) {
		memcpy(CharBoard, MemoryBoard, sizeof(MemoryBoard));
		return ans1;
	}
	if (score == -99999999) {
		memcpy(CharBoard, MemoryBoard, sizeof(MemoryBoard));
		return ans2;
	}
	memcpy(CharBoard, MemoryBoard, sizeof(MemoryBoard));
	return ans;
}

void InitBoard() {
	memset(CharBoard, 46, sizeof(CharBoard));
	for (int j = 0; j < 19; ++j)
		for (int i = 0; i < 19; ++i)
			CharBoard[j + _EXTEND_][i + _EXTEND_] = 0;
}