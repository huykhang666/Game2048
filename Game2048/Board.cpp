#include "Board.h"
#include<algorithm>
#include<sstream>
#include<fstream>
#include <iomanip>
//Constructor
Board::Board() : rng(std::random_device{}()), score(0) {
	reset();
}

// Hàm hỗ trợ để nén các giá trị khác 0 về phía trái
void Board::compressRow(std::array<int, Board::SIZE>& rowVals) {
	int k = 0;
	std::array<int, Board::SIZE> newRow = {};

	// Nén các giá trị khác 0 về phía trái
	for (int i = 0; i < Board::SIZE; i++) {
		if (rowVals[i] != 0) {
			newRow[k++] = rowVals[i];
		}
	}
	rowVals = newRow;
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

	std::uniform_int_distribution<int> distVal(0, 9);
	grid[r][c].setValue((rand() % 10 == 0) ? 4 : 2);
	return true;
}

//Kiểm tra điều kiện thắng
bool Board::hasWon() const {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j].getValue() >= 2048) {
                return true;
            }
        }
    }
    return false;
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

	return anyMergePossible();
}
//Kiểm tra các ô có thể gộp được
bool Board::anyMergePossible() const {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (grid[i][j].getValue() == grid[i][j + 1].getValue() ||
                grid[j][i].getValue() == grid[j + 1][i].getValue()) {
                return true;
            }
        }
    }
    return false;
}

// Di chuyển hàng sang trái (Đã sửa)
bool Board::moveRowLeft(std::array<int, SIZE>& rowVals) {
    bool moved = false;
    std::array<int, SIZE> originalRow = rowVals; // Lưu trữ giá trị ban đầu để kiểm tra moved

    // BƯỚC 1: NÉN (Dời) các ô khác 0 sang trái
    compressRow(rowVals);

    // BƯỚC 2: GỘP (Merge) các ô liền kề
    for (int i = 0; i < SIZE - 1; i++) {
        // Kiểm tra 2 ô liền kề có giống nhau không
        if (rowVals[i] != 0 && rowVals[i] == rowVals[i + 1]) {
            rowVals[i] *= 2;        // Gộp: Nhân đôi giá trị
            score += rowVals[i];    // Cộng điểm
            rowVals[i + 1] = 0;     // Đặt ô gộp thứ hai về 0 (để nó không gộp thêm lần nữa)
            moved = true;
        }
    }

    // BƯỚC 3: NÉN (Dời) lần nữa sau khi gộp
    compressRow(rowVals);

    // Kiểm tra xem có di chuyển/thay đổi nào xảy ra không
    // (Nếu không có gộp, ta so sánh mảng cuối cùng với mảng ban đầu)
    if (!moved) {
        for (int i = 0; i < SIZE; ++i) {
            if (originalRow[i] != rowVals[i]) {
                moved = true; // Chỉ dời vị trí cũng tính là moved
                break;
            }
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

	case Direction::RIGHT:
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				tempRow[j] = grid[i][SIZE - 1 - j].getValue();
			}

			moved |= moveRowLeft(tempRow);

			for (int j = 0; j < SIZE; j++) {
				grid[i][SIZE - 1 - j].setValue(tempRow[j]);
			}
		}
		break;

	case Direction::UP:
		for (int j = 0; j < SIZE; j++) {
			for (int i = 0; i < SIZE; i++) {
				tempRow[i] = grid[i][j].getValue();
			}

			moved |= moveRowLeft(tempRow);

			for (int i = 0; i < SIZE; i++) {
				grid[i][j].setValue(tempRow[i]);
			}
		}
		break;

	case Direction::DOWN:
		for (int j = 0; j < SIZE; j++) {
			for (int i = 0; i < SIZE; i++) {
				tempRow[i] = grid[SIZE - 1 - i][j].getValue();
			}

			moved |= moveRowLeft(tempRow);

			for (int i = 0; i < SIZE; i++) {
				grid[SIZE - 1 - i][j].setValue(tempRow[i]);
			}
		}
		break;
	default:
		break;
	}

	if (moved)
		spawnRandomTile();

	return moved;
}

//In bảng ra chuỗi
std::string Board::toString() const {
	std::ostringstream oss;
	oss << "Score: " << score << "\n";
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (grid[i][j].getValue() == 0) {
				oss << std::setw(4) << ".";
			}
			else {
				oss << std::setw(4) << grid[i][j].getValue();
			}
		}
		oss << "\n";
	}
	return oss.str();
}

//Lưu game
void Board::saveToFile(const std::string& filename) const {
	std::ofstream file(filename);
	if (!file) return;

	file << score << "\n";
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			file << grid[i][j].getValue() << " ";
		}
		file << "\n";
	}
}

//Load game
bool Board::loadFromFile(const std::string& filename) {
	std::fstream file(filename);
	if (!file) return false;

	file >> score;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			int v;
			file >> v;
			grid[i][j].setValue(v);
		}
	}
	return true;
}
