#include "Data.cpp"
#include <cmath>
#include <algorithm>
#include "TwoPieces.h"
#include <vector>
using namespace std;
const int _EXTEND_ = 5;
double _FACTOR_;
extern unsigned short int is_white;
const int(* ScoreHash)[2][2][256];
int GetScorePlus(unsigned const char Board[29][29], unsigned short int PiecesNum, unsigned short int IsAI) {
	if (is_white)
		_FACTOR_ = 0.8;
	unsigned char Cnt1 = 0,//己方
		Cnt2 = 0;//敌方
	int Ans = 0;
	unsigned short int Num1 = ColorHash[1], Num0 = ColorHash[0];
	for (int Y = 0; Y <= 18; ++Y) {
		for (int i = 0; i <= 5; ++i) {
			Cnt1 += Board[Y + _EXTEND_][i + _EXTEND_];
			Cnt2 += Board[Y + _EXTEND_][i + _EXTEND_];
		}for (int X = 0; X <= 13; ++X) {
			Ans += ScoreHash[1][PiecesNum][IsAI][Cnt1];
			Ans += ScoreHash[0][PiecesNum][IsAI][Cnt2];
			Cnt1 -= Board[Y + _EXTEND_][X + _EXTEND_];
			Cnt1 += Board[Y + _EXTEND_][X + 6 + _EXTEND_];
			Cnt2 -= Board[Y + _EXTEND_][X + _EXTEND_];
			Cnt2 += Board[Y + _EXTEND_][X + 6 + _EXTEND_];
		}
		Cnt1 = 0; Cnt2 = 0;
	}


	for (int X = 0; X <= 18; ++X) {
		for (int i = 0; i <= 5; ++i) {
			Cnt1 += Board[i + _EXTEND_][X + _EXTEND_];
			Cnt2 += Board[i + _EXTEND_][X + _EXTEND_];
		}for (int Y = 0; Y <= 13; ++Y) {
			Ans += ScoreHash[1][PiecesNum][IsAI][Cnt1];
			Ans += ScoreHash[0][PiecesNum][IsAI][Cnt2];
			Cnt1 -= Board[Y + _EXTEND_][X + _EXTEND_];
			Cnt1 += Board[Y + 6 + _EXTEND_][X + _EXTEND_];
			Cnt2 -= Board[Y + _EXTEND_][X + _EXTEND_];
			Cnt2 += Board[Y + 6 + _EXTEND_][X + _EXTEND_];
		}
		Cnt1 = 0; Cnt2 = 0;
	}


	for (int Y = 0; Y <= 13; ++Y) {
		for (int i = 0; i <= 5; ++i) {
			Cnt1 += Board[Y + i + _EXTEND_][i + _EXTEND_];
			Cnt2 += Board[Y + i + _EXTEND_][i + _EXTEND_];
		}for (int X = 0; X + Y <= 13; ++X) {
			Ans += ScoreHash[1][PiecesNum][IsAI][Cnt1];
			Ans += ScoreHash[0][PiecesNum][IsAI][Cnt2];
			Cnt1 -= Board[Y + X + _EXTEND_][X + _EXTEND_];
			Cnt1 += Board[Y + X + 6 + _EXTEND_][X + 6 + _EXTEND_];
			Cnt2 -= Board[Y + X + _EXTEND_][X + _EXTEND_];
			Cnt2 += Board[Y + X + 6 + _EXTEND_][X + 6 + _EXTEND_];
		}
		Cnt1 = 0; Cnt2 = 0;
	}


	for (int X = 1; X <= 13; ++X) {
		for (int i = 0; i <= 5; ++i) {
			Cnt1 += Board[i + _EXTEND_][X + i + _EXTEND_];
			Cnt2 += Board[i + _EXTEND_][X + i + _EXTEND_];
		}for (int Y = 0; Y + X <= 13; ++Y) {
			Ans += ScoreHash[1][PiecesNum][IsAI][Cnt1];
			Ans += ScoreHash[0][PiecesNum][IsAI][Cnt2];
			Cnt1 -= Board[Y + _EXTEND_][Y + X + _EXTEND_];
			Cnt1 += Board[Y + 6 + _EXTEND_][Y + X + 6 + _EXTEND_];
			Cnt2 -= Board[Y + _EXTEND_][Y + X + _EXTEND_];
			Cnt2 += Board[Y + 6 + _EXTEND_][Y + X + 6 + _EXTEND_];
		}
		Cnt1 = 0; Cnt2 = 0;
	}


	for (int X = 1; X <= 13; ++X) {
		for (int i = 0; i <= 5; ++i) {
			Cnt1 += Board[18 - i + _EXTEND_][X + i + _EXTEND_];
			Cnt2 += Board[18 - i + _EXTEND_][X + i + _EXTEND_];
		}for (int Y = 18; X + 5 <= Y; --Y) {
			Ans += ScoreHash[1][PiecesNum][IsAI][Cnt1];
			Ans += ScoreHash[0][PiecesNum][IsAI][Cnt2];
			Cnt1 -= Board[Y + _EXTEND_][X - Y + 18 + _EXTEND_];
			Cnt1 += Board[Y - 6 + _EXTEND_][X - Y + 24 + _EXTEND_];
			Cnt2 -= Board[Y + _EXTEND_][X - Y + 18 + _EXTEND_];
			Cnt2 += Board[Y - 6 + _EXTEND_][X - Y + 24 + _EXTEND_];
		}
		Cnt1 = 0; Cnt2 = 0;
	}


	for (int Y = 18; Y >= 5; --Y) {
		for (int i = 0; i <= 5; ++i) {
			Cnt1 += Board[Y - i + _EXTEND_][i + _EXTEND_];
			Cnt2 += Board[Y - i + _EXTEND_][i + _EXTEND_];
		}for (int X = 0; X + 5 <= Y; ++X) {
			Ans += ScoreHash[1][PiecesNum][IsAI][Cnt1];
			Ans += ScoreHash[0][PiecesNum][IsAI][Cnt2];
			Cnt1 -= Board[Y - X + _EXTEND_][X + _EXTEND_];
			Cnt1 += Board[Y - X - 6 + _EXTEND_][X + 6 + _EXTEND_];
			Cnt2 -= Board[Y - X + _EXTEND_][X + _EXTEND_];
			Cnt2 += Board[Y - X - 6 + _EXTEND_][X + 6 + _EXTEND_];
		}
		Cnt1 = 0; Cnt2 = 0;
	}
	return Ans;
}


