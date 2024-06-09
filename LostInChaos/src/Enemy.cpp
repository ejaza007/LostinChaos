#include "../include/Enemy.h"

Enemy::Enemy() {};

Enemy::Enemy(float x, float y, SDL_Renderer* renderer, Map* map, Object* player, vector<Object*>* objects, 
	std::string filename, int type, SoundManager* sm)
	: Object(x, y, renderer, filename, sm, type) {

	this->objects = objects;
	// calculate A* path from current pos to player pos
	this->map = map;
	playerObj = player;

}

void Enemy::render() {
	SDL_Rect src = { 0,0, collisionRect.w, collisionRect.h };
	sprite->renderCopyEx(&src, &collisionRect, nullptr, angle);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//testing purposes
	SDL_RenderDrawRect(renderer, &collisionRect);
}

/*
Enemy AI movement based on the following rules:
	1. Look for nearby objects and player
	2. If found in a certain range, check to see if wall isn't blocking player
	3. If wall is blocking, keep follwing A star path to player
	4. If no nearby objects / player found - genearte A star path and follow it
	5. If found - set attack mode to true and fire
*/
void Enemy::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {

	if ((int) x > 1200) {
		angle = 180;
		translate(1, 0);
	}
	else {

		Astar astar(playerObj, this);

		// set attack mode to false everytimes
		attackTurret = false;
		attackPlayer = false;

		if (turret == nullptr) {
			// iterate over list of objects to see if any turret is in sight
			for (int i = 0; i < objects->size(); i++) {

				// fetch object
				Object* obj = objects->at(i);

				// if obj is nullptr skip
				if (obj == nullptr) continue;

				// get object type
				int otype = obj->getType();

				// only calculate if the type of object is either of the turrets
				if (otype == MACHINE_GUN || otype == CANNON || otype == MISSILE_LAUNCHER) {

					// get delta x and delta y from enmey to object
					float dx = obj->getX() - x;
					float dy = obj->getY() - y;

					// calculate the diagonal distance from enemy to object
					float mObj = (float) sqrt(pow(dx, 2) + pow(dy, 2));

					// if the enemy is within 200 diagonal distance of the turret
					if (mObj <= 300) {

						// if tthe turret is in line of sight, stop moving and set attackMode to true
						if (LineOfSight(obj, 100, map, deltaTime)) {
							// calculate angle between turret and enemy
							angle = angle = calcAngle(obj->getX() - x, obj->getY() - y) - 90;
							// set attackMode to true
							attackTurret = true;
							turret = obj;
							// return function
							return;
						}
					}
				}
			}
		}
		else {
			angle = angle = calcAngle(turret->getX() - x, turret->getY() - y) - 90;
			// set attackMode to true
			attackTurret = true;
			
			return;
		}

		// calculate delta x and y between player and enemy
		float diffX = playerObj->getX() - x;
		float diffY = playerObj->getY() - y;

		// calculate diagonal distance from player to enemy
		float mag = (float) sqrt(pow(diffX, 2) + pow(diffY, 2));

		// carry out same steps as above if the player is found in sight without and walls in between
		if (mag <= 200) {
			if (LineOfSight(playerObj, 70, map, deltaTime)) {
				angle = calcAngle(diffX, diffY) - 90;
				attackPlayer = true;
				path = astar.astar(map);
				return;
			}
		}

		// create astar algorithm object and pass it player target, and enemy object
		// since only the player needs to be followed


		// only calculate a* path if the previous path is already empty
		if (path.size() == 0) {
			path = astar.astar(map);
		}

		// if the stack is not empty, start following path
		if (path.size() != 0) {

			// get the point on stack top - the next path location
			SDL_Point* k = path.top();

			// adjust points to center of tile and calculate delta x and delta y between enemy position and player position
			int dx = (int)x - (k->x + collisionRect.w / 2);
			int dy = (int)y - (k->y + collisionRect.h / 2);

			// sign values that will determine the direction of movement
			int signX = 1;
			int signY = 1;

			// if the difference of location is negative, set signs to negative respectively
			if (dy < 0) signY = -1;
			if (dx < 0) signX = -1;


			// if the abs difference in x and y is less than or equal to 2 i.e. very minmal, pop this point
			// and move on to next point
			if (abs(dx) <= 2 && abs(dy) <= 2) {
				path.pop();
				// deallocate memory
				delete k;
			}
			else {
				// if dy is not 0 , keep moving to reach the y point of path
				if (abs(dy) != 0) {

					// determines the direction of movement based on sign and sets angle of rotation

					if (signY < 0) {
						translate(0, -1.0);
						angle = 90;
					}
					else {
						angle = -90;
						translate(0, 1.0);
					}
				}
				// if dx is not 0, keep moving to reach x point of path
				if (abs(dx) != 0) {

					// determines direction of x movement and changes angle

					if (signX < 0) {
						translate(-1, 0);
						angle = 0;
					}
					else {
						angle = -180;
						translate(1, 0);
					}
				}
			}
		}
	}

	// future values of x and y calculate before moving
	// multiplied by 5 to have some distance before it collides, in order to prevent getting stuck 

	int tempX = (int)(x - (tx * 5));
	int tempY = (int)(y - (ty * 5));

	// a rect to test against wall collision before hand
	SDL_Rect wallCollisionRect = { tempX, tempY, collisionRect.w, collisionRect.h };


	// if object does not collide with wall, move it
	if (!(wallCollision(map, wallCollisionRect))) {
		x -= tx * (float)deltaTime / 23;
		y -= ty * (float)deltaTime / 23;
	}
	// else return
	else return;

	// add friciotn
	tx *= friction;
	ty *= friction;

	// change collisionRect x and y values
	collisionRect.x = (int)x;
	collisionRect.y = (int)y;
}

