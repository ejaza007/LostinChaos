#pragma once
#include "constants.h"
#include "Texture.h"
#include <vector>

class Button {
public:
	Button();
	Button(int startX, int startY, int width, int height,vector<Texture*> buttons, SDL_Renderer* renderer);

	void renderButton();

	bool isHovered();
	bool isClicked(SDL_Event *e);

private:
	SDL_Renderer* gRenderer;
	int startX;
	int startY;
	int width;
	int height;
	int endX;
	int endY;

	Texture* buttonSide;
	Texture* buttonCorner;
	Texture* buttonMiddle;
	
};