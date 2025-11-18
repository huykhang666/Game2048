#pragma once
#include "Board.h"
#include "Utils.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include<map>
#include<vector>
#include <SFML/Audio.hpp> 

// Struct đại diện cho một bông tuyết
struct Snowflake {
	sf::CircleShape shape;
	float speed;
};

// Enum để quản lý các thành phần UI (Mở rộng)
enum class ButtonType {
	START, LOAD, EXIT,
	NEW_GAME,
	PLAY_AGAIN, BACK_TO_MENU, EXIT_GAME
};

//Bộ điều khiền của game
class Game {
private:
	Board board;
	GameState state;

	sf::RenderWindow m_window;
	sf::Font m_font;

	// Ảnh nền và trang trí Giáng sinh
	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;

	
	// Âm Thanh
	sf::Music backgroundMusic;
	sf::SoundBuffer moveBuffer;
	sf::Sound moveSound;        
	sf::SoundBuffer mergeBuffer;
	sf::Sound mergeSound;  
	sf::SoundBuffer gameOverBuffer; 
    sf::Sound gameOverSound;


	// Text cho các màn hình
	sf::Text m_titleText;      
	sf::Text m_welcomeText;    
	sf::Text m_gameOverText;   
	sf::Text m_scoreText;       
	sf::Text m_bestText;  

	//Điểm
	sf::Text m_scoreTextPlaying;
	sf::Text m_bestTextPlaying;

	// Thuộc tính Board Game
	float m_boardX, m_boardY, m_tileSize, m_spacing;
	sf::RectangleShape m_boardShape;
	std::map<int, sf::Color> m_tileColors;
	long long m_bestScore;	

	// KHUNG NỀN CHO SCORE VÀ BEST
	sf::RectangleShape m_scoreBackground;
	sf::RectangleShape m_bestBackground;


	// --- HIỆU ỨNG TUYẾT RƠI ---
	std::vector<Snowflake> m_snowflakes;
	const int NUM_SNOWFLAKES = 200; // Số lượng bông tuyết
	const float MIN_SNOW_SPEED = 1.0f;
	const float MAX_SNOW_SPEED = 3.0f;
	const float MIN_SNOW_SIZE = 1.0f;
	const float MAX_SNOW_SIZE = 3.0f;
public:
	Game();
	void run();

	// Cấu trúc để quản lý Nút bấm
	struct UIButton {
		sf::RectangleShape shape;
		sf::Text text;
		ButtonType type;
		sf::Vector2f originalScale = { 1.0f, 1.0f };
	};

private:
	// Các danh sách nút cho từng màn hình
	std::vector<UIButton> menuButtons;
	std::vector<UIButton> playingButtons;
	std::vector<UIButton> gameOverButtons;
private:
	void loadAssets();
	void setupUI();
	void setupTileColors();
	void setupButtons(std::vector<UIButton>& buttons, ButtonType types[], const std::string names[], int count, float startY);

	void renderMenu();
	void renderGame();
	void renderGameOver();
	void processEvents();

	// Hàm hỗ trợ
	bool isMouseOver(const sf::Shape& shape) const;
	void updateButtonHover();
	void processButtonClick(ButtonType type);
	void drawTile(const Tile& tile, float x, float y, float size);
	void drawTitle(sf::Text& textObj, float y, const std::string& str, int size, float outline);

	void initSnowflake(Snowflake& snowflake);
	~Game() ;

};
