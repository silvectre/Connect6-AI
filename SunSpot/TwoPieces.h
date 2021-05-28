#pragma once
#include <vector>
struct OneBlank {
	int Score = -88888888;
	std::pair<short int, short int> Pos;
	OneBlank() {};
	OneBlank(int _Score, std::pair<short int, short int> _Pos) :
		Score(_Score), Pos(_Pos) {};
	bool operator< (const OneBlank that) const {
		if (Score == that.Score)
			return Pos < that.Pos;
		return Score > that.Score;
	}
};


struct TwoBlank {
	int Score = -88888888;
	std::pair<std::pair<short int, short int>, std::pair<short int, short int>> Pos;
	TwoBlank() {};
	TwoBlank(int _Score, std::pair<std::pair<short int, short int>, std::pair<short int, short int>> _Pos) :
		Score(_Score), Pos(_Pos) {};
	bool operator< (const TwoBlank that) const {
		if (Score == that.Score)
			return Pos < that.Pos;
		return Score > that.Score;
	}
};