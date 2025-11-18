#include "Game.h"
#include <sstream>


// Kích thước cửa sổ
const int WINDOW_WIDTH = 540;
const int WINDOW_HEIGHT = 960;
const sf::Vector2f HOVER_SCALE = { 1.05f, 1.05f };
const sf::Color BUTTON_COLOR = sf::Color(255, 140, 50);
const sf::Color BUTTON_OUTLINE_COLOR = sf::Color(229, 136, 50);

// Constructor
Game::Game()
	: state(GameState::MENU), m_bestScore(0),
	m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2048 Christmas", sf::Style::Close)
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	// --- TẢI VÀ CÀI ĐẶT ÂM THANH ---
	if (!backgroundMusic.openFromFile("nhacNen2048.ogg")) {
		std::cerr << "ERROR: Failed to load nhacNen2048.ogg\n";

	}
	else {
		backgroundMusic.setLoop(true); 
		backgroundMusic.setVolume(20);
	}

	if (moveBuffer.loadFromFile("click.wav")) {
		moveSound.setBuffer(moveBuffer);
		moveSound.setVolume(50);
	}
	else {
		std::cerr << "ERROR: Failed to load click.wav\n";
	}

	if (mergeBuffer.loadFromFile("merge_2.wav")) {
		mergeSound.setBuffer(mergeBuffer);
		mergeSound.setVolume(80);
	}
	else {
		std::cerr << "ERROR: Failed to load merge_2.wav\n";
	}

	if (gameOverBuffer.loadFromFile("game_over.wav")) {
		gameOverSound.setBuffer(gameOverBuffer);
		gameOverSound.setVolume(300); 
	}
	else {
		std::cerr << "ERROR: Failed to load game_over.wav\n";
	}

	// --- KHỞI TẠO TUYẾT RƠI ---
	m_snowflakes.resize(NUM_SNOWFLAKES);
	for (auto& snowflake : m_snowflakes) {
		initSnowflake(snowflake);
	}

	m_window.setFramerateLimit(60);
	setupTileColors();
	loadAssets();
	setupUI();


}

// Hàm hỗ trợ đặt thuộc tính Text
void Game::drawTitle(sf::Text& textObj, float y, const std::string& str, int size, float outline) {
	textObj.setFont(m_font);
	textObj.setString(str);
	textObj.setCharacterSize(size);
	textObj.setFillColor(sf::Color::White);
	textObj.setOutlineColor(sf::Color(255, 69, 0));
	textObj.setOutlineThickness(outline);

	sf::FloatRect textRect = textObj.getLocalBounds();
	textObj.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	textObj.setPosition(WINDOW_WIDTH / 2, y);
}

