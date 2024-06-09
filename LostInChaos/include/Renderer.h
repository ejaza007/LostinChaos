#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include "Constants.h"
#include "Object.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	SDL_Renderer* getRenderer();
	void close();
	
	// calculate delta time
	void updateDeltaTime();
	double getDeltaTime();

	// render objects list
	void renderList(vector<Object*> &list);


private:
	// initialzing SDL
	bool initSDL();

	// private instance of renderer
	SDL_Renderer* renderer;
	SDL_Window* window;

	// delta time variables
	Uint64 NOW;
	Uint64 LAST;
	double deltaTime;
	

};