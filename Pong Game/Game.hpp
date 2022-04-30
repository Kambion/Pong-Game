#pragma once
#include "SDLgraphics.hpp"
#include "Objects.hpp"

class Game {
private:
	enum class State { MENU, GAME, ENDG, EXIT };
	struct {
		int points = 0;
		int highscore = 0;
	}counter;
	bool running = false;
	static constexpr std::string_view TITLE = "PONG GAME";
	static constexpr int SCREEN_WIDTH = 1080;
	static constexpr int SCREEN_HEIGHT = 720;
	static constexpr int BUMPER_HEIGHT = 30;
	static constexpr int BUMPER_WIDTH = 300;
	static constexpr int BUMPER_START_Y = 650;
	static constexpr int BUMPER_START_X = SCREEN_WIDTH / 2 - BUMPER_WIDTH / 2;
	Timer timer{};
	State state = State::MENU;
	SDLWindow window{ SCREEN_WIDTH, SCREEN_HEIGHT, TITLE };
	Ball ball{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 15, timer, window };
	Bumper bumper{ BUMPER_START_X, BUMPER_START_Y, BUMPER_WIDTH, BUMPER_HEIGHT, timer, window };
public:
	void run();
private:
	void eventMenu();
	void event();
	void eventEndGame();
	void menuLoop();
	void mainLoop();
	void endGameLoop();
	void drawMenu();
	void draw();
	void drawEnd();
	void updateWorld();
	void reset();
	void start();
};