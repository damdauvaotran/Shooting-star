#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "TextureAPI.h"
#include "Timer.h"
#include "Character.h"
#include "Enemy.h"
#include "GlobalResource.h"

using namespace std;


int main(int argc, char* argv[]) {
	SDL_Window * window = NULL;
	SDL_Renderer *renderer = NULL;
	
	const int SCREEN_WIDTH = GlobalResource::SCREEN_WIDTH;
	const int SCREEN_HEIGHT = GlobalResource::SCREEN_HEIGHT;


	

	/*Initialize */

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "\nCan not initialize SDL"<<SDL_GetError();
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			cout << "\nWarning: Linear texture filtering not enabled!";
		}
		else {
			window = SDL_CreateWindow("Shooting star", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);//Create window
			if (window == NULL) {
				cout << "\nCould no init window " << SDL_GetError();
			}
			else {
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
				if (renderer == NULL) {
					cout << "\nCould not init renderer"<<SDL_GetError();
				}
				else {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags)) {
						cout << "\nSDL_image could not initialize! SDL_image Error: " << IMG_GetError();
					}

					if (TTF_Init() == -1) {
						cout << "\nSDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError();
					}

					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
						cout << "\nSDL_mixer could not initialize!" << Mix_GetError();
					}

				}
			}
		}
	}


	/*Load media*/
	
	//Load music
	Mix_Music *backgroundMusic = Mix_LoadMUS("Resource/Sound/shootingStar.mp3");
	Mix_Chunk *fireSound = Mix_LoadWAV("Resource/Sound/shot.wav");

	//Load background
	TextureAPI background;
	background.loadFromFile(renderer, "Resource/Image/background.png");

	//Load Character
	Character mainCharacter;
	mainCharacter.loadFromFile(renderer);

	//Load enemy
	Enemy enemy (GlobalResource::MAIN_AREA_WIDTH/2, 100, 0,0);
	enemy.loadFromFile(renderer);

	//Load bullet

	TextureAPI bullet;
	bullet.loadFromFile(renderer, "Resource/Image/bullet.png");

	

	/*Main loop*/

	int scrollingOffset = 0;//this make the screen scroll forever
	Timer moveTimer;
	Timer frameTimer;
	Timer scrollingTimer;
	Timer characterShootTimer;
	Timer enemyShootTimer;

	moveTimer.start();
	frameTimer.start();
	scrollingTimer.start();
	characterShootTimer.start();
	enemyShootTimer.start();

	int bulletCounter = 0;

	bool quit = false;
	SDL_Event e;
	while (!quit) {

		while (SDL_PollEvent(&e)) {

			//Handle event

			if (e.type == SDL_QUIT) {
				quit = true;
			}
			mainCharacter.handleEvent(e);

		}

		//Computing somthing

		// Axis of  mainCharater 
		
		

			mainCharacter.move(moveTimer.getTicks() / 1000.0);
			moveTimer.start();//reset the timer
		

		if (characterShootTimer.getTicks() > 100) {
			mainCharacter.shoot(fireSound, characterShootTimer.getTicks() / 1000.0);
			characterShootTimer.start();//reset Timer
			
		}

		mainCharacter.moveBullets(frameTimer.getTicks() / 1000.0);
		
		//Enemy fire
		
		if (enemyShootTimer.getTicks()>100) {
			for (int i = 0; i < 10; i++) {
				double angle = (bulletCounter * 10+ i* 36) * M_PI / 180;
				double x = 50 * cos(angle);
				double y = 50 * sin(angle);
				enemy.createBullet(x, y, angle);
			}

			bulletCounter++;
			enemyShootTimer.start();
			
		}


		enemy.moveBullets(frameTimer.getTicks() / 1000.0);

		




		
	
		frameTimer.start();


		//Play music
		if (Mix_PlayingMusic() == 0) {
			//Play the music
			Mix_PlayMusic(backgroundMusic, -1);
		}

		//Scroll screen
		if (scrollingTimer.getTicks() > 16) {
			scrollingOffset++;
			scrollingTimer.start(); //Reset the timer
		}
		if (scrollingOffset > background.getHeight()) {
			scrollingOffset = 0;
		}

		//Clear screen
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		//Render here
		background.render(renderer, 0, scrollingOffset);
		background.render(renderer, 0, scrollingOffset-background.getHeight());
		mainCharacter.render(renderer);
		enemy.render(renderer);

		//Update screen
		SDL_RenderPresent(renderer);
		
		
		
	}
	

	/*Quit*/ 
	
	background.free();
	mainCharacter.free();
	

	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	Mix_FreeMusic(backgroundMusic);
	backgroundMusic = NULL;

	Mix_FreeChunk(fireSound);
	fireSound = NULL;



	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();


	return 0;

}

