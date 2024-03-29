#pragma once
#include <iostream>
#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "TextureAPI.h"
#include "GlobalResource.h"
#include "Bullet.h"
#include "EnemyBullet.h"

using namespace std;

class Character {
public:
	
	
	static const int CHARACTER_WIDTH = 44;
	static const int CHARACTER_HEIGHT = 56;

	static const int MIN_CHARACTER_VEL = 50;
	static const int MAX_CHARACTER_VEL = 300;

	Character();
	

	void loadFromFile(SDL_Renderer *renderer, string path);

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move(double timeStep);

	//Shows the dot on the screen
	void render(SDL_Renderer *renderer);

	void free();

	void shoot();

	void createBullet(EnemyBullet &bullet, double angle = 90);
	void moveBullets(double timeStep);
	vector<Bullet> getBullets();
	double getX();
	double getY();
	int getHp();
	void setHp(int hp);

	void setDefaultPlace();
private:
	
	TextureAPI characterTexture;
	TextureAPI bulletTexture;

	const string CHARACTER_PATH = "Resource/Image/planeWithHitBox.png";
	const string BULLET_PATH = "Resource/Image/bullet.png";

	SDL_Rect currentClip = { 0,0,44,56 };
	
	
	//The X and Y offsets of the dot
	double mPosX, mPosY;

	//Center of the hitbox
	

	const int HITBOX_RADIUS = 3;
	
	double mVelX, mVelY;

	int hp;
	vector <Bullet> bullets;

		
};


