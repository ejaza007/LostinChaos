#include "../include/TrapIcon.h"

TrapIcon::TrapIcon() {}

// init variables and create texture
TrapIcon::TrapIcon(int x, int y, std::string path, int type, SDL_Renderer* renderer, unsigned int cooldown) {

	this->renderer = renderer;
	iconSprite = new Texture(path, renderer);
	boundaryRect = { x, y, iconSprite->getWidth(), iconSprite->getHeight() };
	bgRect = { boundaryRect.x - 10, boundaryRect.y - 10, boundaryRect.w + 20, boundaryRect.h + 20 };
	this->type = type;
	placed = false;
	this->cooldown = cooldown;
}

// dtor to free texture
TrapIcon::~TrapIcon() {
	iconSprite->free();
}

// render sprite on its position
void TrapIcon::render() {

	bgRect = { boundaryRect.x - 10, boundaryRect.y - 10, boundaryRect.w + 20, boundaryRect.h + 20 };

	if (placed) {
		if (timer.getTicks() / 1000 >= cooldown) {
			placed = false;
			timer.stop();
		}
		else {
			int h = (int)(bgRect.h - (double)timer.getTicks() / 1000 * bgRect.h / cooldown);
			SDL_Rect cooldownRect = { bgRect.x, bgRect.y, bgRect.w, (int)h };
			SDL_SetRenderDrawColor(renderer, GRAY.r, LIGHT_GRAY.g, GRAY.b, 255);
			SDL_RenderFillRect(renderer, &cooldownRect);
		}
	}
	else {
		int xPos, yPos;
		SDL_GetMouseState(&xPos, &yPos);

		// render hover movement 
		if (checkMouseHover(boundaryRect, xPos, yPos)) {
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(renderer, LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b, LIGHT_GRAY.a);
			SDL_RenderFillRect(renderer, &bgRect);
		}
	}
	
	SDL_SetRenderDrawColor(renderer, GRAY.r, GRAY.g, GRAY.b, GRAY.a);
	SDL_RenderDrawRect(renderer, &bgRect);

	SDL_Rect src = { 0, 0, iconSprite->getWidth(), iconSprite->getHeight() };

	iconSprite->render(&src, &boundaryRect);
}

void TrapIcon::renderAtMouse() {
	int xPos, yPos;
	SDL_GetMouseState(&xPos, &yPos);

	xPos = xPos - (boundaryRect.w / 2);
	yPos = yPos - (boundaryRect.h / 2);

	boundaryRect.x = xPos;
	boundaryRect.y = yPos;

	SDL_Rect src = { 0, 0, iconSprite->getWidth(), iconSprite->getHeight() };
	SDL_Rect dst = { xPos, yPos, iconSprite->getWidth(), iconSprite->getHeight() };

	iconSprite->render(&src, &dst);
}


Texture* TrapIcon::getTexture() {
	return iconSprite;
}

// returns type of trap 
int TrapIcon::getType() {
	return type;
}

// return boundary SDL_Rect
SDL_Rect& TrapIcon::getBoundaryRect() {
	return boundaryRect;
}


void TrapIcon::setPlaced() {
	placed = true;
	timer.start();
}

bool TrapIcon::isPlaced() {
	return placed;
}

SDL_Rect& TrapIcon::getBgRect() {
	return bgRect;
}