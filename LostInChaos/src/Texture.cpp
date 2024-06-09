#include "../include/Texture.h"

Texture::Texture() {}


// loads texture and inits variables.
Texture::Texture(std::string file_name, SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->texture = nullptr;
	bool loaded = loadTexture(file_name);
	if (!loaded) printf("Could not load texture");
}

// destructor to free loaded texture.
Texture::~Texture() {
	free();
}

// Destroy texture if its not in use anymore.
void Texture::free() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
		height = width = 0;
	}
}


// load texture from the file path
bool Texture::loadTexture(std::string file_path) {
	// clearing pre-existing texture
	free();
	// final texture
	SDL_Texture* new_text = nullptr;
	//load surface from image
	SDL_Surface* temp = IMG_Load(file_path.c_str());
	if (temp == nullptr) {
		printf("Unable to load image %s! SDL_image Error: %s\n", file_path.c_str(), IMG_GetError());
	}
	else {
		new_text = SDL_CreateTextureFromSurface(renderer, temp);
		if (new_text == nullptr) {
			printf("Unable to create texture from %s! SDL Error: %s\n", file_path.c_str(),
				SDL_GetError());
		}
		else {
			width = temp->w;
			height = temp->h;
		}

		SDL_FreeSurface(temp);
	}
	texture = new_text;
	return texture != nullptr;
}

void Texture::renderCopyEx(SDL_Rect* src, SDL_Rect* dst, SDL_Point* center, double angle, SDL_RendererFlip flipType) {
	SDL_RenderCopyEx(renderer, texture, src, dst, angle, center, flipType);
}

void Texture::render(SDL_Rect* src, SDL_Rect* dst) {
	SDL_RenderCopy(renderer, texture, src, dst);
}

int Texture::getHeight() {
	return height;
}

int Texture::getWidth() {
	return width;
}

SDL_Texture* Texture::getTexture() {
	return texture;
}
