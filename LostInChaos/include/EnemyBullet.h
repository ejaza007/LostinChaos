#pragma once
#include "Bullet.h"
#include "helper.h"

// class for hostile bullets
class EnemyBullet : public Bullet {
public:
	// default ctor
	EnemyBullet();

	// overloaded ctor for hostile bullets
	EnemyBullet(float x, float y, Object* target, float Angle, SDL_Renderer* renderer, std::string path, int type, SoundManager* sm);

	void move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime);


};