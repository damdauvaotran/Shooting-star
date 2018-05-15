#include "Character.h"



Character::Character() {
	mPosX = (400 - CHARACTER_WIDTH) / 2;
	mPosY = GlobalResource::SCREEN_HEIGHT - CHARACTER_HEIGHT;

	mVelX = 0;
	mVelY = 0;
	hp = 3;
}



void Character::loadFromFile(SDL_Renderer *renderer, string path) {
	characterTexture.loadFromFile(renderer, path);
	bulletTexture.loadFromFile(renderer, BULLET_PATH);
}


void Character::handleEvent(SDL_Event& e) {
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_LSHIFT] ) {
		mVelY = -MAX_CHARACTER_VEL;
		
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN] && !currentKeyStates[SDL_SCANCODE_LSHIFT]) {
		mVelY = MAX_CHARACTER_VEL;
	}
	else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LSHIFT]) {
		mVelY = -MIN_CHARACTER_VEL;
		
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LSHIFT]) {
		mVelY = MIN_CHARACTER_VEL;
		
	}
	

	if (currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_LSHIFT]) {
		mVelX = -MAX_CHARACTER_VEL;
		currentClip.x = 44;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LSHIFT]) {
		mVelX = MAX_CHARACTER_VEL;
		currentClip.x = 85;
	}
	else if (currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_LSHIFT]) {
		mVelX = -MIN_CHARACTER_VEL;
		currentClip.x = 44;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT] && currentKeyStates[SDL_SCANCODE_LSHIFT]) {
		mVelX = MIN_CHARACTER_VEL;
		currentClip.x = 85;

	}

	if (!currentKeyStates[SDL_SCANCODE_UP]&& !currentKeyStates[SDL_SCANCODE_DOWN]){
			mVelY = 0;
			
	}
	if (!currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_RIGHT]) {
		mVelX = 0;
		currentClip.x = 0;
	}

	if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_DOWN]) {
		mVelY = 0;
		currentClip.x = 0;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
		mVelX = 0;
		currentClip.x = 0;
	}

	
		 


	
}


void Character::move(double timeStep) {
	mPosX += mVelX*timeStep;
	mPosY += mVelY*timeStep;

	if (mPosX < 0) {
		mPosX = 0;
	}
	else if (mPosX > GlobalResource::MAIN_AREA_WIDTH - CHARACTER_WIDTH) {
		mPosX = GlobalResource::MAIN_AREA_WIDTH - CHARACTER_WIDTH;
	}

	if (mPosY < 0) {
		mPosY = 0;
	}
	else if (mPosY   > GlobalResource::MAIN_AREA_HEIGHT - CHARACTER_HEIGHT) {
		mPosY = GlobalResource::MAIN_AREA_HEIGHT - CHARACTER_HEIGHT;
	}


}

//Shows the dot on the screen
void Character::render(SDL_Renderer *renderer) {
	characterTexture.render(renderer, mPosX, mPosY, &currentClip);
	for (Bullet bullet : bullets) {
		bullet.render(renderer, bullet.getAngle());
	}
}

void Character::free() {
	characterTexture.free();
}

void Character::shoot() {
	
	
}

void Character::moveBullets(double timeStep) {
	for (int i = 0; i < bullets.size(); i++ ) {
		bullets[i].setY(bullets[i].getY() - GlobalResource::BULLET_VEL* (double)timeStep);
	}	
}





void Character::createBullet(EnemyBullet &bullets, double angle) {
	bullets.createBullet(mPosX+ 14, 0, mPosY-5, 0, angle);
}

double Character::getX() {
	return mPosX;
}
double Character::getY() {
	return mPosY;
}

vector<Bullet> Character::getBullets() {
	return bullets;
}

void Character::setDefaultPlace() {
	mPosX = (400 - CHARACTER_WIDTH) / 2;
	mPosY = GlobalResource::SCREEN_HEIGHT - CHARACTER_HEIGHT;
}