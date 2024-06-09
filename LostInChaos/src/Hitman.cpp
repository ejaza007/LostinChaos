#include "../include/Hitman.h"

Hitman::Hitman() {};

Hitman::Hitman(float x, float y, SDL_Renderer* renderer, Map* map, Object* player, vector<Object*>* objects, SoundManager* sm)
	: Enemy(x, y, renderer, map, player, objects, HITMAN_PNG, HITMAN_TAG, sm) {

	health = 1;
	clipSheet();
	collisionRect.w = rects[0].w;
}


void Hitman::render() {
	if (attackPlayer || attackTurret) frame = 1;
	else frame = 0;
	sprite->renderCopyEx(&rects[frame], &collisionRect, nullptr, angle);
}

void Hitman::fire(vector<Object*>& list, vector<Object*>& bullets, std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {

	if (!attackPlayer && !attackTurret) return;

	//fire at target
	if (!shot) {
		// calculate radian angle
		double radAngle = (angle) * (PI / 180);

		// calculate middle values of cannon
		double originX = x + (double)collisionRect.w / 2;
		double originY = y + (double)collisionRect.h / 2;

		// set a radius for the circle
		int radius = 10;

		// calculate x, y coordinates for the bullet to be fired
		double bX = originX - radius * cos(radAngle);
		double bY = originY + radius * sin(radAngle);

		Object* cBullet;

		if (attackPlayer) {
			cBullet = new EnemyMGBullet((float)bX, (float)bY, playerObj, (float)angle, renderer, sm);
		}
		else {
			cBullet = new EnemyMGBullet((float)bX, (float)bY, turret, (float)angle, renderer, sm);
		}
		// insert into bullets vector
		bullets.insert(bullets.begin(), cBullet);

		shot = true;
		timer.start();

		sm->playSound(ENEMY_SHOT_SOUND);

	}
	else {
		// if bullet was already previously shot, check if cooldown period has passed
		if (timer.getTicks() / 1000 >= 1) {
			// if the cooldown period has passed 
			// set shot to false and reset timer;
			shot = false;
			timer.stop();
		}
	}

	
}

void Hitman::clipSheet() {
	// Coordinates of sprites in sprite sheet 
// Total sprites: 2
// i = row, j = col, (i, j)
// (0, 0)
	rects[0].x = 0;
	rects[0].y = 0;
	rects[0].w = 32;
	rects[0].h = 32;
	// (0, 1)
	rects[1].x = 32;
	rects[1].y = 0;
	rects[1].w = 32;
	rects[1].h = 32;

}
