#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "TextureAPI.h"
#include "GlobalResource.h"

class Bullet {
public:
	Bullet(TextureAPI bulletTexture, double x, double y, double angle = 0);
	~Bullet();

	void free();


	void render(SDL_Renderer *renderer, double angle = 0);
	double getX();
	double getY();
	double getAngle();
	void setAngle(double angle);

	void setX(double x);
	void setY(double y);
	double getHitBoxCenterX();
	double getHitBoxCenterY();
	void setHitBoxCenterX(double x);
	void setHitBoxCenterY(double y);
	int getBulletRadius();
	
	bool isCollision(double centerX, double centerY, int radius);


private:
	TextureAPI bulletTexture;

	double mPosX;
	double mPosY;

	double angle = 0;

	int BULLET_RADIUS = 6;
	double mHitBoxCenterX, mHitBoxCenterY;


};

