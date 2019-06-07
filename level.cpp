#include "level.h"

Level::Level(){}

Level::Level(Graphics &graphics)
{

	// Initialize empty level
	initLevel();
}

Level::~Level(){}

void Level::initLevel() {
	for (int i = 0; i < globals::LEVEL_WIDTH; i++) {
		for (int j = 0; j < globals::LEVEL_HEIGHT; j++)
		{
			mLevel[i][j] = POS_FREE;
		}
	}
}

bool Level::isGameOver()
{
	for (int i = 0; globals::LEVEL_WIDTH; i++)
	{
		if (mLevel[i][0] == POS_FILLED)
		{
			return true;
		}
	}
	return false;
}

void Level::update(int elapsedTime) {

}

void Level::draw(Graphics &graphics)
{

}