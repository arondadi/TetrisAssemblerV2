#include "player.h"
#include "graphics.h"

namespace player_constants {
	const float WALK_SPEED = 0.2f;
}

Player::Player() {}

Player::Player(Graphics &graphics, float x, float y) :
	AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100),
	_dx(0),
	_dy(0),
	_facing(RIGHT)
{
	graphics.loadImage("content/sprites/MyChar.png");

	this->setupAnimations();
	this->playAnimation("IdleRight");

}

void Player::setupAnimations() {
	this->addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 112, 0, "RunUp", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 96, 16, "RunDown", 16, 16, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation) {}

void Player::moveLeft() {
	this->_dx = -player_constants::WALK_SPEED;
	this->playAnimation("RunLeft");
	this->_facing = LEFT;
}

void Player::moveRight() {
	this->_dx = player_constants::WALK_SPEED;
	//this->_dx = this->_boundingBox.getWidth();
	this->playAnimation("RunRight");
	this->_facing = RIGHT;
}

void Player::moveUp() {
	this->_dy = -player_constants::WALK_SPEED;
	this->playAnimation("RunUp");
	this->_facing = UP;
}

void Player::moveDown() {
	this->_dy = player_constants::WALK_SPEED;
	this->playAnimation("RunDown");
	this->_facing = DOWN;
}

void Player::stopMovingHorizontal() {
	this->_dx = 0.0f;
}

void Player::stopMovingVertical() {
	this->_dy = 0.0f;
	//this->playAnimation(this->_facing == UP ? "IdleRight" : "IdleLeft");
}

void Player::stopMoving() {
	this->_dx = 0.0f;
	this->_dy = 0.0f;
	this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

//void handleTileCollisions
//Handls collisions with ALL tiles the player is colliding with
void Player::handleTileCollisions(std::vector<Rectangle> &others) {
	//Figure out what side the collision happend on and move the player accordingly
	for (int i = 0; i < others.size(); i++) {
		sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
		if (collisionSide != sides::NONE) {
			switch (collisionSide) {
			case sides::TOP:
				this->_y = others.at(i).getBottom() + 1;
				break;
			case sides::BOTTOM:
				this->_y = others.at(i).getTop() - this->_boundingBox.getHeight() - 1;
				break;
			case sides::LEFT:
				this->_x = others.at(i).getRight() + 1;
				break;
			case sides::RIGHT:
				this->_x = others.at(i).getLeft() - this->_boundingBox.getWidth() - 1;
				break;
			}
		}
	}
}

////void handleTileCollisions single collisionRect
////Handls collisions with ALL tiles the player is colliding with
//void Player::handleTileCollisions(Rectangle &others) {
//	//Figure out what side the collision happend on and move the player accordingly
//		sides::Side collisionSide = Sprite::getCollisionSide(others);
//		if (collisionSide != sides::NONE) {
//			switch (collisionSide) {
//			case sides::TOP:
//				this->_y = others.getBottom() + 1;
//				break;
//			case sides::BOTTOM:
//				this->_y = others.getTop() - this->_boundingBox.getHeight() - 1;
//				break;
//			case sides::LEFT:
//				this->_x = others.getRight() + 1;
//				break;
//			case sides::RIGHT:
//				this->_x = others.getLeft() - this->_boundingBox.getWidth() - 1;
//				break;
//			}
//		}
//}

void Player::update(float elapsedTime) {
	//Move by dx
	/*if (this->_dx != 0) {
		this->_x = this->_x + this->_dx;
	}*/
	
	this->_x += this->_dx * elapsedTime;

	//Move by dy
	this->_y += this->_dy*elapsedTime;

	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}