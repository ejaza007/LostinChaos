#include "../include/Blood.h"

Blood::Blood() {};

Blood::Blood(float x, float y, float angle, int height, int width, SDL_Renderer* renderer, SoundManager* sm) 
	: Particle(x, y, angle, height, width, renderer, BLOOD_PNG, BLOOD_TAG, sm) {

}

void Blood::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {
	alpha *= (float) 0.999;
	if (alpha < 10) {
		alive = false;
	}
}


