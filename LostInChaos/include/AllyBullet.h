#pragma once
#include "Bullet.h"
#include "helper.h"

// class for friendly bullets
class AllyBullet : public Bullet {
public:
	// default ctor
	AllyBullet();

	// overloaded ctor for friendly bullets
	AllyBullet(float x, float y, Object* target, float Angle, SDL_Renderer* renderer, std::string path, int type, SoundManager* sm);

};