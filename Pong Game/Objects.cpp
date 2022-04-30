#include "Objects.hpp"

void Object::move() {
	position.x += velocity.velX * timer.delta;
	position.y += velocity.velY * timer.delta;
	checkBorder();
}
void Object::setVelocity(int x, int y) {
	velocity.velX = x;
	velocity.velY = y;
}
void Object::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}
void Object::bounce(Direction direction) {
	switch (direction)
	{
	case Direction::HORIZONTAL:
		velocity.velX *= -1;
		break;
	case Direction::VERTICAL:
		velocity.velY *= -1;
		break;
	}
}

void Ball::draw() {
	window.drawCircle(position.x, position.y, radius, radius+1, window.colors.blue);
}
void Bumper::draw() {
	window.drawRectangle(SDL_Rect{ (int)position.x, (int)position.y, width, height }, window.colors.red);
	//window.drawCircle(position.x, position.y, 3, 3, window.colors.green);
}
void Ball::checkBorder() {
	if (position.x < radius+10 && velocity.velX < 0) {
		bounce(Direction::HORIZONTAL);
	}
	if (position.x > window.width() - radius-10 && velocity.velX > 0) {
		bounce(Direction::HORIZONTAL);
	}
	if (position.y < radius + 10 && velocity.velY < 0) {
		bounce(Direction::VERTICAL);
	}
	if (position.y > window.height() - radius-10 && velocity.velY > 0) {
		bounce(Direction::VERTICAL);
	}
}
void Bumper::checkBorder() {
	if (position.x < 10 && velocity.velX < 0) {
		velocity.velX = 0;
	}
	if (position.x + width > window.width() - 10 && velocity.velX > 0) {
		velocity.velX = 0;
	}
}
bool Ball::checkCollision(Object& other) {
	if (position.y + radius >= other.getY() && position.x >= other.getX() && position.x <= other.getX() + other.getRadius()) {
		if (velocity.velY > 0) {
			bounce(Direction::VERTICAL);
			return true;
		}
	}
	return false;
}