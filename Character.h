#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "TextureAPI.h"
#include "Screen.h"

using namespace std;

class Character {
public:
	
	static const int CHARACTER_WIDTH = 44;
	static const int CHARACTER_HEIGHT = 56;

	static const int MIN_CHARACTER_VEL = 1;
	static const int MAX_CHARACTER_VEL = 5;

	Character();
	

	void loadFromFile(SDL_Renderer *renderer);

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move();

	//Shows the dot on the screen
	void render(SDL_Renderer *renderer);

	void free();
	
private:
	
	TextureAPI characterTexture;

	SDL_Rect currentClip = { 0,0,44,56 };
	
	
	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;

	const string CHARACTER_PATH = "Resource/Image/character.png";
};


