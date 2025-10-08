#include "Board.h"
#include<algorithm>
#include<sstream>

//Constructor
Board::Board() : rng(std::random_device{}()), score(0) {
	reset();
}

//Reset giá trị các ô về 0 và tạo 2 ô có giá trị bất kì
void Board::reset() {
	for (auto& row : grid) {
		for (auto& tile : row) {
			tile.setValue(0);
		}
	}
	score = 0;
	spawnRandomTile();
	spawnRandomTile();

}

//Sinh ra 1 giá trị ngẫu nhiên trên bảng
bool Board::spawnRandomTile() {
	std::vector<std::pair<int, int>> emptyCells;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (grid[i][j].getValue() == 0) {
				emptyCells.emplace_back(i, j);
			}
		}
	}

	if (emptyCells.empty()) return false;
	//Sinh số ngẫu nhiên
	std::uniform_int_distribution<> dist(0, (int)emptyCells.size() - 1);
	std::pair<int, int> pos = emptyCells[dist(rng)];
	int x = pos.first;
	int y = pos.second;
}

bool Board::move(Direction dir) {
	bool moved = false;
	std::array<int, SIZE> tempRow;
	for (auto& row : grid) {
		for (auto& tile : row) {
			tile.setMerged(false);
		}
	}
	switch (dir) {
	case Direction::LEFT:
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				tempRow[j] = grid[i][j].getValue();
			}
			moved |= moveRowLeft(tempRow);
			for (int j = 0; j < SIZE; j++) {
				grid[i][j].setValue(tempRow[j]);
			}
		}
		break;
	}
			
}