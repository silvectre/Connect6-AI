#pragma once
#include <unordered_map>
using namespace std;
typedef unsigned long long int LINE;
extern const LINE Bit[3][19];
extern const LINE BitOne[19];
extern const LINE BitSix[19];
extern const LINE BitEight[19];
extern const LINE SelfBitSet[19];
extern const LINE EnemyBitSet[19];
extern const unordered_map<int, int>Path[2];
extern const unordered_map<int, int>ChessTape[2];
extern const char ColorHash[2];
extern const int ScoreHash[2][2][256];
extern const char CentreHash[19][19];
