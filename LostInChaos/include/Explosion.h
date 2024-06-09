#pragma once
#include "Particle.h"

// class for explosion particle
class Explosion : public Particle {
public:
	// default ctor
	Explosion();

	// overloaded ctor for explosion
	Explosion(float x, float y, float angle, int height, int width, SDL_Renderer* renderer, SoundManager* sm);

	//to alter particle with time
	void move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime);



};