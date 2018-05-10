#include "Character.h"



Character::Character() {
	mPosX = (320 - CHARACTER_WIDTH) / 2;
	mPosY = GlobalResource::SCREEN_HEIGHT - CHARACTER_HEIGHT;
	mHitBoxCenterX = mPosX + 22;
	mHitBoxCenterY = mPosY + 36;
	mVelX = 0;
	mVelY = 0;
	hp = 3;
}



void Character::loadFromFile(SDL_Renderer *renderer) {
	characterTexture.loadFromFile(renderer, CHARACTER_PATH);
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

	mHitBoxCenterX = mPosX + 22;
	mHitBoxCenterY = mPosY + 36;
	
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

void Character::shoot(Mix_Chunk *sound, double stepTime) {
	createBullet(mPosX, mPosY);
	
}

void Character::moveBullets(double timeStep) {
	for (int i = 0; i < bullets.size(); i++ ) {
		bullets[i].setY(bullets[i].getY() - GlobalResource::BULLET_VEL* (double)timeStep);
	}


	
}


bool Character::checkCollision(Bullet bullet) {
	double d = (mHitBoxCenterX - bullet.getHitBoxCenterX())*(mHitBoxCenterX - bullet.getHitBoxCenterX()) + (mHitBoxCenterY - bullet.getHitBoxCenterY())*(mHitBoxCenterY - bullet.getHitBoxCenterY());
	if (d < 64) {
		return true;
	}
	return false;
}
bool Character::checkAlive(vector<Bullet> bullets) {
	for (Bullet bullet : bullets) {
		if (checkCollision(bullet)) {
			hp--;
		}
	}

	if (hp < 1) {
		return false;
	}
	else {
		return true;
	}
}

void Character::createBullet(double x, double y, double angle) {
	Bullet bullet = Bullet(bulletTexture, x, y, angle);
	bullets.push_back(bullet);
}