bool Enemy::LineOfSight(Object* t, int SightRadius, std::array<Tile*, MAP_LENGTH>& map, double deltatime) {

	SDL_Rect Rect = SDL_Rect();

	SDL_Rect* targetRect = &t->getCollisionRect();

	Rect.w = 32;
	Rect.h = 32;
	Astar astar;

	Rect.x = astar.calc_x((int)(x));
	Rect.y = astar.calc_y((int)(y));

	float Vy = t->getY() + targetRect->h / 2 - collisionRect.y - collisionRect.h / 2;
	float Vx = t->getX() + targetRect->w / 2 - collisionRect.x - collisionRect.w / 2;
	float M = sqrt(Vy * Vy + Vx * Vx);

	float stepY = Vy / M;
	float stepX = Vx / M;
	float currStepX = stepX;
	float currStepY = stepY;
	bool isWall = false;
	bool foundTarget = false;


	for (int i = 0; i < SightRadius; i++) {

		if (checkCollision(*targetRect, Rect, 0)) {
			Rect.x += (int)stepX;
			Rect.y += (int)stepY;
			angle = 180 * atan2((double)stepY, (double)stepX) / 3.14 + 90;
			foundTarget = true;
			return true;
		}

		int index = MAP_WIDTH * (Rect.y / 32) + (Rect.x - MAP_LEFT_OFFSET) / 32;
		if (index <= MAP_LENGTH) {
			int type = map[MAP_WIDTH * (Rect.y / 32) + (Rect.x - MAP_LEFT_OFFSET) / 32]->getTileType();
			Tile* t = map.at(MAP_WIDTH * (Rect.y / 32) + (Rect.x - MAP_LEFT_OFFSET) / 32);
			if (t != nullptr) {
				SDL_Rect tRec = t->getRect();

				if (checkCollision(tRec, Rect, 0)) {
					if ((type == SWALL_R || type == SWALL_B || type == SWALL_T ||
						type == SWALL_L || type == MID_WALL || type == MID_WALL_TOP || type == MID_WALL_BOTTOM
						|| type == MID_WALL_VERTICAL || type == MID_WALL_R || type == MID_WALL_L)) {

						isWall = true;
						return false;
						break;
					}
				}
			}

		}

		currStepX += stepX;
		currStepY += stepY;
		Rect.x += (int)currStepX;
		Rect.y += (int)currStepY;
	}

	return true;
}



void Enemy::handleInput() {
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP]) {
		frame++;
		angle = 0;
		translate(0, 2.0);
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		frame++;
		angle = 180;
		translate(0, -2.0);
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		frame++;
		translate(2.0, 0);
		angle = -90;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		frame++;
		angle = 90;
		translate(-2.0, 0);
	}
}