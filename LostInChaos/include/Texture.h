#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Texture {
public:
	Texture();
	// ctor for texture with filepath and renderer pointer
	Texture(std::string filePath, SDL_Renderer* renderer);
	// destructor to free loaded textures
	~Texture();

	// free if texture is null
	void free();
	
	// render a texture with angle / flip type
	void renderCopyEx(SDL_Rect* src, SDL_Rect* dst, SDL_Point* center, double angle = 0, SDL_RendererFlip flipType = SDL_FLIP_NONE);

	// render a texture as it is
	void render(SDL_Rect* src, SDL_Rect* dst);

	// get height of texture
	int getHeight();

	// get width of texture
	int getWidth();

	// get texture reference
	SDL_Texture* getTexture();

private:
	// Stores texture
	SDL_Texture* texture;

	// stores renderer reference to show renderer
	SDL_Renderer* renderer;

	// width and height variables for the texture
	int width;
	int height;

	// loading a texture and returning false if it fails to load.
	bool loadTexture(std::string path);
};