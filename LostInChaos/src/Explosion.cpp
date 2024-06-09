#include "../include/Explosion.h"

Explosion::Explosion() {};

Explosion::Explosion(float x, float y, float angle, int height, int width, SDL_Renderer* renderer, SoundManager* sm) 
	: Particle(x, y, angle, height, width, renderer, EXPLOSION_PNG, EXPLOSION_TAG, sm) {

}

void Explosion::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {
	angle++;
	alpha *= (float) 0.9;
	if (alpha < 10) {
		alive = false;
	}
}