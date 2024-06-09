#include "../include/Renderer.h"

Renderer::Renderer() {
	if (renderer == nullptr) {
		bool init = initSDL();
		if (!init) printf("Error while init SDL");
	}
	NOW = SDL_GetPerformanceCounter();
	LAST = 0;
	deltaTime = 0;
}

Renderer::~Renderer() {
	close();
}

SDL_Renderer* Renderer::getRenderer() {
	return renderer;
}

void Renderer::updateDeltaTime() {
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
}

double Renderer::getDeltaTime() {
	return deltaTime;
}

void Renderer::renderList(vector<Object*> &list) {
	for (int i = 0; i < list.size(); i++) {
		list.at(i)->render();
	}
}


void Renderer::close() {
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_Quit();
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
}

bool Renderer::initSDL() {
	bool success = true;
	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// create window
		window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			printf("Window could not be created! SDL Error %s\n", SDL_GetError());
			success = false;
		}
		else {
			// init renderer
			renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == nullptr) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				// init renderer color
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				//init png loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL image could not init! SDL_image error: %s \n", IMG_GetError());
					success = false;
				}

				if (TTF_Init() == -1) {
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}