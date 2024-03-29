#pragma once
#include <iostream>
#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "Bullet.h"

using namespace std;

class GlobalResource {
public:
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;
	static const int MAIN_AREA_WIDTH = 400;
	static const int MAIN_AREA_HEIGHT = 600;
	static const int BULLET_WIDTH = 11;
	static const int BULLET_HEIGHT = 19;
	static const int BULLET_VEL = 400;
	static const int ENEMY_VEL = 50;
	static const int ENEMY_HEIGHT = 49;
	static const int ENEMY_WIDTH = 49;
	static const int ENEMY_BULLET_VEL = 100;
	
	GlobalResource();
	~GlobalResource();

}; 

