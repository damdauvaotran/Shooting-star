#include "Enemy.h"



Enemy::Enemy(double x, double y, double velX, double velY) {
	mPosX = x;
	mPosY = y;
	mVelX = velX;
	mVelY = velY;
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
	for (Bullet singleBullet : bullets) {
		singleBullet.setX(singleBullet.getX() + GlobalResource::ENEMY_BULLET_VEL*cos(singleBullet.getAngle()*timeStep ));
		singleBullet.setY(singleBullet.getY() + GlobalResource::ENEMY_BULLET_VEL*sin(singleBullet.getAngle()*timeStep ));
	}

}


void Enemy::render(SDL_Renderer *renderer, double angle) {
	enemyTexture.render(renderer, (int)mPosX, (int)mPosY);

	for (unsigned int i = 0; i < bullets.size(); i++) {
		bullets[i].render(renderer,  -bullets[i].getAngle()*180/M_PI );

	}
}

void Enemy::free() {

}

void Enemy::shoot(double timeStep) {
	createBullets();
	for (unsigned int i = 0; i < bullets.size(); i++) {
		if (bullets[i].getY() + GlobalResource::BULLET_HEIGHT < 0
			||bullets[i].getX() + GlobalResource::BULLET_WIDTH <0 
			|| bullets[i].getY() > GlobalResource::MAIN_AREA_HEIGHT
			|| bullets[i].getX()  > GlobalResource::MAIN_AREA_WIDTH) {

			bullets.erase(bullets.begin() + i);
		}



	}
}

void Enemy::createBullets() {
	for (int i = 0; i < 37; i++) {
		double phi = (10 * i);
		double r = 50 +  20*phi;
		double x = r * cos(phi);
		double y = r * sin(phi);

		Bullet newBullet = Bullet(bulletTexture, mPosX+25 + x, mPosY +25 - y, phi);
		bullets.push_back(newBullet);
	} 
	

}

void Enemy::moveBullets(double timeStep) {
	for (int i = 0; i < bullets.size(); i++) {
	
		double angle = bullets[i].getAngle();
		bullets[i].setX(bullets[i].getX() + GlobalResource::ENEMY_BULLET_VEL*cos(angle)* timeStep);
		bullets[i].setY(bullets[i].getY() - GlobalResource::ENEMY_BULLET_VEL*sin(angle)* timeStep);
		bullets[i].setHitBoxCenterX(bullets[i].getX() + bullets[i].getBulletRadius());
		bullets[i].setHitBoxCenterY(bullets[i].getY() +  bullets[i].getBulletRadius());


		if (bullets[i].getY() + GlobalResource::BULLET_HEIGHT < 0
			|| bullets[i].getX() + GlobalResource::BULLET_WIDTH <0
			|| bullets[i].getY() > GlobalResource::MAIN_AREA_HEIGHT
			|| bullets[i].getX()  > GlobalResource::MAIN_AREA_WIDTH) {

			bullets.erase(bullets.begin() + i);
		}
	}
	
}

void Enemy::createBullet(double x, double y, double angle) {
	Bullet newBullet = Bullet(bulletTexture, mPosX + x + 25, mPosY - y +25 , angle);
	bullets.push_back(newBullet);
}

vector<Bullet> Enemy::getBullets() {
	return bullets;
}