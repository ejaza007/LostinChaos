#pragma once
#include <array>

#include "Object.h"
#include "TrapIcon.h"
#include "Constants.h"
#include "Cannon.h"
#include "MachineGun.h"
#include "MissileLauncher.h"

class TrapHUD {
public:
	// default ctor
	TrapHUD();

	// override ctor
	TrapHUD(SDL_Renderer* renderer, std::array<Tile*, MAP_LENGTH>* map, vector<Object*> *objects, SoundManager* sm);

	// free memory allocated
	~TrapHUD();

	// render HUD on screen 
	void renderHUD(SDL_Event &e);
	
	// handle trap selection 
	void handleTrapsSelection(SDL_Event& e);

	// place traps on map
	void placeTrap(SDL_Event &e);

private:
	// types of traps stored at indexes:
	// index 0:
	// index 1: 
	// index 2: 
	TrapIcon *icons[NUM_OF_TRAPS];

	// renderer pointer for rendering items
	SDL_Renderer* renderer;

	// start position of trap placement
	int startPosY = (SCREEN_HEIGHT / 2) - 144;

	// tag id of selected trap from menu
	int selectedTrap;

	// selected trap icon for collision detection with map objects
	TrapIcon selectedIcon;

	// render selected trap's image on mouse position
	void renderSelectedTrap();

	// render green or red rect based on availabilty of placing a trap 
	void renderIllegalPlacement(bool isLegal);

	// check if position of trap to be placed is legal
	bool isPositionLegal();

	// map and vector for objects
	std::array<Tile*, MAP_LENGTH>* map;
	vector<Object*> *objects;

	SoundManager* sm;

};
