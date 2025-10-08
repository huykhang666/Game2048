#pragma once
#include <array>
#include<random>
#include<string>
#include "Tile.h"
#include "Utils.h"

//Quản lí logic
class Board {
public:
	static constexpr int SIZE = 4;
	using Row = std::array <Tile, SIZE>;
	std::array<Row, SIZE> grid;
	long long score;

	Board();
	void reset();
	bool spawnRandomTile();
	bool canMove();
	bool move(Direction dir);
	std::string toString() const;

private:
	std::mt19937 rng;
	bool moveRowLeft(std::array<int, SIZE>& rowVals);
	bool anyMergePossoble() const;
};