// Hàm tải tài nguyên và thiết lập background
void Game::loadAssets() {
	if (!m_font.loadFromFile("LuckiestGuy-Regular.ttf")) {
		std::cout << "ERROR: Failed to load font file: assets/arial.ttf" << std::endl;
	}
	if (!m_backgroundTexture.loadFromFile("maingame2048.jpg")) {
		std::cout << "ERROR: Failed to load texture file: assets/background.png" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(
		(float)WINDOW_WIDTH / m_backgroundSprite.getLocalBounds().width,
		(float)WINDOW_HEIGHT / m_backgroundSprite.getLocalBounds().height
	);
}

// Hàm thiết lập màu cho các ô
void Game::setupTileColors() {
	// Màu đa sắc (lấy cảm hứng từ ảnh bạn cung cấp)
	m_tileColors[0] = sf::Color(100, 150, 200, 150); // Màu nền ô trống (Xanh mờ)

	// Các màu sắc tương phản:
	m_tileColors[2] = sf::Color(109, 187, 248); // Xanh dương nhạt
	m_tileColors[4] = sf::Color(176, 118, 222); // Tím Lavender
	m_tileColors[8] = sf::Color(255, 179, 102); // Cam Peach
	m_tileColors[16] = sf::Color(80, 220, 100);  // Xanh lá cây sáng

	m_tileColors[32] = sf::Color(255, 102, 102); // Đỏ san hô
	m_tileColors[64] = sf::Color(100, 150, 200); // Xanh biển
	m_tileColors[128] = sf::Color(255, 153, 204); // Hồng Fuchsia
	m_tileColors[256] = sf::Color(102, 204, 255); // Xanh Cyan

	m_tileColors[512] = sf::Color(255, 102, 178); // Hồng đậm
	m_tileColors[1024] = sf::Color(178, 255, 102); // Xanh lá Chanh
	m_tileColors[2048] = sf::Color(255, 255, 102); // Vàng rực

	m_tileColors[4096] = sf::Color(60, 58, 50);
	m_tileColors[8192] = sf::Color(0, 0, 0);
}

// Hàm khởi tạo 1 nút 
void setupButton(Game::UIButton& btn, float yPos, const std::string& textStr, ButtonType type, const sf::Font& font) {
	sf::Vector2f size(WINDOW_WIDTH * 0.4f, 70.f);
	btn.type = type;
	btn.shape.setSize(size);
	btn.shape.setFillColor(BUTTON_COLOR);
	btn.shape.setOutlineColor(BUTTON_OUTLINE_COLOR);
	btn.shape.setOutlineThickness(2.5f);
	btn.shape.setOrigin(size.x / 2, size.y / 2);
	btn.shape.setPosition(WINDOW_WIDTH / 2, yPos);

	btn.text.setFont(font);
	btn.text.setString(textStr);
	btn.text.setCharacterSize(40);
	btn.text.setFillColor(sf::Color::White);
	sf::FloatRect textRect = btn.text.getLocalBounds();
	btn.text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	btn.text.setPosition(btn.shape.getPosition());
}

// Hàm khởi tạo nhóm nút
void Game::setupButtons(std::vector<UIButton>& buttons, ButtonType types[], const std::string names[], int count, float startY) {
	float buttonSpacing = 20.f;
	buttons.resize(count);
	for (int i = 0; i < count; ++i) {
		setupButton(buttons[i], startY + i * (80.f + buttonSpacing), names[i], types[i], m_font);
	}
}

// Hàm thiết lập toàn bộ UI
void Game::setupUI() {
	// 1. Tiêu đề
	drawTitle(m_titleText, WINDOW_HEIGHT * 0.25f, "2048", 120, 7.f);
	drawTitle(m_welcomeText, WINDOW_HEIGHT * 0.15f, "WELCOME TO", 50, 5.f);
	drawTitle(m_gameOverText, WINDOW_HEIGHT * 0.25f, "GAME OVER!", 80, 8.f);

	// 2. Điểm số (Game Over Screen)
	m_scoreText.setFont(m_font); m_scoreText.setCharacterSize(35); m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.35f);

	m_bestText.setFont(m_font); m_bestText.setCharacterSize(35); m_bestText.setFillColor(sf::Color::White);
	m_bestText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.40);

	// 3. Nút Menu
	ButtonType menuTypes[] = { ButtonType::START, ButtonType::LOAD, ButtonType::EXIT };
	std::string menuNames[] = { "Start", "Load", "Exit" };
	setupButtons(menuButtons, menuTypes, menuNames, 3, WINDOW_HEIGHT * 0.47f);

	// 4. Nút Game Over
	ButtonType overTypes[] = { ButtonType::PLAY_AGAIN, ButtonType::BACK_TO_MENU, ButtonType::EXIT_GAME };
	std::string overNames[] = { "Play Again", "Menu", "Exit Game" };
	setupButtons(gameOverButtons, overTypes, overNames, 3, WINDOW_HEIGHT * 0.5f);

	// 5. Nút Playing 
	ButtonType playingTypes[] = { ButtonType::NEW_GAME, ButtonType::EXIT };
	std::string playingNames[] = { "New Game", "Exit" };


	float smallButtonWidth = WINDOW_WIDTH * 0.25f;
	float smallButtonHeight = 50.f; 

	// Cần khai báo hàm setupSmallButton hoặc sửa lại logic setupButton
	auto setupSmallButton = [&](UIButton& btn, float xPos, float yPos, const std::string& textStr, ButtonType type, const sf::Font& font) {
		btn.type = type;
		btn.shape.setSize(sf::Vector2f(smallButtonWidth, smallButtonHeight));
		btn.shape.setFillColor(BUTTON_COLOR);
		btn.shape.setOutlineColor(BUTTON_OUTLINE_COLOR);
		btn.shape.setOutlineThickness(5);
		btn.shape.setOrigin(smallButtonWidth / 2, smallButtonHeight / 2);
		btn.shape.setPosition(xPos, yPos);

		btn.text.setFont(font);
		btn.text.setString(textStr);
		btn.text.setCharacterSize(25);
		btn.text.setFillColor(sf::Color::White);
		sf::FloatRect textRect = btn.text.getLocalBounds();
		btn.text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		btn.text.setPosition(btn.shape.getPosition());
		};

	playingButtons.resize(2);
	float playingButtonsY = WINDOW_HEIGHT * 0.79f;

	setupSmallButton(playingButtons[0], WINDOW_WIDTH * 0.3f, playingButtonsY, "New Game", playingTypes[0], m_font);
	setupSmallButton(playingButtons[1], WINDOW_WIDTH * 0.7f, playingButtonsY, "Exit", playingTypes[1], m_font);


	// 6. Cấu hình Lưới Chơi Game
	float boardSize = WINDOW_WIDTH * 0.85f;
	m_spacing = 15.f;
	m_tileSize = (boardSize - (Board::SIZE + 1) * m_spacing) / Board::SIZE;
	m_boardX = (WINDOW_WIDTH - boardSize) / 2;
	m_boardY = WINDOW_HEIGHT * 0.25f;
	m_boardShape.setSize(sf::Vector2f(boardSize, boardSize));
	m_boardShape.setPosition(m_boardX, m_boardY);
	m_boardShape.setFillColor(sf::Color(100, 150, 200, 150));
	m_boardShape.setOutlineColor(sf::Color(20, 20, 20, 100));
	m_boardShape.setOutlineThickness(5.f);

	// 7. Text Score và Best Score cho màn hình PLAYING - THIẾT LẬP MỚI

	// Tọa độ trung tâm (X, Y) của khung SCORE và BEST
	float scoreCenterY = WINDOW_HEIGHT * 0.2f; 
	float scoreCenterX_Left = WINDOW_WIDTH * 0.25f; 
	float scoreCenterX_Right = WINDOW_WIDTH * 0.75f;

	// Kích thước của khung nền
	float backgroundWidth = WINDOW_WIDTH * 0.4f; // Tăng chiều rộng để chứa chữ
	float backgroundHeight = 60.f;

	// MÀU XANH ĐẬM CHO KHUNG NỀN
	sf::Color darkBlue = sf::Color(10, 60, 110);

	// --- CẤU HÌNH KHUNG NỀN SCORE ---
	m_scoreBackground.setSize(sf::Vector2f(backgroundWidth, backgroundHeight));
	m_scoreBackground.setFillColor(darkBlue);

	// Căn giữa khung nền theo trục X, Y
	m_scoreBackground.setOrigin(backgroundWidth / 2.f, backgroundHeight / 2.f);
	m_scoreBackground.setPosition(scoreCenterX_Left, scoreCenterY);


	// --- CẤU HÌNH KHUNG NỀN BEST ---
	m_bestBackground.setSize(sf::Vector2f(backgroundWidth, backgroundHeight));
	m_bestBackground.setFillColor(darkBlue);

	// Căn giữa khung nền theo trục X, Y
	m_bestBackground.setOrigin(backgroundWidth / 2.f, backgroundHeight / 2.f);
	m_bestBackground.setPosition(scoreCenterX_Right, scoreCenterY);


	// --- CẤU HÌNH TEXT SCORE VÀ BEST SCORE ---

	// Text SCORE
	m_scoreTextPlaying = m_scoreText;
	m_scoreTextPlaying.setCharacterSize(30);
	m_scoreTextPlaying.setFillColor(sf::Color::White);
	m_scoreTextPlaying.setOutlineColor(sf::Color::Black);
	m_scoreTextPlaying.setOutlineThickness(1.f);
	m_scoreTextPlaying.setString("SCORE: 0");

	// Thiết lập điểm gốc (Origin) ở giữa Text để căn giữa nội dung
	sf::FloatRect scoreRect = m_scoreTextPlaying.getLocalBounds();
	m_scoreTextPlaying.setOrigin(scoreRect.left + scoreRect.width / 2.0f, scoreRect.top + scoreRect.height / 2.0f);
	// Đặt Text vào vị trí trung tâm của khung nền
	m_scoreTextPlaying.setPosition(scoreCenterX_Left, scoreCenterY);

	// Text BEST SCORE
	m_bestTextPlaying = m_bestText;
	m_bestTextPlaying.setCharacterSize(30);
	m_bestTextPlaying.setFillColor(sf::Color::White);
	m_bestTextPlaying.setOutlineColor(sf::Color::Black);
	m_bestTextPlaying.setOutlineThickness(1.f);
	m_bestTextPlaying.setString("BEST: 0");

	// Thiết lập điểm gốc (Origin) ở giữa Text để căn giữa nội dung
	sf::FloatRect bestRect = m_bestTextPlaying.getLocalBounds();
	m_bestTextPlaying.setOrigin(bestRect.left + bestRect.width / 2.0f, bestRect.top + bestRect.height / 2.0f);
	// Đặt Text vào vị trí trung tâm của khung nền
	m_bestTextPlaying.setPosition(scoreCenterX_Right, scoreCenterY);
}

