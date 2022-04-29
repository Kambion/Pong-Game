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
void Ball::checkBorder() {
	if (position.x < radius && velocity.velX < 0) {
		bounce(Direction::HORIZONTAL);
	}
	if (position.x > window.width() - radius && velocity.velX > 0) {
		bounce(Direction::HORIZONTAL);
	}
	if (position.y < radius && velocity.velY < 0) {
		bounce(Direction::VERTICAL);
	}
	if (position.y > window.height() - radius && velocity.velY > 0) {
		bounce(Direction::VERTICAL);
	}
}