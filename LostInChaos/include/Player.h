#pragma once
#include "Object.h"
#include "Astar.h"

class Player : public Object {
	
public:
	Player();
	Player(float x, float y, SDL_Renderer* renderer, SoundManager* sm);

	void move(std::array<Tile*, MAP_LENGTH> &map, double deltaTime);

	void handleInput();

	void render();

private:
	
	// function that clips the sprite sheet of player
	void clipSheet();

	SDL_Rect rects[6];

	int frame;

	int frameCounter;
};