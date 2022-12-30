#pragma once
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>
#include "Bullet.h"
#include "TextureAPI.h"

using namespace std;
class EnemyBullet {
public:

	
	
	EnemyBullet();
	~EnemyBullet();



	void loadFromFile(SDL_Renderer *renderer ,string path);
	void render(SDL_Renderer *renderer);
	void createBullet(double mPosX, double x, double mPosY, double y,int vel, double angle);

	void moveBullets(double vel, double stepTime);
	bool isCollision(double centerX, double centerY, int radius);
	vector<Bullet> getBullets();
	void deleteBullet(int index);
	void clear();
	
private:
	TextureAPI bulletTexture;
	vector<Bullet> bullets;

};

