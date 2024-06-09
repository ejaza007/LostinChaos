#pragma once
#include <string>
#include <SDL.h>
#include "Texture.h"
#include "helper.h"
#include "Timer.h"

class TrapIcon {
public:
	// overloaded ctor
	TrapIcon(int x, int y, std::string path, int type, SDL_Renderer* renderer, unsigned int cooldown);
	// default public ctor
	TrapIcon();
	// dtor
	~TrapIcon();
	// get type of icon
	int getType();
	// get rect that stores coordinates
	SDL_Rect& getBoundaryRect();
	
	// get background rect
	SDL_Rect& getBgRect();

	// render trap icon at given x, y values 
	void render();

	// render icon at mouse position
	void renderAtMouse();

	// get texture reference
	Texture* getTexture();

	// set placed = true if trap placed
	void setPlaced();

	// get if icon is placed
	bool isPlaced();

	

private:
	// icon sprite to display Icon
	Texture* iconSprite;

	// rect to store icon x, y values
	SDL_Rect boundaryRect;

	// background rect for animations and hover
	SDL_Rect bgRect;

	SDL_Renderer* renderer;

	bool placed;

	// type of trap 
	int type;

	// timer to track cooldown period
	Timer timer;

	// time to track cooldown period
	unsigned int cooldown;
};