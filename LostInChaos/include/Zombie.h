#pragma once
#include "Enemy.h"
#include "EnemyMGBullet.h"

class Zombie : public Enemy {
public:
	
	Zombie();

	Zombie(float x, float y, SDL_Renderer* renderer, Map* map, Object* player, vector<Object*>* objects, SoundManager* sm);

	virtual void fire(vector<Object*>& list, vector<Object*>& bullets, std::array<Tile*, MAP_LENGTH>& map, double deltaTime);

	void render();

private:
	void clipSheet();
	
	SDL_Rect rects[2];

};