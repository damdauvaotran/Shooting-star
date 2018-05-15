#include "Bullet.h"



Bullet::Bullet(TextureAPI bulletTexture, double x, double y, double angle) {
	this->bulletTexture = bulletTexture;
	mPosX = x;
	mPosY = y;
	this->angle = angle;
}


Bullet::~Bullet() {

}



void Bullet::render(SDL_Renderer *renderer, double angle ) {
	bulletTexture.render(renderer, mPosX, mPosY, NULL, angle);
}

void Bullet::free() {
	bulletTexture.free();
}

double Bullet::getX() {
	return mPosX;
}
double Bullet::getY() {
	return mPosY;
}

void Bullet::setX(double x) {
	mPosX = x;
}

void Bullet::setY(double y) {
	mPosY = y;

}

double Bullet::getAngle() {
	return angle;
}

void Bullet::setAngle(double angle) {
	this->angle = angle;
}


int Bullet::getBulletRadius() {
	return BULLET_RADIUS;
}

bool Bullet::isCollision(double centerX, double centerY, int radius) {
	double d = (centerX - (mPosX+7))*(centerX - (mPosX+7)) + (centerY - (mPosY+7))*(centerY - (mPosY+7));
	if (d > (BULLET_RADIUS + radius)*(BULLET_RADIUS + radius)) {
		return false;
	}else {
		return true;
	}
}