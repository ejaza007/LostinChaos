#include "../include/MenuManager.h"

MenuManager::MenuManager() {};

MenuManager::MenuManager(SDL_Renderer* SDLRenderer) {
	renderer = SDLRenderer;
	font = new Font(FONT_PATH, renderer, 45);

	buttons.insert(buttons.begin(), new Texture(BUTTON_CORNER, renderer));
	buttons.insert(buttons.begin(), new Texture(BUTTON_TOP, renderer));
	buttons.insert(buttons.begin(), new Texture(BUTTON_MIDDLE, renderer));
};

MenuManager::~MenuManager() {
	delete font;
}

void MenuManager::createText() {
	SDL_Color color = { 0,0,0,255 };
	int dimX = (SCREEN_WIDTH / 2) - (92 / 2);
	font->render(dimX-5, SCREEN_HEIGHT / 2 - 80, "Play", color);
	font->render(dimX-11, (SCREEN_HEIGHT / 2) + 6, "Save", color);
	font->render(dimX, (SCREEN_HEIGHT / 2) + 92, "Exit", color);
	font->render(dimX-15, SCREEN_HEIGHT / 2 - 290, "Menu", color);
}

void MenuManager::render() {
	renderMenu((int)(SCREEN_WIDTH / 2 - 16 * 24), (int)(SCREEN_HEIGHT / 2 - 16 * 20));
	renderButton((int)(SCREEN_WIDTH / 2 - 16 * 5.9), (int)(SCREEN_HEIGHT / 2 - 16 * 6));
	renderButton((int)(SCREEN_WIDTH / 2 - 16 * 5.9), (int)(SCREEN_HEIGHT / 2 - 16 * 0.6));
	renderButton((int)(SCREEN_WIDTH / 2 - 16 * 5.9), (int)(SCREEN_HEIGHT / 2 + 16 * 4.8));

	createText();
}

void MenuManager::renderButton(int startX, int startY) {
	
	Button x(startX, startY, 10, 4, buttons, renderer);
	x.renderButton();
}

void MenuManager::renderMenu(int startX, int startY) {
	Button x(startX, startY, 46, 32, buttons, renderer);
	x.renderButton();
}