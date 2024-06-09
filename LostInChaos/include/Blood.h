#pragma once
#include "Particle.h"

// class for blood particle
class Blood : public Particle {
public:
	// default ctor
	Blood();

	// overloaded ctor for blood
	Blood(float x, float y, float angle, int height, int width, SDL_Renderer* renderer, SoundManager* sm);

	//to alter particle with time
	void move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime);


};
