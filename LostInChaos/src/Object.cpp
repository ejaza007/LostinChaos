#include "../include/Object.h"

Object::Object() {};

Object::Object(float x, float y, SDL_Renderer* gRenderer, std::string file_name, SoundManager* sm, int type) {
	// set x, y coordinates and pass renderer
	this->sm = sm;
	this->x = x;
	this->y = y;
	this->renderer = gRenderer;
	this->type = type;
	// initialize texture by its path
	this->sprite = new Texture(file_name, renderer);
	// all objects by default have health 1
	this->health = 1;
	// by default collision rect will be the same as the complete sprite size
	this->collisionRect = { (int)x , (int)y , sprite->getWidth(), sprite->getHeight()};
	// object set to alive on creation
	alive = true;
	// angle = 0 pointing upwards by default
	angle = 0;
}

// free sprite if object is destroyed.
Object::~Object() {
	sprite->free();
}

bool Object::isAlive() {
	return alive;
}

int Object::getDamage() {
	return damage;
}

void Object::kill(int damage, double deltaTime) {
	health -= damage;
	if (health <= 0) alive = false;
	else {
		sm->playSound(HIT_SOUND);
	}
}

void Object::render() {

	SDL_Rect src = { 0, 0, sprite->getWidth(), sprite->getHeight() };
	SDL_Rect dst = { (int) x, (int) y, sprite->getWidth(), sprite->getHeight() };
	sprite->render(&src, &dst);
}

// check if object touches wall
bool Object::wallCollision(std::array<Tile*, MAP_LENGTH>& map, SDL_Rect &rect) {
	Tile* tile;
	SDL_Rect tileRect;
	for (int i = 0; i < map.size(); i++) {
		tile = map.at(i);
		if (tile != nullptr) {
			tileRect = tile->getRect();
			int type = tile->getTileType();
			if (type == SWALL_R || type == SWALL_B || type == SWALL_T || 
				type == SWALL_L || type == MID_WALL || type == MID_WALL_TOP || type == MID_WALL_BOTTOM
				|| type == MID_WALL_VERTICAL || type == MID_WALL_R || type == MID_WALL_L) {
				if (checkCollision(tileRect, rect, 0)) {
					return true;
				}
			}
		}
	}
	return false;
}


SDL_Rect& Object::getCollisionRect() {
	return collisionRect;
}

// move object by x and y values.
void Object::translate(float x_val, float y_val) {
	tx = x_val;
	ty = y_val;
}

// virtual function of an object firing 
// left empty since not all objects will fire
void Object::fire(vector<Object*>& list, vector<Object*>& bullets, std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {

}

void Object::setTarget(Object* target) {

}

int Object::getType() {
	return type;
}

float Object::getX() {
	return x;
}

float Object::getY() {
	return y;
}

