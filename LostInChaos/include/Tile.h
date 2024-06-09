#pragma once
#include "Texture.h"
#include "Constants.h"

class Tile {
public:
	Tile();
	Tile(int x, int y, int tileType);

	int getTileType();
	SDL_Rect getRect();

private:
	int tileType;
	SDL_Rect tileBox;
};