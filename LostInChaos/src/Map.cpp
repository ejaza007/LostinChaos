#include "../include/Map.h"

Map::Map() {
	renderer = nullptr;
	tiles = { nullptr };
};

Map::Map(SDL_Renderer* gRenderer) {
	renderer = gRenderer;
	tileset = new Texture(TILESET_PNG, renderer);
	clipSpriteSheet();
	readMap();
}

Map::~Map() {
	for (int i = 0; i < tiles.size(); i++) {
		delete tiles.at(i);
	}
	tileset->free();
}

void Map::readMap() {
	std::ifstream mapFile(MAP_FILE);
	// starting initials of map 
	int x = 128, y = 0;
	// read map file 
	int i = 0;

	while (!mapFile.eof()) {
		// determines tile type 
		int tileType = -1;

		// Read type from map file 
		mapFile >> tileType;
		// if error occurs in reading from file
		if (mapFile.fail()) {
			mapFile.close();
			return;
		}
		// read tiles with valid tile types
		if (tileType >= 0) {
			tiles[MAP_WIDTH * (y / TILE_HEIGHT) + ((x - MAP_LEFT_OFFSET) / TILE_WIDTH)] = new Tile(x, y, tileType);
		}

		// increase x values 
		x += TILE_WIDTH;
		// if x value is maxed out, go to next row
		if (x >= SCREEN_WIDTH) {
			x = 128;
			y += TILE_HEIGHT;
		}
	}
	mapFile.close();
}

void Map::renderMap() {

	/// <summary>
	/// to render the map this goes over the loaded tiles array
	/// the array has tiles with their types stored
	/// each type of tile is defined in constants.h which tells where the tile is
	/// The tilesheet sprite is clipped using animation editor and values are stored in an array
	/// </summary>

	SDL_Rect dst;
	int type = -1;

	for (int i = 0; i < tiles.size(); i++) {
		if (tiles[i] != nullptr) {
			
			SDL_Rect tileRect = tiles.at(i)->getRect();
			int type = tiles.at(i)->getTileType();
			dst = { tileRect.x, tileRect.y, TILE_WIDTH, TILE_HEIGHT };

			switch (type) {
				case PLAIN:
					tileset->render(&rects[PLAIN], &dst);
					break;
				case ASTAR_BOUNDARY:
					tileset->render(&rects[PLAIN], &dst);
					break;
				case SWALL_T:
					tileset->render(&rects[SWALL_T], &dst);
					break;
				case WALL_T:
					tileset->renderCopyEx(&rects[WALL_B], &dst, nullptr, 0, SDL_FLIP_VERTICAL);
					break;
				case WALL_B:
					tileset->render(&rects[WALL_B], &dst);
					break;
				case SWALL_B:
					tileset->renderCopyEx(&rects[SWALL_R], &dst, nullptr, 90);
					break;
				case CBR_WALL:
					tileset->render(&rects[CBR_WALL], &dst);
					break;
				case CBL_WALL:
					tileset->renderCopyEx(&rects[CBR_WALL], &dst, nullptr, 0, SDL_FLIP_HORIZONTAL);
					break;
				case CTR_WALL:
					tileset->renderCopyEx(&rects[CBR_WALL], &dst, nullptr, 180, SDL_FLIP_HORIZONTAL);
					break;
				case CTL_WALL:
					tileset->renderCopyEx(&rects[CBR_WALL], &dst, nullptr, 180, SDL_FLIP_NONE);
					break;
				case WALL_R:
					tileset->render(&rects[WALL_R], &dst);
					break;
				case SWALL_R:
					tileset->render(&rects[SWALL_R], &dst);
					break;
				case SWALL_L:
					tileset->renderCopyEx(&rects[SWALL_R], &dst, nullptr, 0, SDL_FLIP_HORIZONTAL);
					break;
				case WALL_L:
					tileset->renderCopyEx(&rects[WALL_R], &dst, nullptr, 0, SDL_FLIP_HORIZONTAL);
					break;
				case MID_WALL:
					tileset->render(&rects[MID_WALL], &dst);
					break;
				case MID_WALL_BOTTOM:
					tileset->render(&rects[MID_WALL_BOTTOM], &dst);
					break;	
				case MID_WALL_TOP:
					tileset->renderCopyEx(&rects[MID_WALL_BOTTOM], &dst, nullptr, 0, SDL_FLIP_VERTICAL);
					break;
				case MID_WALL_VERTICAL:
					tileset->renderCopyEx(&rects[MID_WALL], &dst, nullptr, -90);
					break;
				case MID_WALL_L:
					tileset->renderCopyEx(&rects[MID_WALL_BOTTOM], &dst, nullptr, 90, SDL_FLIP_HORIZONTAL);
					break;
				case MID_WALL_R:
					tileset->renderCopyEx(&rects[MID_WALL_BOTTOM], &dst, nullptr, -90);
					break;
				case CORNER_TL:
					tileset->render(&rects[CORNER_TL], &dst);
					break;
				case CORNER_BL:
					tileset->renderCopyEx(&rects[CORNER_TL], &dst, nullptr, 0, SDL_FLIP_VERTICAL);
					break;
				case CORNER_BR:
					tileset->renderCopyEx(&rects[CORNER_TL], &dst, nullptr, 90, SDL_FLIP_HORIZONTAL);
					break;
				case CORNER_TR:
					tileset->renderCopyEx(&rects[CORNER_TL], &dst, nullptr, 0, SDL_FLIP_HORIZONTAL);
					break;

			}
		}
	}
}

