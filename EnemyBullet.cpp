#include "EnemyBullet.h"



EnemyBullet::EnemyBullet() {
	
}


EnemyBullet::~EnemyBullet() {
}

void EnemyBullet::loadFromFile(SDL_Renderer *renderer, string path) {
	bulletTexture.loadFromFile(renderer, path);

}

void EnemyBullet::render (SDL_Renderer *renderer) {
	for (unsigned int i = 0; i < bullets.size(); i++) {
		bullets[i].render(renderer, -bullets[i].getAngle());
	}
}



void EnemyBullet::moveBullets(double vel, double timeStep) {
	for (int i = 0; i < bullets.size(); i++) {

		double angle = bullets[i].getAngle() *M_PI / 180;
		bullets[i].setX(bullets[i].getX() + vel*cos(angle)* timeStep);
		bullets[i].setY(bullets[i].getY() - vel*sin(angle)* timeStep);


		if (bullets[i].getY() + GlobalResource::BULLET_HEIGHT < 0
			|| bullets[i].getX() + GlobalResource::BULLET_WIDTH <0
			|| bullets[i].getY() > GlobalResource::MAIN_AREA_HEIGHT
			|| bullets[i].getX()  > GlobalResource::MAIN_AREA_WIDTH) {

			bullets.erase(bullets.begin() + i);
		}
	}

}

void EnemyBullet::createBullet(double mPosX, double x, double mPosY, double y, double angle) {
	Bullet newBullet = Bullet(bulletTexture, mPosX + x , mPosY -y , angle);
	bullets.push_back(newBullet);
}

bool EnemyBullet::isCollision(double centerX, double centerY, int radius) {
	for (Bullet bullet : bullets) {
		if (bullet.isCollision(centerX, centerY, radius)) {
			return true;
		}
	}
	return false;
}

vector<Bullet> EnemyBullet::getBullets() {
	return bullets;
}