int GetScorePart(unsigned char Board[29][29], unsigned short int PiecesNum, unsigned short int IsAI, unsigned short int y1,
	unsigned short int x1, unsigned short int y2, unsigned short int x2) {
	unsigned char Cnt1 = 0,//己方
		Cnt2 = 0;//敌方
	int Ans = 0;
	unsigned short int Num1 = ColorHash[IsAI], Num0 = ColorHash[!IsAI], Coory[2]{ y1, y2 }, Coorx[2]{ x1, x2 };
	for (int K = 0; K < 2; ++K) {
		int Y1 = Coory[K], X1 = Coorx[K];
		for (int X = 0; X <= 5; ++X)
			Cnt1 += Board[Y1 + _EXTEND_][X1 - X + _EXTEND_];
		for (int X = -5; X <= 0; ++X) {
			Ans += ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
			Cnt1 -= Board[Y1 + _EXTEND_][X1 + X + _EXTEND_];
			Cnt1 += Board[Y1 + _EXTEND_][X1 + X + 6 + _EXTEND_];
		}
		Cnt1 = 0;

		for (int Y = 0; Y <= 5; ++Y)
			Cnt1 += Board[Y1 - Y + _EXTEND_][X1 + _EXTEND_];
		for (int Y = -5; Y <= 0; ++Y) {
			Ans += ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
			Cnt1 -= Board[Y1 + Y + _EXTEND_][X1 + _EXTEND_];
			Cnt1 += Board[Y1 + Y + 6 + _EXTEND_][X1 + _EXTEND_];
		}
		Cnt1 = 0;

		for (int Y = 0; Y <= 5; ++Y)
			Cnt1 += Board[Y1 - Y + _EXTEND_][X1 - Y + _EXTEND_];
		for (int Y = -5; Y <= 0; ++Y) {
 			Ans += ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
			Cnt1 -= Board[Y1 + Y + _EXTEND_][X1 + Y + _EXTEND_];
			Cnt1 += Board[Y1 + Y + 6 + _EXTEND_][X1 + Y + 6 + _EXTEND_];
		}
		Cnt1 = 0;

		for (int Y = 0; Y <= 5; ++Y)
			Cnt1 += Board[Y1 + Y + _EXTEND_][X1 - Y + _EXTEND_];
		for (int Y = -5; Y <= 0; ++Y) {
			Ans += ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
			Cnt1 -= Board[Y1 - Y + _EXTEND_][X1 + Y + _EXTEND_];
			Cnt1 += Board[Y1 - Y - 6 + _EXTEND_][X1 + Y + 6 + _EXTEND_];
		}
		Cnt1 = 0;
	}

	if (abs(y1 - y2) <= 5 && abs(x1 - x2) <= 5) {
		if (y1 - y2 == x1 - x2) {
			short int Y1 = max(y1, y2), X1 = max(x1, x2), Y2 = min(y1, y2), X2 = min(x1, x2);
			for (int Y = 0; Y <= 5; ++Y)
				Cnt1 += Board[Y1 - Y + _EXTEND_][X1 - Y + _EXTEND_];
			for (int Y = -5; Y <= Y2 - Y1; ++Y) {
				Ans -= ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
				Cnt1 -= Board[Y1 + Y + _EXTEND_][X1 + Y + _EXTEND_];
				Cnt1 += Board[Y1 + Y + 6 + _EXTEND_][X1 + Y + 6 + _EXTEND_];
			}
			Cnt1 = 0;
		}
		else if (y1 == y2) {
			short int X1 = max(x1, x2), X2 = min(x1, x2);
			for (int X = 0; X <= 5; ++X)
				Cnt1 += Board[y1 + _EXTEND_][X1 - X + _EXTEND_];
			for (int X = -5; X <= X2 - X1; ++X) {
				Ans -= ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
				Cnt1 -= Board[y1 + _EXTEND_][X1 + X + _EXTEND_];
				Cnt1 += Board[y1 + _EXTEND_][X1 + X + 6 + _EXTEND_];
			}
			Cnt1 = 0;
		}
		else if (y2 - y1 == x1 - x2) {
			short int Y1 = min(y1, y2), X1 = max(x1, x2), Y2 = max(y1, y2), X2 = min(x1, x2);
			for (int Y = 0; Y <= 5; ++Y)
				Cnt1 += Board[Y1 + Y + _EXTEND_][X1 - Y + _EXTEND_];
			for (int Y = -5; Y <= Y1 - Y2; ++Y) {
				Ans -= ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
				Cnt1 -= Board[Y1 - Y + _EXTEND_][X1 + Y + _EXTEND_];
				Cnt1 += Board[Y1 - Y - 6 + _EXTEND_][X1 + Y + 6 + _EXTEND_];
			}
			Cnt1 = 0;
		}
		else if (x1 == x2) {
			short int Y1 = max(y1, y2), Y2 = min(y1, y2);
			for (int Y = 0; Y <= 5; ++Y)
				Cnt1 += Board[Y1 - Y + _EXTEND_][x1 + _EXTEND_];
			for (int Y = -5; Y <= Y2 - Y1; ++Y) {
				Ans -= ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
				Cnt1 -= Board[Y1 + Y + _EXTEND_][x1 + _EXTEND_];
				Cnt1 += Board[Y1 + Y + 6 + _EXTEND_][x1 + _EXTEND_];
			}
			Cnt1 = 0;
		}
	}


	Board[y1 + _EXTEND_][x1 + _EXTEND_] = 0;
	Board[y2 + _EXTEND_][x2 + _EXTEND_] = 0;
	for (int K = 0; K < 2; ++K) {
		int Y1 = Coory[K], X1 = Coorx[K];
		for (int X = 0; X <= 5; ++X) {
			Cnt1 += Board[Y1 + _EXTEND_][X1 - X + _EXTEND_];
			Cnt2 += Board[Y1 + _EXTEND_][X1 - X + _EXTEND_];
		}
		for (int X = -5; X <= 0; ++X) {
			Ans -= ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
			Ans -= ScoreHash[!IsAI][PiecesNum][IsAI][Cnt2];
			Cnt1 -= Board[Y1 + _EXTEND_][X1 + X + _EXTEND_];
			Cnt1 += Board[Y1 + _EXTEND_][X1 + X + 6 + _EXTEND_];
			Cnt2 -= Board[Y1 + _EXTEND_][X1 + X + _EXTEND_];
			Cnt2 += Board[Y1 + _EXTEND_][X1 + X + 6 + _EXTEND_];
		}
		Cnt1 = 0; Cnt2 = 0;

		for (int Y = 0; Y <= 5; ++Y) {
			Cnt1 += Board[Y1 - Y + _EXTEND_][X1 + _EXTEND_];
			Cnt2 += Board[Y1 - Y + _EXTEND_][X1 + _EXTEND_];
		}
		for (int Y = -5; Y <= 0; ++Y) {
			Ans -= ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
			Ans -= ScoreHash[!IsAI][PiecesNum][IsAI][Cnt2];
			Cnt1 -= Board[Y1 + Y + _EXTEND_][X1 + _EXTEND_];
			Cnt1 += Board[Y1 + Y + 6 + _EXTEND_][X1 + _EXTEND_];
			Cnt2 -= Board[Y1 + Y + _EXTEND_][X1 + _EXTEND_];
			Cnt2 += Board[Y1 + Y + 6 + _EXTEND_][X1 + _EXTEND_];
		}
		Cnt1 = 0; Cnt2 = 0;

		for (int Y = 0; Y <= 5; ++Y) {
			Cnt1 += Board[Y1 - Y + _EXTEND_][X1 - Y + _EXTEND_];
			Cnt2 += Board[Y1 - Y + _EXTEND_][X1 - Y + _EXTEND_];
		}
		for (int Y = -5; Y <= 0; ++Y) {
			Ans -= ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
			Ans -= ScoreHash[!IsAI][PiecesNum][IsAI][Cnt2];
			Cnt1 -= Board[Y1 + Y + _EXTEND_][X1 + Y + _EXTEND_];
			Cnt1 += Board[Y1 + Y + 6 + _EXTEND_][X1 + Y + 6 + _EXTEND_];
			Cnt2 -= Board[Y1 + Y + _EXTEND_][X1 + Y + _EXTEND_];
			Cnt2 += Board[Y1 + Y + 6 + _EXTEND_][X1 + Y + 6 + _EXTEND_];
		}
		Cnt1 = 0; Cnt2 = 0;

		for (int Y = 0; Y <= 5; ++Y) {
			Cnt1 += Board[Y1 + Y + _EXTEND_][X1 - Y + _EXTEND_];
			Cnt2 += Board[Y1 + Y + _EXTEND_][X1 - Y + _EXTEND_];
		}
		for (int Y = -5; Y <= 0; ++Y) {
			Ans -= ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
			Ans -= ScoreHash[!IsAI][PiecesNum][IsAI][Cnt2];
			Cnt1 -= Board[Y1 - Y + _EXTEND_][X1 + Y + _EXTEND_];
			Cnt1 += Board[Y1 - Y - 6 + _EXTEND_][X1 + Y + 6 + _EXTEND_];
			Cnt2 -= Board[Y1 - Y + _EXTEND_][X1 + Y + _EXTEND_];
			Cnt2 += Board[Y1 - Y - 6 + _EXTEND_][X1 + Y + 6 + _EXTEND_];
		}
		Cnt1 = 0; Cnt2 = 0;
	}

	if (abs(y1 - y2) <= 5 && abs(x1 - x2) <= 5) {
		if (y1 - y2 == x1 - x2) {
			short int Y1 = max(y1, y2), X1 = max(x1, x2), Y2 = min(y1, y2), X2 = min(x1, x2);
			for (int Y = 0; Y <= 5; ++Y) {
				Cnt1 += Board[Y1 - Y + _EXTEND_][X1 - Y + _EXTEND_];
				Cnt2 += Board[Y1 - Y + _EXTEND_][X1 - Y + _EXTEND_];
			}
			for (int Y = -5; Y <= Y2 - Y1; ++Y) {
				Ans += ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
				Ans += ScoreHash[!IsAI][PiecesNum][IsAI][Cnt2];
				Cnt1 -= Board[Y1 + Y + _EXTEND_][X1 + Y + _EXTEND_];
				Cnt1 += Board[Y1 + Y + 6 + _EXTEND_][X1 + Y + 6 + _EXTEND_];
				Cnt2 -= Board[Y1 + Y + _EXTEND_][X1 + Y + _EXTEND_];
				Cnt2 += Board[Y1 + Y + 6 + _EXTEND_][X1 + Y + 6 + _EXTEND_];
			}
			Cnt1 = 0; Cnt2 = 0;
		}
		else if (y1 == y2) {
			short int X1 = max(x1, x2), X2 = min(x1, x2);
			for (int X = 0; X <= 5; ++X) {
				Cnt1 += Board[y1 + _EXTEND_][X1 - X + _EXTEND_];
				Cnt2 += Board[y1 + _EXTEND_][X1 - X + _EXTEND_];
			}
			for (int X = -5; X <= X2 - X1; ++X) {
				Ans += ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
				Ans += ScoreHash[!IsAI][PiecesNum][IsAI][Cnt2];
				Cnt1 -= Board[y1 + _EXTEND_][X1 + X + _EXTEND_];
				Cnt1 += Board[y1 + _EXTEND_][X1 + X + 6 + _EXTEND_];
				Cnt2 -= Board[y1 + _EXTEND_][X1 + X + _EXTEND_];
				Cnt2 += Board[y1 + _EXTEND_][X1 + X + 6 + _EXTEND_];
			}
			Cnt1 = 0; Cnt2 = 0;
		}
		else if (y2 - y1 == x1 - x2) {
			short int Y1 = min(y1, y2), X1 = max(x1, x2), Y2 = max(y1, y2), X2 = min(x1, x2);
			for (int Y = 0; Y <= 5; ++Y) {
				Cnt1 += Board[Y1 + Y + _EXTEND_][X1 - Y + _EXTEND_];
				Cnt2 += Board[Y1 + Y + _EXTEND_][X1 - Y + _EXTEND_];
			}
			for (int Y = -5; Y <= Y1 - Y2; ++Y) {
				Ans += ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
				Ans += ScoreHash[!IsAI][PiecesNum][IsAI][Cnt2];
				Cnt1 -= Board[Y1 - Y + _EXTEND_][X1 + Y + _EXTEND_];
				Cnt1 += Board[Y1 - Y - 6 + _EXTEND_][X1 + Y + 6 + _EXTEND_];
				Cnt2 -= Board[Y1 - Y + _EXTEND_][X1 + Y + _EXTEND_];
				Cnt2 += Board[Y1 - Y - 6 + _EXTEND_][X1 + Y + 6 + _EXTEND_];
			}
			Cnt1 = 0; Cnt2 = 0;
		}
		else if (x1 == x2) {
			short int Y1 = max(y1, y2), Y2 = min(y1, y2);
			for (int Y = 0; Y <= 5; ++Y) {
				Cnt1 += Board[Y2 + Y + _EXTEND_][x1 + _EXTEND_];
				Cnt2 += Board[Y2 + Y + _EXTEND_][x1 + _EXTEND_];
			}
			for (int Y = -5; Y <= Y2 - Y1; ++Y) {
				Ans += ScoreHash[IsAI][PiecesNum][IsAI][Cnt1];
				Ans += ScoreHash[!IsAI][PiecesNum][IsAI][Cnt2];
				Cnt1 -= Board[Y2 - Y + _EXTEND_][x1 + _EXTEND_];
				Cnt1 += Board[Y2 - Y - 6 + _EXTEND_][x1 + _EXTEND_];
				Cnt2 -= Board[Y2 - Y + _EXTEND_][x1 + _EXTEND_];
				Cnt2 += Board[Y2 - Y - 6 + _EXTEND_][x1 + _EXTEND_];
			}
			Cnt1 = 0; Cnt2 = 0;
		}
	}


	Board[y1 + _EXTEND_][x1 + _EXTEND_] = Num1;
	Board[y2 + _EXTEND_][x2 + _EXTEND_] = Num1;

	return Ans;
}


