#include "../include/Font.h"

Font::Font() {};

Font::Font(std::string filename, SDL_Renderer* gRenderer, int size) {
	this->filename = std::move(filename);
	this->renderer = gRenderer;
	height = width = 0;
	if (!loadFont(size))
		printf("Could not load font");
}

Font::~Font() {
	TTF_CloseFont(font);
}



void Font::render(int x, int y, std::string text, SDL_Color textColor) {
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (textSurface == nullptr)
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	else {
		//Create texture from surface pixels
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == nullptr)
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		else {
			height = textSurface->h;
			width = textSurface->w;
			SDL_Rect src = { 0, 0, width, height };
			SDL_Rect dst = { x, y, width, height };
			SDL_RenderCopy(renderer, texture, &src, &dst);
		}
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(texture);
	}
}

bool Font::loadFont(int size) {
	bool success = true;
	//Open the font
	font = TTF_OpenFont(filename.c_str(), size);
	if (font == nullptr) {
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	return success;
}

int Font::getHeight() {
	return height;
}

int Font::getWidth() {
	return width;
}