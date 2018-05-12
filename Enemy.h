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
#include "EnemyBullet.h"

using namespace std;

class Enemy {
public:
	Enemy(double x, double y, double velX);
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

	void createBullet(EnemyBullet &bullets, double x, double y, double angle);


	
	

private:
	TextureAPI enemyTexture;
	TextureAPI bulletTexture;

	//The X and Y offsets of the dot
	double mPosX, mPosY;

	//The velocity of the dot
	int velocity;

	const string ENEMY_PATH = "Resource/Image/enemy.png";
	const string BULLET_PATH = "Resource/Image/enemy.png";

	
};

