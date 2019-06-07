#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"
#include "globals.h"

/*
- Keeps track of every blocks location on the screen
- Checks for collision
- Checks if movement is possible
*/

class Level {
public:
	Level();
	Level(Graphics &graphics);
	~Level();
	
	void update(int elapsedTime);
	void draw(Graphics &graphics);

	bool isCollision(); // What should be checked?

	bool isMovePossible();

	// Checks if there is block in the top position
	bool isGameOver();

	// 
	void storePieces(int _x, int _y, int _pieces, int _rotation);


private:
	enum { POS_FREE, POS_FILLED };

	// Keeps track of wether location is empty or not
	bool mLevel[globals::LEVEL_WIDTH][globals::LEVEL_HEIGHT];

	// Initalize the level with empty position
	void initLevel();
};


#endif
