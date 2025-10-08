#pragma once;
#include<string>

//Enum các hướng di chuyển
enum class Direction {
	UP, DOWN, LEFT, RIGHT, NONE
};

//Enum trạng thái game
enum class GameState {
	MENU, PLAYING, GAME_OVER, EXIT
};

//Union: dữ liệu đa kiểu
union dataValue {
	int intValue;
	float floatValue;
	const char* strValue;

	dataValue() : intValue(0) {}
	dataValue(int v) : intValue(v) {}
	dataValue(float v) : floatValue(v) {}
	dataValue(const char* s) : strValue(s) {}

};