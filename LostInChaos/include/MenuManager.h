#pragma once
#include "Texture.h"
#include "Font.h"
#include "constants.h"
#include "Button.h"
#include <iostream>
#include <vector>

class MenuManager {
public:
	MenuManager();
	MenuManager(SDL_Renderer* renderer);
	~MenuManager();

	void createText();
	void renderButton(int startX, int startY);
	void renderMenu(int startX, int startY);

	void render();

private:
	Font* font;
	SDL_Renderer* renderer;
	vector<Texture*> buttons;

	int buttonHeight;
	int buttonWidth;
};