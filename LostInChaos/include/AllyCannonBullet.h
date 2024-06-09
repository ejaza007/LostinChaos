#pragma once
#include "AllyBullet.h"
#include "helper.h"

// class for machine gun bullet
class AllyCannonBullet : public AllyBullet {
public:
	// default ctor
	AllyCannonBullet();

	// overloaded ctor for cannon gun bullet
	AllyCannonBullet(float x, float y, Object* target, float angle, SDL_Renderer* renderer, SoundManager* sm);

};