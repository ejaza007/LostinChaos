#include "../include/SoundManager.h"

SoundManager::SoundManager() {
	if (!loadSounds()) {
		printf("Could not load sound");
	}

}

SoundManager::~SoundManager() {
	Mix_FreeChunk(explosion);
	Mix_FreeChunk(laser);
	explosion = nullptr;
	laser = nullptr;
}

void SoundManager::playSound(char TAG) {
	switch (TAG) {
	case EXPLOSION_SOUND:
		Mix_PlayChannel(-1, explosion, 0);
		break;
	case LASER_SHOOT:
		Mix_PlayChannel(-1, laser, 0);
		break;
	case MISSILE_SOUND:
		Mix_PlayChannel(-1, missile, 0);
		break;
	case HIT_SOUND:
		Mix_PlayChannel(-1, hit, 0);
		break;
	case ENEMY_SHOT_SOUND:
		Mix_PlayChannel(-1, enemyShot, 0);
		break;
	}
}

void SoundManager::playMenuMusic() {
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(menuMusic, -1);
	}
}

void SoundManager::playGameMusic() {
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(gameMusic, -1);
	}
}

bool SoundManager::loadSounds() {
	bool success = true;

	laser = Mix_LoadWAV(laserSound.c_str());
	if (laser == nullptr) {
		printf("Failed to load laser sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	hit = Mix_LoadWAV(hitSound.c_str());
	if (hit == nullptr) {
		printf("Failed to load hit sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	enemyShot = Mix_LoadWAV(ENEMY_SHOOT.c_str());
	if (enemyShot == nullptr) {
		printf("Failed to load enemy shot sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	missile = Mix_LoadWAV(missileSound.c_str());
	if (missile == nullptr) {
		printf("Failed to load missile sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}


	explosion = Mix_LoadWAV(explosionSound.c_str());
	if (explosion == nullptr) {
		printf("Failed to load explosion sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gameMusic = Mix_LoadMUS(GAME_MUSIC.c_str());
	if (gameMusic == nullptr) {
		printf("Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	menuMusic = Mix_LoadMUS(MENU_MUSIC.c_str());
	if (menuMusic == nullptr) {
		printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}



	return success;
}