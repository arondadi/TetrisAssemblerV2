#ifndef BLOCK_H
#define BLOCK_H

#include "animatedsprite.h"
#include "globals.h"
#include "rectangle.h"


class Block : public AnimatedSprite {
public:
	Block();
	Block(Graphics &graphics, float x, float y);

	void draw(Graphics &graphics);
	void update(float elapsedTime);

	// The block can move in all direction
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();

	const Rectangle getCollisionRects();
	
	// Vector version of collisionRect
	std::vector<Rectangle> checkTileCollision(const Rectangle &other);
	void handleTileCollisions(std::vector<Rectangle> &other);

	// Check single collision
	//const Rectangle checkTileCollision(const Rectangle &other);

	// Maybe remove
	//void handleTileCollisions(std::vector<Rectangle> &other);
private:
	// Vector of collisionRects
	std::vector<Rectangle> _collisionRects;

protected:
	//Single collisionRect
	//Rectangle _collisionRect;

};

#endif // !BLOCK_H
