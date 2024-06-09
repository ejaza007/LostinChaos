#pragma once
#include "Trap.h"
#include "AllyCannonBullet.h"
#include "Player.h"

class Cannon : public Trap {
public:
	Cannon();
	Cannon(float x, float y, SDL_Renderer* renderer, vector<Object*>* targets, SoundManager* sm);

	// fire funciton override
	void fire(vector<Object*>& list, vector<Object*>& bullets, std::array<Tile*, MAP_LENGTH>& map, double deltaTime);
};

