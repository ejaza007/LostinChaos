#include "../include/AllyMGBullet.h"

AllyMGBullet::AllyMGBullet() {};

AllyMGBullet::AllyMGBullet(float x, float y, Object* target, float angle, SDL_Renderer* renderer, SoundManager* sm)
	: AllyBullet(x, y, target, angle, renderer, MG_BULLET_PNG, ALLY_MG_BULLET_TAG, sm) {
	damage = 1;
	
}