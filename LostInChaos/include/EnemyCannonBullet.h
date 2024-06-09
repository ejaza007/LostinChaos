#pragma once
#include "EnemyBullet.h"
#include "helper.h"

// class for machine gun bullet
class EnemyCannonBullet : public EnemyBullet {
public:
	// default ctor
	EnemyCannonBullet();

	// overloaded ctor for cannon gun bullet
	EnemyCannonBullet(float x, float y, Object* target, float angle, SDL_Renderer* renderer, SoundManager* sm);

};