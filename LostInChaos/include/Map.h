#pragma once

#include <fstream>
#include <array>
#include "Tile.h"
#include "Texture.h"

class Map {
public:
	Map();
	Map(SDL_Renderer* renderer);
	~Map();

	void readMap();
	void renderMap();
	std::array<Tile*, MAP_LENGTH> &getMap();

private:
	SDL_Renderer* renderer;
	std::array<Tile*, MAP_LENGTH> tiles;

	SDL_Rect rects[TOTAL_TILES];
	Texture* tileset;

	void clipSpriteSheet();
	
};