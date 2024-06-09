#pragma once
#include <string>
#include <SDL_mixer.h>
#include "constants.h"

class SoundManager {
public:
	SoundManager();
	~SoundManager();

	void playSound(char TAG);
	void playMenuMusic();
	void playGameMusic();

private:
	bool loadSounds();

	Mix_Chunk* explosion;
	Mix_Chunk* laser;
	Mix_Chunk* missile;
	Mix_Chunk* hit;
	Mix_Chunk* enemyShot;

	Mix_Music* gameMusic;
	Mix_Music* menuMusic;
};