#pragma once
#include <array>
#include "Object.h"

class Bullet : public Object {
public:
	Bullet();
	// ctor for bullet class
	Bullet(float x, float y, Object* target, float angle,  SDL_Renderer* renderer, std::string path, int type, SoundManager* sm);

	// keeping it pure virtual since each type of bullet will have different speed
	virtual void move(std::array<Tile*, MAP_LENGTH> &map, double deltaTime);

	// override render function since bullet will be shot at an angle
	void render();

protected:

	// damage each type of bullet inflicts
	int damage;

	// target object to shoot on
	Object* target;
	
	// unit x and y variables to move the bullet
	double unitX;
	double unitY;
};