#include "../include/EnemyBullet.h"

EnemyBullet::EnemyBullet() {};

EnemyBullet::EnemyBullet(float x, float y, Object* target, float Angle, SDL_Renderer* renderer, std::string path, int type, SoundManager* sm)
	: Bullet(x, y, target, Angle, renderer, path, type, sm) {
	damage = 1;

	double diffX = target->getX() - x;
	double diffY = target->getY() - y;

	double* unitVectors = calcVector(diffX, diffY);
	unitX = unitVectors[0];
	unitY = unitVectors[1];
	angle = calcAngle(diffX, diffY);

}

void EnemyBullet::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {
	// if bullet collides with wall - destroy it
	if (wallCollision(map, collisionRect)) {
		alive = false;
	}
	else {
		// if bullet is in screen , move it
		if (y > 0) y += (float)(unitY * (deltaTime / 7));
		if (y > SCREEN_HEIGHT) alive = false;

		if (x > 0 && x < SCREEN_WIDTH - collisionRect.w) x += (float)(unitX * (deltaTime / 7));
		else alive = false;
	}

	collisionRect.x = (int)x;
	collisionRect.y = (int)y;
}