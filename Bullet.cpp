#include "Bullet.h"



Bullet::Bullet(TextureAPI bulletTexture, int x, int y, double angle) {
	this->bulletTexture = bulletTexture;
	mPosX = x;
	mPosY = y;
	this->angle = angle;
}


Bullet::~Bullet() {

}



void Bullet::render(SDL_Renderer *renderer, double angle ) {
	bulletTexture.render(renderer, mPosX, mPosY,NULL, angle);
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
	setHitBoxCenterX(x + BULLET_RADIUS);
}

void Bullet::setY(double y) {
	mPosY = y;
	setHitBoxCenterX(y + BULLET_RADIUS);
}

double Bullet::getAngle() {
	return angle;
}

void Bullet::setAngle(double angle) {
	this->angle = angle;
}

double Bullet::getHitBoxCenterX() {
	return mHitBoxCenterX;
}
double Bullet::getHitBoxCenterY() {
	return mHitBoxCenterY;
}
void Bullet::setHitBoxCenterX(double x) {
	mHitBoxCenterX = x;

}
void Bullet::setHitBoxCenterY(double y) {
	mHitBoxCenterY = y;
}
int Bullet::getBulletRadius() {
	return BULLET_RADIUS;
}


