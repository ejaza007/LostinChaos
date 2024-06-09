#include "../include/AllyMissile.h"

AllyMissile::AllyMissile() {};

AllyMissile::AllyMissile(float x, float y, Object* target, float angle, SDL_Renderer* renderer, SoundManager* sm)
	: AllyBullet(x, y, target, angle, renderer, MISSILE_BULLET_PNG, ALLY_MISSILE_BULLET_TAG, sm) {
	damage = 5;
}
