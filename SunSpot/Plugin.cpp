#include <vector>
#include "Data.cpp"
#define _EXTEND_ 5
using namespace std;
extern unsigned short int is_white;
extern pair<pair<short int, short int>, pair<short int, short int>> other;
extern short int board[19][19];
extern unsigned char CharBoard[29][29];
pair<pair<short int, short int>, pair<short int, short int>>Greedy(unsigned short int IsAI);
pair<pair<short int, short int>, pair<short int, short int>>GreedyPlus(unsigned short int IsAI);
pair<pair<short int, short int>, pair<short int, short int>>GreedyPlusCut(unsigned short int IsAI);
pair<pair<short int, short int>, pair<short int, short int>>Plugin(unsigned short int);
pair<pair<short int, short int>, pair<short int, short int>>GreedyPlusMax(unsigned short int IsAI);
pair<pair<short int, short int>, pair<short int, short int>>GreedyPlusTwo(unsigned short int IsAI);
pair<pair<short int, short int>, pair<short int, short int>>Plugin(unsigned short int IsAI) {
	board[other.first.first][other.first.second] = !is_white;
	board[other.second.first][other.second.second] = !is_white;
	CharBoard[other.first.first + _EXTEND_][other.first.second + _EXTEND_] = ColorHash[0];
	CharBoard[other.second.first + _EXTEND_][other.second.second + _EXTEND_] = ColorHash[0];
	pair<pair<short int, short int>, pair<short int, short int>> ans;
	ans = GreedyPlusMax(1);
	board[ans.first.first][ans.first.second] = is_white;
	board[ans.second.first][ans.second.second] = is_white;
	CharBoard[ans.first.first + _EXTEND_][ans.first.second + _EXTEND_] = ColorHash[1];
	CharBoard[ans.second.first + _EXTEND_][ans.second.second + _EXTEND_] = ColorHash[1];
	return ans;
}