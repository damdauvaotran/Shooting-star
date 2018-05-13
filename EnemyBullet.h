#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "Bullet.h"
#include "TextureAPI.h"

using namespace std;
class EnemyBullet {
public:

	
	
	EnemyBullet();
	~EnemyBullet();



	void loadFromFile(SDL_Renderer *renderer ,string path);
	void render(SDL_Renderer *renderer);
	void createBullet(double mPosX, double x, double mPosY, double y, double angle);

	void moveBullets(double vel, double stepTime);
	bool isCollision(double centerX, double centerY, int radius);
	vector<Bullet> getBullets();
	
private:
	TextureAPI bulletTexture;
	vector<Bullet> bullets;

};

