#pragma once
#include "SDLgraphics.hpp"
#include "Objects.hpp"

class Game {
private:
	enum class State { MENU, GAME, ENDG, EXIT };

	static constexpr std::string_view TITLE = "PONG GAME";
	static constexpr int SCREEN_WIDTH = 1080;
	static constexpr int SCREEN_HEIGHT = 720;
	Timer timer{};
	State state = State::MENU;
	SDLWindow window{ SCREEN_WIDTH, SCREEN_HEIGHT, TITLE };
	Ball ball{ 300, 300, 15, timer, window };
	Bumper bumper{ 10, 650, 300, 30, timer, window };
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
};