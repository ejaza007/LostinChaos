#pragma once
#include <math.h>
#include <string>
#include <SDL.h>

using namespace std;

// WINDOW DIMENSIONS
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;

// PI VALUE
const double PI = M_PI;

// WINDOW TITLE
const string WINDOW_TITLE = "Lost in Chaos";

// RESOURCE FILES 
// ALL ASSETS ARE IN RES FOLDER
const string BASE = "./src/res/";

// MAP TILE DIMENSIONS
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int MAP_HEIGHT = SCREEN_HEIGHT / TILE_HEIGHT;
const int MAP_LEFT_OFFSET = 128;
const int MAP_WIDTH = (SCREEN_WIDTH - MAP_LEFT_OFFSET) / TILE_WIDTH;
const int MAP_LENGTH = MAP_WIDTH * MAP_HEIGHT;

const int TOTAL_TILES = 15;
// tile types
const int PLAIN = 14;
// shadow tiles

// corners
const int CORNER_TL = 4;
// corner top right - horizontal flip of corner_TL
const int CORNER_TR = 54;
// corner bottom left - vertical flip of CORNER_TL
const int CORNER_BL = 55;
// corner bottom right - horizontal flip - left 90
const int CORNER_BR = 56;


// bottom wall 
const int WALL_B = 6;
// top wall | flip of bottom wall 
const int WALL_T = 31;
// right  wall
const int WALL_R = 0;
// top shadow
const int SWALL_T = 1;
// right wall shadow
const int SWALL_R = 3;
// bottom wall shadow | rotate of right wall shadow
const int SWALL_B = 33;
// left wall shadow || horizontal flip of right wall shadow
const int SWALL_L = 34;
// left wall | horizontal flip of right wall
const int WALL_L = 30;
// corner of walls
// bottom right wall
const int CBR_WALL = 11;
// bottom left | horizontal flip of bottom right
const int CBL_WALL = 44;
// top right | horizontal flip of bottom right + rotate 180 degrees
const int CTR_WALL = 45;
// top left | rotate 180 of bottom right 
const int CTL_WALL = 46;

const int ASTAR_BOUNDARY = 114;

// mid wall
const int MID_WALL = 10;
// mid wall border
const int MID_WALL_BOTTOM = 9;
// mid wall top - vertically flipped of mid wall bottom
const int MID_WALL_TOP = 39;
// mid wall vertical - 90 degree left rotate 
const int MID_WALL_VERTICAL = 40;
// mid wall vertical border left | rotate 90 degree
const int MID_WALL_L = 99;
// mid wall vertical border right | rotate -90 degrees 
const int MID_WALL_R = 100;

//FONT
const std::string FONT_PATH = BASE + "font.ttf";

// MENU ELEMENTS
const std::string BUTTON_MIDDLE = BASE + "menu/button_middle.png";
const std::string BUTTON_CORNER = BASE + "menu/button_corner.png";
const std::string BUTTON_TOP = BASE + "menu/button_side.png";

// COOLDOWN PERIODS FOR TURRETS (in seconds)
const int CANNON_COOLDOWN = 10;
const int MG_COOLDOWN = 20;
const int MISSILELAUNCHER_COOLDOWN = 30;

// MAP PATH
const string MAP_FILE = BASE + "map.txt";

// SPRITESHEETS FOR ENTITIES
// tiles
const string TILESET_PNG = BASE + "tiles/tileset.png";

// sprites
const string SOLDIER_PNG = BASE + "soldier.png";
const string PLAYER_PNG = BASE + "player2.png";
const string ZOMBIE_PNG = BASE + "zombie.png";
const string HITMAN_PNG = BASE + "hitman.png";

// TRAPS SPRITES
const string TOWER_PNG = BASE + "/turrets/tower.png";
const string CANNON_PNG = BASE + "/turrets/cannon.png";
const string MISSILE_LAUNCHER_PNG = BASE + "/turrets/missileLauncher.png";
const string MACHINE_GUN_PNG = BASE + "/turrets/machineGun.png";

//TRAPS ICON
const string CANNON_ICON_PNG = BASE + "/turrets/cannonIcon.png";
const string MISSILE_LAUNCHER_ICON_PNG = BASE + "/turrets/missileLauncherIcon.png";
const string MACHINE_GUN_ICON_PNG = BASE + "/turrets/machineGunIcon.png";

// BULLETS
const string MG_BULLET_PNG = BASE + "/turrets/mgBullet.png";
const string CANNON_BULLET_PNG = BASE + "/turrets/cannonBullet.png";
const string MISSILE_BULLET_PNG = BASE + "/turrets/missileBullet.png";
const string ENEMY_MG_BULLET_PNG = BASE + "/turrets/EmgBullet.png";
const string ENEMY_CANNON_BULLET_PNG = BASE + "/turrets/EcannonBullet.png";
const string ENEMY_MISSILE_BULLET_PNG = BASE + "/turrets/EmissileBullet.png";

// PARTICLES 
const string BLOOD_PNG = BASE + "blood_splat.png";
const string EXPLOSION_PNG = BASE + "explosion.png";

// AUDIO AND SFX
const std::string explosionSound = BASE + "audio/explosion.wav";
const std::string laserSound = BASE + "audio/laserShoot.wav";
const std::string missileSound = BASE + "audio/missileSound.wav";
const std::string hitSound = BASE + "audio/hit.wav";
const std::string MENU_MUSIC = BASE + "audio/menuMusic.mp3";
const std::string GAME_MUSIC = BASE + "audio/gameMusic.mp3";
const std::string ENEMY_SHOOT = BASE + "audio/enemyShoot.wav";

// UI RESOURCES

// COLORS 
//BACKGROUND
const SDL_Color BG = { 199, 230, 249, 255 };
const SDL_Color GRAY = { 121, 144, 158, 150 };
const SDL_Color LIGHT_GRAY = { 82, 109, 126, 150 };

// NUMBER OF TRAPS 
const int NUM_OF_TRAPS = 3;

// ENUM FOR TYPE OF OBJECTS
enum TAG {
	PLAYER_TAG, SOLDIER_TAG, ZOMBIE_TAG, HITMAN_TAG, ALLY_MG_BULLET_TAG, ALLY_CANNON_BULLET_TAG,
	ALLY_MISSILE_BULLET_TAG, ENEMY_MG_BULLET_TAG, ENEMY_CANNON_BULLET_TAG,
	ENEMY_MISSILE_BULLET_TAG, MISSILE_LAUNCHER, CANNON, MACHINE_GUN, BLOOD_TAG, EXPLOSION_TAG,
	EXPLOSION_SOUND, LASER_SHOOT, MISSILE_SOUND, HIT_SOUND, ENEMY_SHOT_SOUND
};

enum TRAPS_INDEX {
	ML, CAN, MG
};