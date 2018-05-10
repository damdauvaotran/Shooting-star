#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <cmath>
#include "TextureAPI.h"
#include "GlobalResource.h"
#include "Bullet.h"

using namespace std;

class Enemy {
public:
	Enemy(double x, double y, double velX, double velY);
	~Enemy();

	static const int ENEMY_WIDTH = 44;
	static const int ENEMY_HEIGHT = 56;
	static const int ENEMY_VEL = 5;
	
	void loadFromFile(SDL_Renderer *renderer);

	
	void handleEvent(SDL_Event& e);

	
	void move(double timeStep);

	
	void render(SDL_Renderer *renderer, double angle = 0);

	void free();

	void shoot(double timeStep);

	void createBullets();

	void createBullet(double x, double y, double angle);

	void moveBullets(double stepTime);

	vector<Bullet> getBullets();
	

private:
	TextureAPI enemyTexture;
	TextureAPI bulletTexture;

	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;

	const string ENEMY_PATH = "Resource/Image/enemy.png";
	const string BULLET_PATH = "Resource/Image/enemyBullet.png";

	vector <Bullet> bullets;
};

