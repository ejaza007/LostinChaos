#pragma once
#include "EnemyBullet.h"
#include "helper.h"

// class for machine gun bullet
class EnemyMGBullet : public EnemyBullet {
public:
	// default ctor
	EnemyMGBullet();

	// overloaded ctor for cannon gun bullet
	EnemyMGBullet(float x, float y, Object* target, float angle, SDL_Renderer* renderer, SoundManager* sm);

};