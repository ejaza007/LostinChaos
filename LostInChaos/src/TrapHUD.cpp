#include "../include/TrapHUD.h"

TrapHUD::TrapHUD() {
	map = nullptr;
	objects = nullptr;
	renderer = nullptr;
	selectedTrap = -1;
	for (int i = 0; i < 3; i++) {
		icons[i] = nullptr;
	}
};

TrapHUD::TrapHUD(SDL_Renderer* renderer, std::array<Tile*, MAP_LENGTH>* map, vector<Object*>* objects,
	SoundManager* sm) {
	this->map = map;
	this->sm = sm;
	this->objects = objects;
	this->renderer = renderer;

	icons[ML] = new TrapIcon(32, startPosY, MISSILE_LAUNCHER_ICON_PNG, ML, renderer, MISSILELAUNCHER_COOLDOWN);
	icons[CAN] = new TrapIcon(32, startPosY + 112, CANNON_ICON_PNG, CAN, renderer, CANNON_COOLDOWN);
	icons[MG] = new TrapIcon(32, startPosY + 224, MACHINE_GUN_ICON_PNG, MG, renderer, MG_COOLDOWN);

	selectedTrap = -1;
}

TrapHUD::~TrapHUD() {
	for (int i = 0; i < NUM_OF_TRAPS; i++) {
		delete icons[i];
	}
}

void TrapHUD::renderHUD(SDL_Event& e) {
	renderSelectedTrap();
	for (int i = 0; i < NUM_OF_TRAPS; i++) {
		icons[i]->render();
	}
}

void TrapHUD::renderSelectedTrap() {
	if (selectedTrap != -1) {

		bool isLegal = isPositionLegal();
		renderIllegalPlacement(isLegal);
		// get mouse positions
		int xPos, yPos;
		SDL_GetMouseState(&xPos, &yPos);

		// fill selected icon with a background
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, GRAY.r, GRAY.g, GRAY.b, GRAY.a);
		SDL_RenderFillRect(renderer, &icons[selectedTrap]->getBgRect());

		// get texture reference
		selectedIcon = *icons[selectedTrap];

		// adjust x and y values to center
		int x = xPos - (icons[selectedTrap]->getBoundaryRect().w / 2);
		int y = yPos - (icons[selectedTrap]->getBoundaryRect().h / 2);

		SDL_Rect src = { 0 , 0, icons[selectedTrap]->getBoundaryRect().w, icons[selectedTrap]->getBoundaryRect().h };
		SDL_Rect dst = { x, y, icons[selectedTrap]->getBoundaryRect().w, icons[selectedTrap]->getBoundaryRect().h };
		selectedIcon.renderAtMouse();
	}
}

void TrapHUD::handleTrapsSelection(SDL_Event& e) {
	// only check if mouse clicked 
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		// if no trap is selected look for selection
		if (selectedTrap == -1) {
			// check for trap selection based on id
			if (checkMouseClick(icons[ML]->getBoundaryRect(), e)) {
				if (!icons[ML]->isPlaced()) {
					selectedTrap = ML;
				}
			}
			else if (checkMouseClick(icons[CAN]->getBoundaryRect(), e)) {
				if (!icons[CAN]->isPlaced()) {
					selectedTrap = CAN;
				}
			}
			else if (checkMouseClick(icons[MG]->getBoundaryRect(), e)) {
				if (!icons[MG]->isPlaced()) {
					selectedTrap = MG;
				}
			}
		}
		// if trap is selected look for placement
		else placeTrap(e);
	}
	// if escape key pressed, cancel any trap selection.
	else if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			selectedTrap = -1;
		}
	}
}

void TrapHUD::placeTrap(SDL_Event& e) {
	int x = e.button.x - (icons[selectedTrap]->getBoundaryRect().w / 4);
		int y = e.button.y - (icons[selectedTrap]->getBoundaryRect().h / 2);

	// do not place if attempted to be placed at illegal position
	if (!isPositionLegal()) {
		return;
	}

	Object* trap = nullptr;

	if (selectedTrap == CAN) {
		trap = new Cannon((float)x, (float)y, renderer, objects, sm);
	}
	else if (selectedTrap == ML) {
		trap = new MissileLauncher((float)x, (float)y, renderer, objects, sm);
	}
	else if (selectedTrap == MG) {
		trap = new MachineGun((float)x, (float)y, renderer, objects, sm);
	}
	if (trap != nullptr) {
		objects->insert(objects->begin(), trap);
		icons[selectedTrap]->setPlaced();
	}
	selectedTrap = -1;
}

void TrapHUD::renderIllegalPlacement(bool isLegal) {
	// render a green background if its legal to place
	if (isLegal) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
		SDL_RenderFillRect(renderer, &selectedIcon.getBoundaryRect());
	}
	// render a red background if illegal to place 
	else {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
		SDL_RenderFillRect(renderer, &selectedIcon.getBoundaryRect());
	}
}

bool TrapHUD::isPositionLegal() {
	// check if trap collides with walls or boundaries
	for (int i = 0; i < map->size(); i++) {
		if (map->at(i) != nullptr) {
			SDL_Rect tile = map->at(i)->getRect();
			int type = map->at(i)->getTileType();
			if (type == SWALL_R || type == SWALL_B || type == SWALL_T ||
				type == SWALL_L || type == MID_WALL || type == MID_WALL_TOP || type == MID_WALL_BOTTOM
				|| type == MID_WALL_VERTICAL || type == MID_WALL_R || type == MID_WALL_L || type == ASTAR_BOUNDARY) {
				if (checkCollision(selectedIcon.getBoundaryRect(), tile, 0)) {
					return false;
				}
			}
		}
	}
	// check if trap collides with existing objects in list
	for (int i = 0; i < objects->size(); i++) {
		if (checkCollision(objects->at(i)->getCollisionRect(), selectedIcon.getBoundaryRect(), 0)) {
			return false;
		}
	}

	if (selectedIcon.getBoundaryRect().x <= 128) return false;

	return true;
}