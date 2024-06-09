#include <SDL.h>
#include "../include/Enemy.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/Renderer.h"
#include "../include/GlobalVars.h"
#include "../include/TrapHUD.h"
#include "../include/Zombie.h"
#include "../include/Soldier.h"
#include "../include/Hitman.h"
#include "../include/MenuManager.h"
#include "../include/Explosion.h"
#include "../include/Blood.h"


SoundManager* sm = new SoundManager();

void updateList(SDL_Renderer* renderer, vector<Object*>& objects, vector<Object*>& bullets, Map* map, double deltaTime);

void generateEnemies(SDL_Renderer* renderer, vector<Object*>& objects, Object* player,
	unsigned int& timelapse, Map* map, SoundManager* sm);

int main(int argc, char* args[]) {

	GlobalVars gvars;

	// set in menu to true for game start
	gvars.inMenu = true;

	Renderer* system = new Renderer();
	SDL_Renderer* renderer = system->getRenderer();

	// menu manager to handle UI elements
	MenuManager* menu = new MenuManager(renderer);
	// sound manager to play sfx and music


	// game objects vector to store objects such as enemies and turrets
	vector<Object*> objects;

	// bullets and particles are stored in another vector to make collision detection
	// simpler and easier
	vector<Object*> bullets;

	// map pointer 
	Map* map = new Map(renderer);
	// player poitner
	Player* player = new Player(722, 600, renderer, sm);
	// trap hud 
	TrapHUD* trapHUD = new TrapHUD(renderer, &map->getMap(), &objects, sm);

	Timer enemyGenerationTimer;

	enemyGenerationTimer.start();

	while (!gvars.gameLoop) {
		// keep updating deltaTime
		system->updateDeltaTime();


		// handle events like mouse click and keyboard presses
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				gvars.gameLoop = true;
			}

			if (e.type == SDL_MOUSEBUTTONDOWN) {

				if (gvars.inMenu) {
					// PLAY BUTTON PRESSED
					if (e.button.x > (SCREEN_WIDTH / 2) - 92 - 5 && e.button.x < (SCREEN_WIDTH / 2) - 92 - 5 + 160 &&
						e.button.y > SCREEN_HEIGHT / 2 - 80 && e.button.y < SCREEN_HEIGHT / 2 - 80 + 64) {
						gvars.inMenu = false;
						Mix_HaltMusic();
						sm->playGameMusic();
					}
					// SAVE BUTTON PRESSED
					if (e.button.x > (SCREEN_WIDTH / 2) - 46 && e.button.x < (SCREEN_WIDTH / 2) + 92 &&
						e.button.y > SCREEN_HEIGHT / 2 && e.button.y < SCREEN_HEIGHT / 2 + 100) {
						gvars.inMenu = false;

						// carry out save operation
					}
					// EXIT BUTTON PRESSED
					if (e.button.x > (SCREEN_WIDTH / 2) - 46 && e.button.x < (SCREEN_WIDTH / 2) + 92 &&
						e.button.y > SCREEN_HEIGHT / 2 && e.button.y < SCREEN_HEIGHT / 2 + 100) {
						gvars.inMenu = false;
						gvars.gameLoop = false;
					}
				}
			}

			// handle trap selection when user clicks on traps and places them
			// ESC key to cancel selection
			// Left Mouse Click to select a turret
			// Left Mouse Click to place a turret if the position is valid
			trapHUD->handleTrapsSelection(e);
		}

		// set renderer color
		SDL_SetRenderDrawColor(renderer, BG.r, BG.g, BG.b, BG.a);
		// clear renderer to draw on screen
		SDL_RenderClear(renderer);

		// render menu if the screen is in menu

		if (gvars.inMenu) {
			menu->render();
			sm->playMenuMusic();
		}
		else {

			/*
			Map rendered below every entity
			*/
			map->renderMap();

			/*
			Enemeies generated at map
			*/
			gvars.enemyCounter += (unsigned int)system->getDeltaTime();
			generateEnemies(renderer, objects, player, gvars.enemyCounter, map, sm);
			/*
			All player rendering, movements, and attack goes below this code
			*/
			player->render();
			player->move(map->getMap(), system->getDeltaTime());

			/* Player End */
			/*
			both vectors are rendered using a helper function in Renderer class
			*/
			system->renderList(objects);
			system->renderList(bullets);

			/* List Rendering End*/

			/*
			Lists are updated such as movement, attack and other function calls
			*/
			updateList(renderer, objects, bullets, map, system->getDeltaTime());
			updateList(renderer, objects, bullets, map, system->getDeltaTime());

			/* List updating End */

			/*
			Trap HUD shown at right side of the game is rendered
			*/
			trapHUD->renderHUD(e);

			/* Trap HUD Rendering End*/

		}
		// render above entities
		SDL_RenderPresent(renderer);

	}
	// if game exits, delete renderer and all other components
	delete menu;
	delete sm;
	delete system;
	return 0;
}

