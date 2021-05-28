#include "BitData.cpp"
/*#include "Data.cpp*/
LINE Direction1[19];
LINE Direction2[19];
LINE Direction3[38];
LINE Direction4[38];
LINE* AllDirctions[4]{ Direction1, Direction2, Direction3, Direction4};
bool IfInTwo(unsigned char Board[29][29], unsigned char Y, unsigned char X);
extern char CharBoard[29][29];
extern const int _EXTEND_;
extern pair<pair<short int, short int>, pair<short int, short int>> other;


int GetScoreBit(LINE* BitBoard[4], bool PiecesNum) {

	int Ans = 0;
	return Ans;
}