// Hàm kiểm tra di chuột
bool Game::isMouseOver(const sf::Shape& shape) const {
	sf::FloatRect bounds = shape.getGlobalBounds();
	sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	return bounds.contains(mousePos);
}

// Xử lý logic khi nút được click
void Game::processButtonClick(ButtonType type) {
	if (board.score > m_bestScore) m_bestScore = board.score; // Cập nhật Best Score

	switch (type) {
	case ButtonType::START:
	case ButtonType::NEW_GAME:
	case ButtonType::PLAY_AGAIN:
		board.reset();
		state = GameState::PLAYING;

		// BỔ SUNG: Bật nhạc nền khi bắt đầu/chơi lại
		if (backgroundMusic.getStatus() == sf::Music::Paused) {
			backgroundMusic.play();
		}
		break;

	case ButtonType::LOAD:
		if (board.loadFromFile("save.txt")) {
			state = GameState::PLAYING;

			// BỔ SUNG: Bật nhạc nền khi Load Game thành công
			if (backgroundMusic.getStatus() == sf::Music::Paused) {
				backgroundMusic.play();
			}
		}
		else { /* Thêm thông báo lỗi Load SFML */ }
		break;

	case ButtonType::EXIT:
	case ButtonType::EXIT_GAME:
		state = GameState::EXIT;
		break;

	case ButtonType::BACK_TO_MENU:
		state = GameState::MENU;

		// BỔ SUNG: Bật nhạc nền khi quay lại Menu
		if (backgroundMusic.getStatus() == sf::Music::Paused) {
			backgroundMusic.play();
		}
		break;
	}
}

