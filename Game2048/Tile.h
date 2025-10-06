#pragma once

class Tile {
	int value;
public:
	int getValue() const { return value; }
	Tile(int v = 0) : value(v) {}
	bool isEmpty() const { return value == 0; }
};