bool IfInTwo(unsigned char Board[29][29], unsigned char Y, unsigned char X) {
	return  Board[Y + 2][X - 2] & 1 || Board[Y + 2][X - 1] & 1 || Board[Y + 2][X] & 1 || Board[Y + 2][X + 1] & 1 || Board[Y + 2][X + 2] & 1 ||
		Board[Y + 1][X - 2] & 1 || Board[Y + 1][X - 1] & 1 || Board[Y + 1][X] & 1 || Board[Y + 1][X + 1] & 1 || Board[Y + 1][X + 2] & 1 ||
		Board[Y][X - 2] & 1 || Board[Y][X - 1] & 1 || Board[Y][X] & 1 || Board[Y][X + 1] & 1 || Board[Y][X + 2] & 1 ||
		Board[Y - 1][X - 2] & 1 || Board[Y - 1][X - 1] & 1 || Board[Y - 1][X] & 1 || Board[Y - 1][X + 1] & 1 || Board[Y - 1][X + 2] & 1 ||
		Board[Y - 2][X - 2] & 1 || Board[Y - 2][X - 1] & 1 || Board[Y - 2][X] & 1 || Board[Y - 2][X + 1] & 1 || Board[Y - 2][X + 2] & 1;
}


void GetPos(unsigned char CharBoard[29][29], unsigned short int PiecesNum, unsigned short int IsAI,
	unsigned short Num, vector<TwoBlank>& Ans) {
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
						int the_score = GetScorePart(CharBoard, false, IsAI, y1, x1, y2, x2);
						the_score += CentreHash[y1][x1];
						the_score += CentreHash[y2][x2];
						Ans.push_back(TwoBlank(the_score, make_pair(make_pair(short(y1), short(x1)), make_pair(short(y2), short(x2)))));
						CharBoard[y1 + _EXTEND_][x1 + _EXTEND_] = 0;
						CharBoard[y2 + _EXTEND_][x2 + _EXTEND_] = 0;
					}
				}
	delete[]vis;
	sort(Ans.begin(), Ans.end());
	if (Ans.size() > Num)
		Ans.erase(Ans.begin() + Num, Ans.end());
}