// Cập nhật hiệu ứng HOVER
void Game::updateButtonHover() {
	auto processButtons = [&](std::vector<UIButton>& buttons) {
		for (auto& btn : buttons) {
			if (isMouseOver(btn.shape)) {
				btn.shape.setScale(HOVER_SCALE);
				btn.text.setScale(HOVER_SCALE);
			}
			else {
				btn.shape.setScale(btn.originalScale);
				btn.text.setScale(btn.originalScale);
			}
		}
		};
	if (state == GameState::MENU) processButtons(menuButtons);
	else if (state == GameState::PLAYING) processButtons(playingButtons);
	else if (state == GameState::GAME_OVER) processButtons(gameOverButtons);
}

// Xử lý các sự kiện chính (Chuột, Phím, Đóng cửa sổ)
void Game::processEvents() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) state = GameState::EXIT;

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

			sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

			// Hàm xử lý chung cho mọi nút
			auto processClickAndSound = [&](std::vector<UIButton>& buttons) {
				for (auto& btn : buttons) {
					if (btn.shape.getGlobalBounds().contains(mousePos)) {
						processButtonClick(btn.type);
						moveSound.play();
						return;
					}
				}
				};

			if (state == GameState::MENU) {
				processClickAndSound(menuButtons);
			}
			else if (state == GameState::PLAYING) {
				processClickAndSound(playingButtons);
			}
			else if (state == GameState::GAME_OVER) {
				processClickAndSound(gameOverButtons);
			}
		}

		// --- BƯỚC 2: XỬ LÝ INPUT BÀN PHÍM (Key Pressed) ---
		if (state == GameState::PLAYING && event.type == sf::Event::KeyPressed) {
			Direction dir = Direction::NONE;
			switch (event.key.code) {
			case sf::Keyboard::Up: case sf::Keyboard::W: dir = Direction::UP; break;
			case sf::Keyboard::Left: case sf::Keyboard::A: dir = Direction::LEFT; break;
			case sf::Keyboard::Down: case sf::Keyboard::S: dir = Direction::DOWN; break;
			case sf::Keyboard::Right: case sf::Keyboard::D: dir = Direction::RIGHT; break;
			case sf::Keyboard::L: board.saveToFile("save.txt"); break;
			case sf::Keyboard::Q: state = GameState::EXIT; break;
			default: break;
			}

			if (dir != Direction::NONE) {

				if (board.move(dir)) {
					// Phát âm thanh MERGE cho TẤT CẢ các di chuyển hợp lệ
					mergeSound.play();

					board.spawnRandomTile();

					// KIỂM TRA GAME OVER SAU KHI DI CHUYỂN
					if (!board.canMove()) {
						state = GameState::GAME_OVER;
						backgroundMusic.pause();
						gameOverSound.play();
					}
				}
			}
		}
	}
	// Xử lý Hiệu ứng Rê chuột
	updateButtonHover();
}

