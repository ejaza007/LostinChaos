#include "../include/Button.h"

Button::Button() {};

Button::Button(int x, int y, int w, int h, vector<Texture*> buttons, SDL_Renderer* renderer) {
	gRenderer = renderer;
	startX = x;
	startY = y;
	width = w;
	height = h;
	endX = x + width;
	endY = y + height;

	buttonCorner = buttons.at(2);
	buttonSide = buttons.at(1);
	buttonMiddle = buttons.at(0);
}

void Button::renderButton() {
	
	int W = width;
	int H = height;
	SDL_Rect R1;
	SDL_Rect* R = &R1;
	
	for (int h = 0; h <= H; h++) {
		for (int w = 0; w <= W; w++) {

			R1.x = startX + 16 * w;
			R1.y = startY + 16 * h;
			R1.h = 16;
			R1.w = 16;


			if (w != 0 && w != W && h != 0 && h != H) {        //Middle
				SDL_RenderCopyEx(gRenderer, buttonMiddle->getTexture(), NULL, R, 0, NULL, SDL_FLIP_NONE);
			}
			else if (w == 0 && w != W && h != 0 && h != H) {   //Left Side
				SDL_RenderCopyEx(gRenderer, buttonSide->getTexture(), NULL, R, 90, NULL, SDL_FLIP_NONE);
			}
			else if (w != 0 && w == W && h != 0 && h != H) {   //Right Side
				SDL_RenderCopyEx(gRenderer, buttonSide->getTexture(), NULL, R, 90, NULL, SDL_FLIP_VERTICAL);
			}
			else if (w != 0 && w != W && h == 0 && h != H) {   //Top
				SDL_RenderCopyEx(gRenderer, buttonSide->getTexture(), NULL, R, 180, NULL, SDL_FLIP_NONE);
			}
			else if (w != 0 && w != W && h != 0 && h == H) {   //Bottom
				SDL_RenderCopyEx(gRenderer, buttonSide->getTexture(), NULL, R, 0, NULL, SDL_FLIP_NONE);
			}
			else if (w == 0 && w != W && h == 0 && h != H) {   //Top Left Corner
				SDL_RenderCopyEx(gRenderer, buttonCorner->getTexture(), NULL, R, 90, NULL, SDL_FLIP_NONE);
			}
			else if (w == 0 && w != W && h != 0 && h == H) {   //Bottom Left Corner
				SDL_RenderCopyEx(gRenderer, buttonCorner->getTexture(), NULL, R, 0, NULL, SDL_FLIP_NONE);
			}
			else if (w != 0 && w == W && h == 0 && h != H) {   //Top Right Corner
				SDL_RenderCopyEx(gRenderer, buttonCorner->getTexture(), NULL, R, 180, NULL, SDL_FLIP_NONE);
			}
			else if (w != 0 && w == W && h != 0 && h == H) {   //Bottom Right Corner
				SDL_RenderCopyEx(gRenderer, buttonCorner->getTexture(), NULL, R, 270, NULL, SDL_FLIP_NONE);
			}
		}
	}


	
}

 