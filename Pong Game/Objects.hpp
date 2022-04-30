#pragma once
#include "SDLgraphics.hpp"

enum class Direction {
	HORIZONTAL,
	VERTICAL
};

struct Timer {
	int t1, t2 = 0, frames = 0;
	double delta = 0, worldTime = 0, fpsTimer = 0, fps = 0;

	Timer() : t1(SDL_GetTicks()) {}

	void tick();
};

class Object {
protected:
	Timer& timer;
	SDLWindow& window;
	struct Velocity {
		double velX = 0;
		double velY = 0;
	};
	struct Position {
		double x;
		double y;
	};
	Position position;
	Velocity velocity = { 0, 0 };
	virtual void checkBorder() = 0;
public:
	Object(double x, double y, Timer& timer, SDLWindow& window) : timer(timer), window(window) {
		position = { x, y };
	}
	double getX() { return position.x; }
	double getY() { return position.y; }
	virtual int getRadius() = 0;
	virtual void draw() = 0;
	void move();
	void bounce(Direction direction);
	void setVelocity(int x, int y);
	void setPosition(int x, int y);
	virtual bool checkCollision(Object& other) = 0;
};

class Ball : public Object {
private:
	int radius;
	void checkBorder() override;
public:
	Ball(double x, double y, int radius, Timer& timer, SDLWindow& window) : Object(x, y, timer, window), radius(radius) {}
	void draw() override;
	int getRadius() override { return radius; }
	bool checkCollision(Object& other) override;
};

class Bumper : public Object {
private:
	int width, height;
	void checkBorder() override;
public:
	Bumper(double x, double y, int width, int height, Timer& timer, SDLWindow& window) : Object(x, y, timer, window), width(width), height(height) {}
	void draw() override;
	int getRadius() override { return width; }
	bool checkCollision(Object& other) override { return false; }
};