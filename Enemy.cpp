#include "Enemy.h"



Enemy::Enemy(TextureAPI enemyTexture, double x, double y, int vel,double _angle) {
	mPosX = x;
	mPosY = y;
	velocity = vel;
	angle = _angle;
	this->enemyTexture = enemyTexture;
}






void Enemy::loadFromFile(SDL_Renderer *renderer) {
	

}

void Enemy::handleEvent(SDL_Event& e){

}

void Enemy::move(double timeStep) {
	
	
}


void Enemy::render(SDL_Renderer *renderer) {
	enemyTexture.render(renderer, (int)mPosX, (int)mPosY);

	
}

void Enemy::free() {
	enemyTexture.free();
}





void Enemy::createBullet(EnemyBullet &bullets, double x, double y, double angle) {
	bullets.createBullet(mPosX+24, x, mPosY+24, y, angle);
}

void Enemy::setX(double x) {
	mPosX = x;
}
void Enemy::setY(double y) {
	mPosY = y;
}
double Enemy::getX() {
	return mPosX;
}
double Enemy::getY() {
	return mPosY;
}

void Enemy::setAngle(double angle) {
	this->angle = angle;
}
double Enemy::getAngle() {
	return angle;
}

bool Enemy::isCollision(double centerX, double centerY, int radius) {
	double d = (centerX - (mPosX + ENEMY_RADIUS))*(centerX - (mPosX + ENEMY_RADIUS)) + (centerY - (mPosY + ENEMY_RADIUS))*(centerY - (mPosY + ENEMY_RADIUS));
	if (d > (ENEMY_RADIUS + radius)*(ENEMY_RADIUS + radius)) {
		return false;
	}
	else {
		return true;
	}
}