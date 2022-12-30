#pragma once
#include <iostream>
#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
	Enemy(TextureAPI enemyTexture, double x, double y, int vel , double angle);



	static const int ENEMY_WIDTH = 44;
	static const int ENEMY_HEIGHT = 56;
	static const int ENEMY_VEL = 5;
	
	void loadFromFile(SDL_Renderer *renderer);

	
	void handleEvent(SDL_Event& e);

	
	void move(double timeStep);

	
	void render(SDL_Renderer *renderer);

	void free();




	void createBullet(EnemyBullet &bullets, double x, double y, double angle);

	void setX(double x);
	void setY(double y);
	double getX();
	double getY();
	void setAngle(double angle);
	double getAngle();
	int getHp();
	void setHp(int hp);
	bool isCollision(double centerX, double centerY, int radius);
	

private:
	TextureAPI enemyTexture;
	TextureAPI bulletTexture;


	double mPosX, mPosY;

	int hp;

	int velocity;
	double angle;

	int ENEMY_RADIUS = 25;


	
};

