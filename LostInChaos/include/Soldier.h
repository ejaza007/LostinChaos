#pragma once
#include "Enemy.h"
#include "Timer.h"
#include "EnemyMGBullet.h"

class Soldier : public Enemy {
public:
	Soldier();

	Soldier(float x, float y, SDL_Renderer* renderer, Map* map, Object* player, vector<Object*> *objects, SoundManager* sm);

	virtual void fire(vector<Object*>& list, vector<Object*>& bullets, std::array<Tile*, MAP_LENGTH>& map, double deltaTime);

	void render();

private:
	void clipSheet();

	SDL_Rect rects[2];
};
