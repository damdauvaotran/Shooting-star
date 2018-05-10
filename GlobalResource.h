#pragma once
#include "TextureAPI.h"
class GlobalResource {
public:
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;
	static const int MAIN_AREA_WIDTH = 400;
	static const int MAIN_AREA_HEIGHT = 600;
	static const int BULLET_WIDTH = 11;
	static const int BULLET_HEIGHT = 19;
	static const int BULLET_VEL = 400;
	static const int ENEMY_BULLET_VEL = 100;
	GlobalResource();
	~GlobalResource();

	static bool checkCollision(){
	
	}

	
}; 

