#include "Game.h"
#include<conio.h>

//Constructor
Game::Game() : state(GameState::MENU) {}

//Hàm run game chạy đến khi ấn exit
void Game::run() {
	while (state != GameState::EXIT) {
		switch (state) {
		case GameState::MENU: 
			renderMenu();
			break;
		case GameState::PLAYING:
			renderGame();
			break;
		case GameState::GAME_OVER:
			renderGameOver();
			break;
		default: break;
		}
	}
}

//Hiển thị MENU chính
void Game::renderMenu() {
	system("cls");
	std::cout << "===== 2048 GAME ==== \n";
	std::cout << "1. Start New Game \n";
	std::cout << "2. Load Game \n";
	std::cout << "3. Exit \n";
	std::cout << "===================== \n";
	std::cout << "Choose: ";

	int choice;
	std::cin >> choice;

	switch (choice) {
	case 1:
		board.reset();
		state = GameState::PLAYING;
		break;

	case 2:
		if (board.loadFromFile("save.txt"))
			std::cout << "Loaded successfully! \n";
		else
			std::cout << "No save file found. \n";
		system("pause");
		state = GameState::PLAYING;
		break;
	case 3:
		state = GameState::EXIT;
		break;
	default:
		break;
	}
}

//Xử lí khi đang chơi
void Game::renderGame() {
	system("cls");
	std::cout << board.toString();
	std::cout << "\nUse W/A/S/D to move. Press Q to quit, L to save.\n";

	char key = _getch();
	Direction dir = Direction::NONE;

	switch (tolower(key)) {
	case 'w': dir = Direction::UP; break;
	case 'a': dir = Direction::LEFT; break;
	case 's': dir = Direction::DOWN; break;
	case 'd': dir = Direction::RIGHT; break;
	case 'l': board.saveToFile("save.txt"); return;
	case 'q': state = GameState::EXIT; return;
	default: return;
	}

	if (board.move(dir)) {
		board.spawnRandomTile();
	}

	if (!board.canMove()) {
		state = GameState::GAME_OVER;
	}
}

void Game::renderGameOver() {
	system("cls");
	std::cout << "===== GAME OVER ===== \n";
	std::cout << board.toString();
	std::cout << "\n Press M to return to menu to menu or Q to quit \n";

	char key = _getch();
	if (tolower(key) == 'm') state = GameState::MENU;
	else state = GameState::EXIT;
}