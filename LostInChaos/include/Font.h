#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include "constants.h"
#include <string>

class Font {
public:
	Font();
	Font(std::string filename, SDL_Renderer* gRenderer, int size);
	~Font();

	void render(int x, int y, std::string text, SDL_Color color);

	int getWidth();
	int getHeight();


private:
	std::string filename;
	SDL_Renderer* renderer;
	TTF_Font* font;
	int height;
	int width;

	bool loadFont(int size);

};