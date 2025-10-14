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

	grid[r][c].setValue((rand() % 10 == 0) ? 4 : 2);
	return true;	
}

//Kiểm tra còn có thể di chuyển được không, nếu không thì game over
bool Board::canMove() {
	//Kiểm tra các ô trống
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (grid[i][j].getValue() == 0) {
				return true;
			}
		}
	}

	//Kiểm tra các ô có thể gộp được
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE - 1; j++) {
			if (grid[i][j].getValue() == grid[i][j + 1].getValue() ||
				grid[j][i].getValue() == grid[j + 1][i].getValue())
				return true;
		}
	}
}

// Di chuyển hàng sang trái
bool Board::moveRowLeft(std::array<int, SIZE>& rowVals) {
	bool moved = false;
	int lastMerge = -1;

	for (int i = 1; i < SIZE; i++) {
		if (rowVals[i] == 0) continue;
		int j = i;

		//Dời ô sang trái hết mức có thể
		while (j > 0 && rowVals[j - 1] == 0) {
			rowVals[j - 1] = rowVals[j];
			rowVals[j] = 0;
			j--;
			moved = true;
		}

		//Gộp lại các giá trị
		if (j > 0 && rowVals[j - 1] == rowVals[j] && lastMerge != j - 1) {
			rowVals[j - 1] *= 2;
			score += rowVals[j - 1];
			lastMerge = j - 1;
			moved = true;
		}
	}
	return moved;
}

//Xử lí di chuyển
bool Board::move(Direction dir) {
	bool moved = false;
	std::array<int, SIZE> tempRow;

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