//Hàm run game chạy đến khi ấn exit
void Game::run() {
	backgroundMusic.play();
	if (moveSound.getStatus() == sf::Sound::Playing) moveSound.stop();
	if (mergeSound.getStatus() == sf::Sound::Playing) mergeSound.stop();
	while (m_window.isOpen()) {
		processEvents();
		m_window.clear();
		m_window.draw(m_backgroundSprite);

		switch (state) {
		case GameState::MENU: renderMenu(); break;
		case GameState::PLAYING: renderGame(); break;
		case GameState::GAME_OVER: renderGameOver(); break;
		case GameState::EXIT: m_window.close(); break;
		default: break;
		}

		m_window.display();
	}
}

//Hiển thị MENU chính
void Game::renderMenu() {
	m_window.draw(m_welcomeText);
	m_window.draw(m_titleText);

	for (const auto& btn : menuButtons) {
		m_window.draw(btn.shape);
		m_window.draw(btn.text);
	}
}

//Xử lí khi đang chơi
void Game::renderGame() {

	m_window.draw(m_scoreBackground);
	m_window.draw(m_bestBackground);

	// Cập nhật và vẽ Score và Best Score
	m_scoreTextPlaying.setString("SCORE: " + std::to_string(board.score));
	m_bestTextPlaying.setString("BEST: " + std::to_string(m_bestScore));

	m_window.draw(m_scoreTextPlaying);
	m_window.draw(m_bestTextPlaying);

	// Vẽ khung lưới (Board Background)
	m_window.draw(m_boardShape);

	// Duyệt qua từng ô và vẽ
	for (int i = 0; i < Board::SIZE; ++i) {
		for (int j = 0; j < Board::SIZE; ++j) {
			float currentX = m_boardX + m_spacing + j * (m_tileSize + m_spacing);
			float currentY = m_boardY + m_spacing + i * (m_tileSize + m_spacing);

			drawTile(board.grid[i][j], currentX, currentY, m_tileSize);
		}
	}

	// Vẽ các nút New Game và Exit
	for (const auto& btn : playingButtons) {
		m_window.draw(btn.shape);
		m_window.draw(btn.text);
	}

	// --- VẼ VÀ CẬP NHẬT TUYẾT RƠI ---
	for (auto& snowflake : m_snowflakes) {
		// Di chuyển bông tuyết xuống
		snowflake.shape.move(0, snowflake.speed);

		// Nếu bông tuyết ra khỏi màn hình, khởi tạo lại từ trên
		if (snowflake.shape.getPosition().y > WINDOW_HEIGHT) {
			initSnowflake(snowflake);
			// Đặt lại vị trí Y ở phía trên màn hình một chút để không bị giật
			snowflake.shape.setPosition(snowflake.shape.getPosition().x, -snowflake.shape.getRadius());
		}
		m_window.draw(snowflake.shape);
	}
}

