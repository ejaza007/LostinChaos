#pragma once
#include "Trap.h"
#include "AllyMGBullet.h"
#include "Player.h"

class MachineGun : public Trap {
public:
	MachineGun();
	MachineGun(float x, float y, SDL_Renderer* renderer, vector<Object*>* targets, SoundManager* sm);

	// fire funciton override
	void fire(vector<Object*>& list, vector<Object*>& bullets, std::array<Tile*, MAP_LENGTH>& map, double deltaTime);
};

