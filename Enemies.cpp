#include "Enemies.h"



Enemies::Enemies() {
}


Enemies::~Enemies() {
}

void Enemies::loadFromFile(SDL_Renderer *renderer, string path) {
		enemyTexture.loadFromFile(renderer, path);
}

void Enemies::render(SDL_Renderer *renderer) {
	for (Enemy enemy : enemies) {
		enemy.render(renderer);
	}

}

void Enemies::createEnemy(double x, double y, double angle) {
	Enemy enemy(enemyTexture ,x, y, 100, angle);
	enemies.push_back(enemy);
}
	
void Enemies::moveEnemy(double stepTime) {
	for (unsigned int i = 0; i < enemies.size(); i++ ) {
		enemies[i].setX(enemies[i].getX() + GlobalResource::ENEMY_VEL * stepTime*cos(enemies[i].getAngle()*M_PI / 180));
		enemies[i].setY(enemies[i].getY() - GlobalResource::ENEMY_VEL * stepTime*sin(enemies[i].getAngle()*M_PI / 180));

		if (enemies[i].getY() + GlobalResource::BULLET_HEIGHT < 0
			|| enemies[i].getX() + GlobalResource::BULLET_WIDTH <0
			|| enemies[i].getY() > GlobalResource::MAIN_AREA_HEIGHT
			|| enemies[i].getX()  > GlobalResource::MAIN_AREA_WIDTH) {

			enemies.erase(enemies.begin() + i);
		}

		
	}
}

vector<Enemy> Enemies::getEnemy() {
	return enemies;
}

void Enemies::deleteEnemy(int index) {
	enemies.erase(enemies.begin() + index);
}

bool Enemies::isCollision(double centerX, double centerY, int radius) {
	for (Enemy enemy : enemies) {
		if (enemy.isCollision(centerX, centerY, radius)) {
			return true;
		}
	}
	return false;
}