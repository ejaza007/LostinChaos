#pragma once
#include "Object.h"
#include "helper.h"
#include "Timer.h"
#include "Astar.h"

class Trap : public Object {
public:
	Trap();
	Trap(float x, float y, vector<Object*> *targets,SDL_Renderer* renderer, std::string fileName, int type, SoundManager* sm);

	void move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime);

	void render();

protected:

	// since all traps need a target to fire on
	// this function returns a target from the list provided in fire function
	Object* getTarget(vector<Object*> &list);

	// a timer object to keep track of shooting time
	// make a trap fire after intervals
	Timer timer;

	// a cooldown period for the bullet being shot
	unsigned int cooldown;

	// boolean variable to keep track whether bullet was shot or not
	bool shot;

	bool LineOfSight(Object* target, int SightRadius, std::array<Tile*, MAP_LENGTH>& map, double deltatime);

	Object* t;

	vector<Object*> *targets;

private:
	Texture* tower;


};