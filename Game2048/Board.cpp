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
	std::vector<std::pair<int, int>> empties;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (grid[i][j].isEmpty()) {
				empties.emplace_back(i, j);
			}
		}
	}

	if (empties.empty()) return false;
	std::uniform_int_distribution<int> dist(0, (int)empties.size() - 1);
	std::pair<int, int> pos = empties[dist(rng)];
	int r = pos.first;
	int c = pos.second;
}