#include "Enemy.h"



Enemy::Enemy(double x, double y, double vel) {
	mPosX = x;
	mPosY = y;
	velocity = GlobalResource::ENEMY_VEL;
}



Enemy::~Enemy() {
}



void Enemy::loadFromFile(SDL_Renderer *renderer) {
	enemyTexture.loadFromFile(renderer, ENEMY_PATH);
	bulletTexture.loadFromFile(renderer, BULLET_PATH);

}

void Enemy::handleEvent(SDL_Event& e){

}

void Enemy::move(double timeStep) {
	mPosX += velocity * timeStep;
	
}


void Enemy::render(SDL_Renderer *renderer, double angle) {
	enemyTexture.render(renderer, (int)mPosX, (int)mPosY);

	
}

void Enemy::free() {
	enemyTexture.free();
}





void Enemy::createBullet(EnemyBullet &bullets, double x, double y, double angle) {
	bullets.createBullet(mPosX, x, mPosY, y, angle);
	
}

