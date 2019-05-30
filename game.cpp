#include <SDL.h>
#include <algorithm>

#include "game.h"
#include "graphics.h"
#include "input.h"



/*Game class
This class holds all inormation for our main game loop
*/

namespace {
	const int FPS = 60;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event;

	// Instance player object
	this->_player = Player(graphics, 320, 320);

	// Test block
	this->_block = Block(graphics, 416, 416);
	

	// Todo: make a moveble block

	// Used to limit fps 
	int LAST_UPDATE_TIME = SDL_GetTicks();

	//Start the game loop
	while (true) {
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}

		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}
		else if (input.wasKeyPressed(SDL_SCANCODE_LEFT) == true) {
				this->_player.moveLeft();
		}
		else if (input.wasKeyPressed(SDL_SCANCODE_RIGHT) == true) {
				this->_player.moveRight();
		}
		else if (input.wasKeyPressed(SDL_SCANCODE_DOWN) == true) {
				this->_player.moveDown();
		}
		else if (input.wasKeyPressed(SDL_SCANCODE_UP) == true) {	
				this->_player.moveUp();	
		}

		if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)
			&& !input.isKeyHeld(SDL_SCANCODE_UP) && !input.isKeyHeld(SDL_SCANCODE_DOWN)) {
			this->_player.stopMoving();
		}

		// // 
		//else if (!input.isKeyHeld(SDL_SCANCODE_UP) && !input.isKeyHeld(SDL_SCANCODE_DOWN)) {
		//	if (input.wasKeyPressed(SDL_SCANCODE_LEFT) == true) {
		//		this->_player.moveLeft();
		//	}
		//	else if (input.wasKeyPressed(SDL_SCANCODE_RIGHT) == true) {
		//		this->_player.moveRight();
		//	}
		//}
		//else if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
		//	if (input.wasKeyPressed(SDL_SCANCODE_DOWN) == true) {
		//		this->_player.moveDown();
		//	}
		//	else if (input.wasKeyPressed(SDL_SCANCODE_UP) == true) {
		//		this->_player.moveUp();
		//	}
		//}
		//if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)
		//	&& !input.isKeyHeld(SDL_SCANCODE_UP) && !input.isKeyHeld(SDL_SCANCODE_DOWN)) {
		//	this->_player.stopMoving();
		//}



		// Limiting fps 
		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {
	graphics.clear();


	/*Player is drawn on top of level*/
	this->_player.draw(graphics);

	this->_block.draw(graphics);

	graphics.flip();
}

void Game::update(float elapsedTime) {
	this->_player.update(elapsedTime);
	this->_block.update(elapsedTime);

	// Check collisions
	std::vector<Rectangle> others;

	if ((others = this->_block.checkTileCollision(this->_player.getBoundingBox())).size() > 0) {

		this->_block.handleTileCollisions(this->_player.getBoundingBox());

		//Player collided with at least one tile. Handle it.
		this->_player.handleTileCollisions(others);
	
	}

	// single collision version Check collisions
	/*Rectangle others;
	(others = this->_block.checkTileCollision(this->_player.getBoundingBox()));*/
	//if ((others = this->_block.checkTileCollision(this->_player.getBoundingBox()))) {
	//	//Player collided with at least one tile. Handle it.
	//	this->_player.handleTileCollisions(others);
	//}
}