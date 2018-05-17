#pragma once
#include "Enemy.h"
#include <SDL.h>

class Enemies {
public:
	Enemies();
	~Enemies();
	

	void loadFromFile(SDL_Renderer *renderer, string path);
	void render(SDL_Renderer *renderer);
	void createEnemy( double x,double y,int vel, double angle);

	void moveEnemy(double stepTime);
	vector<Enemy> getEnemies ();
	void deleteEnemy(int index);
	bool isCollision(double centerX, double centerY, int radius);
	void clear();
private:

	vector <Enemy> enemies;
	TextureAPI enemyTexture; 
};

