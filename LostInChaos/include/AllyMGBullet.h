#pragma once
#include "AllyBullet.h"
#include "helper.h"

// class for machine gun bullet
class AllyMGBullet : public AllyBullet {
public:
	// default ctor
	AllyMGBullet();
	
	// overloaded ctor for machine gun bullet
	AllyMGBullet(float x, float y, Object* target, float angle,  SDL_Renderer* renderer, SoundManager* sm);

};