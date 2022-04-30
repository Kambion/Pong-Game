#include "Game.hpp"
#include <sstream>

void Timer::tick() {
	t2 = SDL_GetTicks();
	delta = (1. * t2 - t1) * 0.001;
	t1 = t2;

	worldTime += delta;

	fpsTimer += delta;
	if (fpsTimer > 0.5) {
		fps = frames * 2.;
		frames = 0;
		fpsTimer -= 0.5;
	}
	frames++;
}

void Game::run() {
	menuLoop();
	mainLoop();
	endGameLoop();
}

void Game::mainLoop() {
	while (state == State::GAME) {
		event();
		updateWorld();
		draw();
	}
}

void Game::menuLoop() {
	while (state == State::MENU) {
		drawMenu();
		eventMenu();
	}
}

void Game::endGameLoop() {
	while (state == State::ENDG) {
		drawEnd();
		eventEndGame();
	}
}

void Game::draw() {
	window.drawBackground();
	std::stringstream score;
	score << "Highscore: " << counter.highscore;
	window.drawString(5, 2, score.str(), 30, Fonts::ARIAL, { 255, 255, 255 });
	score.str("");
	score << "Score: " << counter.points;
	window.drawString(5, 32, score.str(), 30, Fonts::ARIAL, { 255, 255, 255 });
	ball.draw();
	bumper.draw();
	window.update();
}

void Game::drawMenu() {
	window.drawBackground();
	window.drawString(5, 2, "MENU", 40, Fonts::ARIAL, { 255, 255, 255 });
	window.update();
}

void Game::drawEnd() {
	window.drawBackground();
	window.drawString(5, 2, "END", 40, Fonts::ARIAL, { 255, 255, 255 });
	window.update();
}

void Game::event() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				state = State::ENDG;
				break;
			case SDLK_SPACE:
				start();
				break;
			case SDLK_d:
				bumper.setVelocity(300, 0);
				break;
			case SDLK_a:
				bumper.setVelocity(-300, 0);
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_d:
				break;
			case SDLK_a:
				break;
			case SDL_QUIT:
				state = State::EXIT;
				break;
			}
		};
	};
}

void Game::eventEndGame() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				state = State::EXIT;
				break;
			}
			break;
		case SDL_KEYUP:
			break;
		case SDL_QUIT:
			state = State::EXIT;
			break;
		};
	};
}

void Game::eventMenu() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				state = State::EXIT;
				break;
			case SDLK_SPACE:
				state = State::GAME;
				break;
			}
			break;
		case SDL_KEYUP:
			break;
		case SDL_QUIT:
			state = State::EXIT;
			break;
		};
	};
}
void Game::updateWorld() {
	ball.move();
	bumper.move();
	if (ball.checkCollision(bumper)) {
		counter.points++;
	}
	if (counter.points > counter.highscore) {
		counter.highscore = counter.points;
	}
	if (ball.getY() > bumper.getY() + 10) {
		counter.points = 0;
		reset();
	}
	timer.tick();
}
void Game::reset() {
	running = false;
	ball.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3);
	ball.setVelocity(0, 0);
	bumper.setPosition(BUMPER_START_X, BUMPER_START_Y);
	bumper.setVelocity(0, 0);
}
void Game::start() {
	if (!running) {
		running = true;
		int velX = rand() % 800 - 400;
		ball.setVelocity(velX, 400);
	}
}