void Game::renderGameOver() {
	// 1. Vẽ tiêu đề "GAME OVER!"
	m_window.draw(m_gameOverText);

	// 2. Cập nhật và vẽ Score/Best
	m_scoreText.setString("YOUR SCORE: " + std::to_string(board.score));
	m_bestText.setString("BEST: " + std::to_string(m_bestScore));
	// Cần căn giữa lại text trước khi vẽ
	m_scoreText.setOrigin(m_scoreText.getLocalBounds().width / 2, m_scoreText.getLocalBounds().height / 2);
	m_bestText.setOrigin(m_bestText.getLocalBounds().width / 2, m_bestText.getLocalBounds().height / 2);

	m_window.draw(m_scoreText);
	m_window.draw(m_bestText);

	// 3. Vẽ các nút
	for (const auto& btn : gameOverButtons) {
		m_window.draw(btn.shape);
		m_window.draw(btn.text);
	}
}

// === HÀM VẼ TỪNG Ô ===
void Game::drawTile(const Tile& tile, float x, float y, float size) {
	int value = tile.getValue();

	// 1. Vẽ hình chữ nhật
	sf::RectangleShape rect(sf::Vector2f(size, size));
	rect.setPosition(x, y);
	rect.setFillColor(m_tileColors.count(value) ? m_tileColors[value] : sf::Color::Black);
	rect.setOutlineColor(sf::Color(255, 255, 255, 50));
	rect.setOutlineThickness(3.f);

	m_window.draw(rect);

	// 2. Vẽ văn bản (Số)
	if (value != 0) {
		sf::Text text;
		text.setFont(m_font);
		text.setString(std::to_string(value));

		// Kích thước font
		int charSize;
		if (value < 100) charSize = 50;
		else if (value < 1000) charSize = 40;
		else charSize = 35;
		text.setCharacterSize(charSize);

		// Màu chữ
		text.setFillColor(sf::Color::White);

		// Căn giữa và vẽ
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		text.setPosition(x + size / 2.f, y + size / 2.f);

		m_window.draw(text);
	}
}

//Hiệu ứng tuyết rơi
void Game::initSnowflake(Snowflake& snowflake) {
	float randomX = static_cast<float>(rand() % WINDOW_WIDTH);
	float randomY = static_cast<float>(rand() % (WINDOW_HEIGHT + 100)) - 100;

	float randomSize = MIN_SNOW_SIZE + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (MAX_SNOW_SIZE - MIN_SNOW_SIZE)));
	snowflake.speed = MIN_SNOW_SPEED + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (MAX_SNOW_SPEED - MIN_SNOW_SPEED)));

	snowflake.shape.setRadius(randomSize);
	snowflake.shape.setFillColor(sf::Color::White);
	snowflake.shape.setPosition(randomX, randomY);
}
