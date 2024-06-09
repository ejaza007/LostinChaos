#pragma once
#include "Object.h"
#include "helper.h"
#include "Astar.h"
#include "Timer.h"

class Enemy : public Object {
public:
	Enemy();

	// overriding ctor for enemy
	Enemy(float x, float y, SDL_Renderer* renderer, Map* map, Object* player, vector<Object*> *objects, 
		std::string filename, int type, SoundManager* sm);

	/*
	 All enemy movement will comprise of 2 basic things: 
		1. Using A star search to find the player and move in that path.
		2. Keep looking for turrets in area.
		3. If turret found:
			a. Stop A* search
			b. Set attack mode to true
			c. Attack turret 
		4. If no turret found, keep following the path.
	*/
	void move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime);

	// virtual render function since somme enemies will have sprite sheet animations like meele attack
	virtual void render();

	// using the virtual fire function, each enemy will define its different type of attacks

	// returns true if line of sight is clear
	bool LineOfSight(Object* target, int SightRadius, std::array<Tile*, MAP_LENGTH>& map, double deltatime);

protected:

	// attack mode which tells if enemy should attack or follwo A* path
	bool attackTurret;

	bool attackPlayer;

	bool shot;

	Timer timer;

	bool targetFound;

	// target for A* search
	Object* playerObj;

	// target for turret
	Object* turret;

	// to check for turrets
	vector<Object*>* objects;
	
	// frame int for enemies that have sprite sheets
	int frame;

	// map 
	Map* map;

private:
	
	stack<SDL_Point*> path;

	void handleInput();

};