#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "sprite.h"
#include "player.h"
#include "block.h"

class Graphics;

class Game {
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	Player _player;
	Block _block;
};

#endif // !GAME_H

