#pragma once
#include "Enemy.h"
#include <SDL.h>

class Enemies {
public:
	Enemies();
	~Enemies();
	vector <Enemy> enemies;

	void loadFromFile(SDL_Renderer *renderer, string path);
	void render(SDL_Renderer *renderer);
	void createEnemy( double x,double y, double angle);

	void moveEnemy(double stepTime);
	vector<Enemy> getEnemy ();
	void deleteEnemy(int index);
private:

	
	TextureAPI enemyTexture; 
};

