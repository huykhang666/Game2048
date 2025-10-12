#pragma once;
#include "GameObjects.h"
#include <iomanip>
#include<iostream>

//Quản lí 1 ô vuông trong bàn chơi
class Tile : public GameObject {
private:
	int value;
	bool merged;
public:
	Tile(int v = 0) : value(v), merged(false) {};
	int getValue() const { return value; }
	void setValue(int v) { value = v; }
	bool isMerged() const { return merged; }
	void setMerged(bool m) { merged = m; }

	void render() const override {
		if (value == 0) std::cout << " .";
		else std::cout << std::setw(4) << value;
	}

	bool isEmpty() const {
		return value == 0;
	}

	void update() override {};
};