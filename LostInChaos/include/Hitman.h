#pragma once
#pragma once
#include "Enemy.h"
#include "Timer.h"
#include "EnemyMGBullet.h"

class Hitman : public Enemy {
public:
	Hitman();

	Hitman(float x, float y, SDL_Renderer* renderer, Map* map, Object* player, vector<Object*>* objects, SoundManager* sm);

	virtual void fire(vector<Object*>& list, vector<Object*>& bullets, std::array<Tile*, MAP_LENGTH>& map, double deltaTime);

	void render();

private:
	SDL_Rect rects[3];

	void clipSheet();

};