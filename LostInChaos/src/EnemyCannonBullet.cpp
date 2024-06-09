#include "../include/EnemyCannonBullet.h"

EnemyCannonBullet::EnemyCannonBullet() {};

EnemyCannonBullet::EnemyCannonBullet(float x, float y, Object* target, float angle, SDL_Renderer* renderer, SoundManager* sm) :
	EnemyBullet(x, y, target, angle, renderer, ENEMY_CANNON_BULLET_PNG, ALLY_CANNON_BULLET_TAG, sm) {
	damage = 3;
}