#pragma once
#include "AllyBullet.h"
#include "helper.h"

// class for machine gun bullet
class AllyMissile : public AllyBullet {
public:
	// default ctor
	AllyMissile();

	// overloaded ctor for machine gun bullet
	AllyMissile(float x, float y, Object* target, float angle, SDL_Renderer* renderer, SoundManager* sm);

};