void Map::clipSpriteSheet() {
	// Coordinates of sprites in sprite sheet 
	// Total sprites: 20
	// i = row, j = col, (i, j)
	// (0, 0)
	rects[0].x = 0;
	rects[0].y = 0;
	rects[0].w = 32;
	rects[0].h = 32;
	// (0, 1)
	rects[1].x = 32;
	rects[1].y = 0;
	rects[1].w = 32;
	rects[1].h = 32;
	// (0, 2)
	rects[2].x = 64;
	rects[2].y = 0;
	rects[2].w = 32;
	rects[2].h = 32;
	// (0, 3)
	rects[3].x = 96;
	rects[3].y = 0;
	rects[3].w = 32;
	rects[3].h = 32;
	// (0, 4)
	rects[4].x = 128;
	rects[4].y = 0;
	rects[4].w = 32;
	rects[4].h = 32;
	// (0, 5)
	rects[5].x = 160;
	rects[5].y = 0;
	rects[5].w = 32;
	rects[5].h = 32;
	// (0, 6)
	rects[6].x = 192;
	rects[6].y = 0;
	rects[6].w = 32;
	rects[6].h = 32;
	// (0, 7)
	rects[7].x = 224;
	rects[7].y = 0;
	rects[7].w = 32;
	rects[7].h = 32;
	// (0, 8)
	rects[8].x = 256;
	rects[8].y = 0;
	rects[8].w = 32;
	rects[8].h = 32;
	// (0, 9)
	rects[9].x = 288;
	rects[9].y = 0;
	rects[9].w = 32;
	rects[9].h = 32;
	// (1, 0)
	rects[10].x = 0;
	rects[10].y = 32;
	rects[10].w = 32;
	rects[10].h = 32;
	// (1, 1)
	rects[11].x = 32;
	rects[11].y = 32;
	rects[11].w = 32;
	rects[11].h = 32;
	// (1, 2)
	rects[12].x = 64;
	rects[12].y = 32;
	rects[12].w = 32;
	rects[12].h = 32;
	// (1, 3)
	rects[13].x = 96;
	rects[13].y = 32;
	rects[13].w = 32;
	rects[13].h = 32;
	// (1, 4)
	rects[14].x = 128;
	rects[14].y = 32;
	rects[14].w = 32;
	rects[14].h = 32;
	

}

std::array<Tile*, MAP_LENGTH> &Map::getMap() {
	return tiles;
}

