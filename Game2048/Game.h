#pragma once
#include "Board.h"
#include "Utils.h"
#include<iostream>

//Bộ điều khiền của game
class Game {
private:
	Board board;
	GameState state;

public:
	Game();
	void run();

private:
	void renderMenu();
	void renderGame();
	void renderGameOver();
	void processInput();

};
