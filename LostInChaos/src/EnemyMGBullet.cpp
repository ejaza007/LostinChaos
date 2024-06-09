#include "../include/EnemyMGBullet.h"

EnemyMGBullet::EnemyMGBullet() {};

EnemyMGBullet::EnemyMGBullet(float x, float y, Object* target, float angle, SDL_Renderer* renderer, SoundManager* sm)
	: EnemyBullet(x, y, target, angle, renderer, ENEMY_MG_BULLET_PNG, ENEMY_MG_BULLET_TAG, sm) {
	damage = 2;

}