// function to generate several enemies after time
// generation increases as time increases hence level gets harder

void generateEnemies(SDL_Renderer* renderer, vector<Object*>& objects, Object* player,
	unsigned int& timelapse, Map* map, SoundManager* sm) {

	// after every five seconds generate random enemies
	unsigned int delay = 5000;
	if (timelapse > delay) {

		int eType = rand() % 100;

		float xPos = 1300;
		float yPos = 198;

		// genearte a soldier and zombie
		if (eType <= 30) {

			Object* soldier = new Soldier(xPos, yPos, renderer, map, player, &objects, sm);
			Object* zombie = new Zombie(xPos, yPos + 64, renderer, map, player, &objects, sm);
			objects.insert(objects.begin(), soldier);
			objects.insert(objects.begin(), zombie);
		}
		// generate a zombie and hitman
		else if (eType > 30 && eType <= 70) {

			Object* hitman = new Hitman(xPos, yPos, renderer, map, player, &objects, sm);
			Object* zombie = new Zombie(xPos, yPos + 64, renderer, map, player, &objects, sm);
			objects.insert(objects.begin(), hitman);
			objects.insert(objects.begin(), zombie);
		}

		// genearte a hitman only
		else {


			Object* hitman = new Hitman(xPos, yPos, renderer, map, player, &objects, sm);
			objects.insert(objects.begin(), hitman);
		}

		timelapse = 0;

	}
}


void updateList(SDL_Renderer* renderer, vector<Object*>& objects, vector<Object*>& bullets, Map* map, double deltaTime) {


	/*
	Collision detection between game objects
	*/

	//Bullets and Objects Collide
	for (int i = 0; i < bullets.size(); i++) {
		for (int j = 0; j < objects.size(); j++) {
			int BTag = bullets[i]->getType();
			int OTag = objects[j]->getType();
			int dmg = 3;
			if (BTag == ENEMY_MG_BULLET_TAG || BTag == ALLY_MG_BULLET_TAG) {
				dmg = 1;
			}

			if (checkCollision(bullets[i]->getCollisionRect(), objects[j]->getCollisionRect(), 0)) {

				// if enemy bullets hit
				if (BTag == ENEMY_MISSILE_BULLET_TAG || BTag == ENEMY_CANNON_BULLET_TAG || BTag == ENEMY_MG_BULLET_TAG) {
					// enemy bullets hit a turret
					if (OTag == ML || OTag == CAN || OTag == MG) {
						objects[j]->kill(dmg, deltaTime);
						Explosion* Exp = new Explosion(objects[j]->getX(), objects[j]->getY(), 0, 32, 32, renderer, sm);
						objects.insert(objects.begin() + objects.size(), Exp);

					}
					// enemy bullets hit player
					if (OTag == PLAYER_TAG) {
						objects[j]->kill(dmg, deltaTime);
						Blood* Bld = new Blood(objects[j]->getX(), objects[j]->getY(), 0, 32, 32, renderer, sm);
						objects.insert(objects.begin() + objects.size(), Bld);

					}
				}
				// if ally bullets hit
				if (BTag == ALLY_CANNON_BULLET_TAG || BTag == ALLY_MG_BULLET_TAG || BTag == ALLY_MISSILE_BULLET_TAG) {
					// if ally bullets hit enemies
					if (OTag == SOLDIER_TAG || OTag == ZOMBIE_TAG || OTag == HITMAN_TAG) {
						objects[j]->kill(dmg, deltaTime);
						Blood* Bld = new Blood(objects[j]->getX(), objects[j]->getY(), 0, 32, 32, renderer, sm);
						objects.insert(objects.begin() + objects.size(), Bld);


					}
				}

			}


		}
	}


	// move and fire enemies, turrets
	for (int i = 0; i < objects.size(); i++) {
		objects.at(i)->move(map->getMap(), deltaTime);
		objects.at(i)->fire(objects, bullets, map->getMap(), deltaTime);
	}

	// move and fire bullet and particles 
	for (int i = 0; i < bullets.size(); i++) {
		bullets.at(i)->move(map->getMap(), deltaTime);
		bullets.at(i)->fire(objects, bullets, map->getMap(), deltaTime);
	}

	// clear bullets list for non alive elements
	for (int i = 0; i < bullets.size(); i++) {
		if (!(bullets.at(i)->isAlive())) {
			delete bullets.at(i);
			bullets.erase(bullets.begin() + i);
		}
	}

	// clear objects list for non alive elements
	for (int i = 0; i < objects.size(); i++) {
		if (!(objects.at(i)->isAlive())) {
			delete objects.at(i);
			objects.erase(objects.begin() + i);
		}
	}

}
