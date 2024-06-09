#include "../include/EnemyMissile.h"

EnemyMissile::EnemyMissile() {};

EnemyMissile::EnemyMissile(float x, float y, Object* target, float angle, SDL_Renderer* renderer, SoundManager* sm)
	: EnemyBullet(x, y, target, angle, renderer, ENEMY_MISSILE_BULLET_PNG, ENEMY_MISSILE_BULLET_TAG, sm) {
	damage = 3;

}