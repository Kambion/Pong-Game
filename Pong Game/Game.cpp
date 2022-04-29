#include "Game.hpp"

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
	ball.setVelocity(400, 400);
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
		draw();
		eventEndGame();
	}
}

void Game::draw() {
	window.drawBackground();
	window.drawString(5, 2, "GAME", 40, Fonts::ARIAL, { 255, 255, 255 });
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
				state = State::EXIT;
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
	timer.tick();
}