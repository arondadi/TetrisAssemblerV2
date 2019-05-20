#include "block.h"
#include "graphics.h"


Block::Block() { }

Block::Block(Graphics &graphics, float x, float y) :
	AnimatedSprite(graphics, "content/sprites/PrtCave.png", 0, 0, 16, 16, x, y, 100)
{
	graphics.loadImage("content/sprites/PrtCave.png");

	this->setupAnimations();
	this->playAnimation("TestBlock");
}

void Block::setupAnimations() {
	this->addAnimation(1, 16, 0, "TestBlock", 16, 16, Vector2(0, 0));
}

void Block::animationDone(std::string currentAnimation) {};


void Block::moveDown() {
	this->_y = this->_y + this->_boundingBox.getHeight();
}

void Block::moveUp() {
	this->_y = this->_y - this->_boundingBox.getHeight();
}

void Block::moveRight() {
	this->_x = this->_x + this->_boundingBox.getWidth();
}

void Block::moveLeft() {
	this->_x = this->_x - this->_boundingBox.getWidth();
}

void Block::update(float elapsedTime) {
	AnimatedSprite::update(elapsedTime);
}

void Block::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}


//const Rectangle Block::getCollisionRects() {
//	this->_collisionRects.push_back(Rectangle(
//		this->_x,
//		this->_y,
//		this->_boundingBox.getWidth(),
//		this->_boundingBox.getHeight()
//	));
//
//	return this->_collisionRects;
//}

std::vector<Rectangle> Block::checkTileCollision(const Rectangle &other) {
	std::vector<Rectangle> others;

	//const Rectangle _collisionRects = this->getCollisionRects();

	this->_collisionRects.push_back(Rectangle(
		this->_x,
		this->_y,
		this->_boundingBox.getWidth(),
		this->_boundingBox.getHeight()
	));

	//for (int i = 0; i < this->_collisionRects.size(); i++) {
	for (int i = 0; i < 1; i++) {
		if (this->_collisionRects.at(i).collidesWith(other)) {
			others.push_back(this->_collisionRects.at(i));
		}
	}

	this->_collisionRects.pop_back();

	return others;
}

//void handleTileCollisions
//Handls collisions with ALL tiles the player is colliding with
void Block::handleTileCollisions(const Rectangle &player) {
	//Figure out what side the collision happend on and move the player accordingly
	//for (int i = 0; i < others.size(); i++) {
	int i = 0;
		sides::Side collisionSide = Sprite::getCollisionSide(player);
		if (collisionSide != sides::NONE) {
			switch (collisionSide) {
			case sides::TOP:
				this->moveDown();
				break;
			case sides::BOTTOM:
				this->moveUp();
				break;
			case sides::LEFT:
				this->moveRight();
				break;
			case sides::RIGHT:
				this->moveLeft();
				break;
			}
		}
	//}
}

// // single collisionRect version
//const Rectangle Block::checkTileCollision(const Rectangle &other) {
//
//	Rectangle others;
//
//	this->_collisionRect = Rectangle(
//		this->_x,
//		this->_y,
//		this->_boundingBox.getWidth(),
//		this->_boundingBox.getHeight()
//	);
//
//	
//	if (this->_collisionRect.collidesWith(other)) {
//		const Rectangle others = this->_collisionRect;
//		//this->moveRight();
//	}
//	
//	return others;
//}