#include "../include/Tile.h"

Tile::Tile() {};

Tile::Tile(int x, int y, int type) {
	tileBox.x = x;
	tileBox.y = y;
	tileBox.w = TILE_WIDTH;
	tileBox.h = TILE_HEIGHT;

	tileType = type;
}

int Tile::getTileType() {
	return tileType;
}

SDL_Rect Tile::getRect() {
	return tileBox;
}

