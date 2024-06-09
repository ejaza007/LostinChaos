#include "../include/MissileLauncher.h"

MissileLauncher::MissileLauncher() {};

MissileLauncher::MissileLauncher(float x, float y, SDL_Renderer* renderer, vector<Object*>* targets, SoundManager* sm)
	: Trap(x, y, targets, renderer, MISSILE_LAUNCHER_PNG, MISSILE_LAUNCHER, sm) {
	// 2 seconds cooldown for cannon turret
	cooldown = 3;
}

void MissileLauncher::fire(vector<Object*>& list, vector<Object*>& bullets, std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {
	bool target = false;

	t = nullptr;
	// find target
	for (int i = 0; i < targets->size(); i++) {
		if (targets->at(i)->getType() == SOLDIER_TAG || targets->at(i)->getType() == HITMAN_TAG ||
			targets->at(i)->getType() == ZOMBIE_TAG) {
			if (LineOfSight(targets->at(i), 30, map, deltaTime)) {
				target = true;
				t = targets->at(i);
			}
		}
	}
	// if no target do nothing
	if (!target) { return; }

	//fire at target
	if (!shot) {
		// calculate radian angle
		double radAngle = (90 - angle) * (PI / 180);

		// calculate middle values of cannon
		double originX = x + (double)collisionRect.w / 4;
		double originY = y + (double)collisionRect.h / 2;

		// set a radius for the circle
		int radius = -(collisionRect.h);

		// calculate x, y coordinates for the bullet to be fired
		double bX = originX - radius * cos(radAngle);
		double bY = originY + radius * sin(radAngle);

		// create a cannon bullet object
		Object* cBullet = new AllyMissile((float)bX, (float)bY, t, (float) angle, renderer, sm);

		// insert into bullets vector
		bullets.insert(bullets.begin(), cBullet);

		shot = true;
		timer.start();

		sm->playSound(MISSILE_SOUND);
	}
	else {
		// if bullet was already previously shot, check if cooldown period has passed
		if (timer.getTicks() / 1000 >= cooldown) {
			// if the cooldown period has passed 
			// set shot to false and reset timer;
			shot = false;
			timer.stop();
		}
	}
}