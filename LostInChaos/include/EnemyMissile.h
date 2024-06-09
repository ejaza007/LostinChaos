#pragma once
#include "EnemyBullet.h"
#include "helper.h"

// class for machine gun bullet
class EnemyMissile : public EnemyBullet {
public:
	// default ctor
	EnemyMissile();

	// overloaded ctor for cannon gun bullet
	EnemyMissile(float x, float y, Object* target, float angle, SDL_Renderer* renderer, SoundManager* sm);

};