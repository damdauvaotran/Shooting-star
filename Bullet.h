#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "TextureAPI.h"
#include "GlobalResource.h"

class Bullet {
public:
	Bullet(TextureAPI bulletTexture, int x, int y);
	~Bullet();

	void free();

	void move();

	void render(SDL_Renderer *renderer, double angle = 0);
	double getX();
	double getY();
	double getAngle();
	void setAngle(double angle);

	void setX(double x);
	void setY(double y);
	
private:
	TextureAPI bulletTexture;

	//The X and Y offsets of the dot
	double mPosX;
	double mPosY;

	double angle = 0;

};

