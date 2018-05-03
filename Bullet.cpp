#include "Bullet.h"



Bullet::Bullet(TextureAPI bulletTexture, int x, int y) {
	this->bulletTexture = bulletTexture;
	mPosX = x;
	mPosY = y;
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

void Bullet::setY(double y) {
	mPosY = y;
}
void Bullet::setX(double x) {
	mPosX = x;
}

double Bullet::getAngle() {
	return angle;
}

void Bullet::setAngle(double _angle) {
	angle = _angle;
}
