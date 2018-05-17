#pragma once
#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>
#include <string>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "TextureAPI.h"
#include "Timer.h"
#include "Character.h"
#include "Enemy.h"
#include "Enemies.h"
#include "EnemyBullet.h"
#include "GlobalResource.h"

using namespace std;


int main(int argc, char* argv[]) {
	srand(time(NULL));
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
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

	// Load highscore
	ifstream highScoreFileInput("Resource/highscore.txt");
	long highScore;
	highScoreFileInput >> highScore;
	highScoreFileInput.close();


	//Load fps 
	TextureAPI fpsTexture;

	//Load music
	Mix_Music *backgroundMusic = Mix_LoadMUS("Resource/Sound/shootingStar.mp3");
	Mix_Music *menuMusic = Mix_LoadMUS("Resource/Sound/undertale.mp3");
	Mix_Chunk *fireSound = Mix_LoadWAV("Resource/Sound/shot.wav");

	//Load background
	TextureAPI background;
	background.loadFromFile(renderer, "Resource/Image/background.png");

	//Load Character
	Character mainCharacter;
	mainCharacter.loadFromFile(renderer, "Resource/Image/main-character.png");

	//Load enemy
	Enemies enemies;
	enemies.loadFromFile(renderer, "Resource/Image/enemy.png");

	

	//Load bullet

	EnemyBullet charBullet;
	charBullet.loadFromFile(renderer, "Resource/Image/bullet.png");

	EnemyBullet enemyBullets;
	enemyBullets.loadFromFile(renderer, "Resource/Image/greenbullet.png");

	//load font
	TTF_Font *gugi;
	gugi = TTF_OpenFont("Resource/Font/Gugi.ttf",40);
	TTF_Font *gugi20;
	gugi20 = TTF_OpenFont("Resource/Font/Gugi.ttf", 20);

	//Score texture
	TextureAPI highScoreTexture;
	TextureAPI scoreTexture;

	TextureAPI scoreBackground;
	scoreBackground.loadFromFile(renderer, "Resource/Image/Nop.png");
	
	//Game over texture
	TextureAPI gameOverTexture;
	stringstream gameOverText;
	gameOverText.str("GAME OVER");
	gameOverTexture.loadFromRenderedText(renderer, gameOverText.str(), { 255,255,255,255 }, gugi);

	TextureAPI restartTexture;
	stringstream restartText;
	restartText.str("Press R to restart");
	restartTexture.loadFromRenderedText(renderer, restartText.str(), { 255,255,255,255 }, gugi20);
	//Load menu

	TextureAPI menuTexture;
	menuTexture.loadFromFile(renderer, "Resource/Image/menu.png");

	

	/*Main loop*/

	

	int scrollingOffset = 0;//this make the screen scroll forever
	unsigned int stage = 0;
	bool isGameOver = false;
	double level = 4;
	stringstream scoreText;
	stringstream highScoreText;
	stringstream fpsText;


	

	ofstream highScoreFileOutput;
	

	long score = 0;
	Timer gameTimer;
	Timer createEnemyTimer;
	Timer frameTimer;
	Timer scrollingTimer;
	Timer characterShootTimer;
	Timer enemyShootTimer;

	

	int bulletCounter = 0;

	bool quit = false;
	SDL_Event e;

	//Menu

	bool isInMenu = true;
	bool isInGame = false;
	int menuCurrentState = 1;
	SDL_Rect menuClip;
	



	

	while (!quit) {
		//Menu
		if(isInMenu) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				if (e.type == SDL_KEYDOWN) {
					switch (e.key.keysym.sym) {
					case SDLK_UP:
						menuCurrentState--;
						if (menuCurrentState < 1) {
							menuCurrentState = 1;
						}
						break;
					case SDLK_DOWN:
						menuCurrentState++;
						if (menuCurrentState > 2) {
							menuCurrentState = 2;
						}
						break;
					case SDLK_RETURN:
						switch (menuCurrentState) {
						case 1:
							isInMenu = false;
							isInGame = true;
							gameTimer.start();
							createEnemyTimer.start();
							frameTimer.start();
							scrollingTimer.start();
							characterShootTimer.start();
							enemyShootTimer.start();
						
							break;
						case 2:
							isInMenu = false;
							isInGame = false;
						
							quit = true;
							break;
						}
						break;
					default:
						break;
					}
				}
			}


			switch (menuCurrentState) {
			case 1:
				menuClip.x = 0;
				menuClip.y = 0;
				menuClip.w = 800;
				menuClip.h = 600;
				break;
			case 2:
				menuClip.x = 0;
				menuClip.y = 0;
				menuClip.w = 800;
				menuClip.h = 600;
			default:
				menuClip.x = 800;
				menuClip.y = 0;
				menuClip.w = 800;
				menuClip.h = 600;
				break;
			}
			

			//Clear screen
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);

			// render menu
			menuTexture.render(renderer, 0, 0, &menuClip);

			//Update screen
			SDL_RenderPresent(renderer);
			if (frameTimer.getTicks() < 1000 / 65) {
				SDL_Delay(1000 / 65 - frameTimer.getTicks());
			}
		}


		//Game loop
		if (isInGame) {
			while (SDL_PollEvent(&e)) {

				//Handle event

				if (e.type == SDL_QUIT) {
					quit = true;
				}

				mainCharacter.handleEvent(e);
				if (e.type == SDL_KEYDOWN) {
					switch (e.key.keysym.sym) {
					case SDLK_ESCAPE:
						isInGame = false;
						isInMenu = true;
						Mix_HaltMusic();
					}
				}	
				if (isGameOver) {
					if (e.type == SDL_KEYDOWN) {
						if (e.key.keysym.sym == SDLK_r) {
							isGameOver = false;
							gameTimer.start();
							createEnemyTimer.start();
							frameTimer.start();
							scrollingTimer.start();
							characterShootTimer.start();
							enemyShootTimer.start();

							level = 4;//Reset level
							score = 0;
							mainCharacter.setDefaultPlace(); //set main character to defalt place
							enemies.clear(); //delete all enemy on screen

							charBullet.clear();
							enemyBullets.clear();

						}
					}
				}

			}

			//Computing somthing


			// Collision
			if (enemies.isCollision(mainCharacter.getX() + 22, mainCharacter.getY() + 36, 4) || enemyBullets.isCollision(mainCharacter.getX() + 22, mainCharacter.getY() + 36, 4)) {
				isGameOver = true;
				Mix_HaltMusic();
				gameTimer.stop();
				createEnemyTimer.stop();
				frameTimer.stop();
				scrollingTimer.stop();
				characterShootTimer.stop();
				enemyShootTimer.stop();

			}

			if (!isGameOver) {
				for (unsigned int i = 0; i < enemies.getEnemies().size(); i++) {
					Enemy thisEnemy = enemies.getEnemies()[i];
					for (unsigned int j = 0; j < charBullet.getBullets().size(); j++) {
						if (charBullet.getBullets()[j].isCollision(thisEnemy.getX() + 24, thisEnemy.getY() + 24, 24)) {
							score += 100;
							enemies.deleteEnemy(i);
							charBullet.deleteBullet(j);
							break;
						}
					}

				}




				//Character shoot
				if (characterShootTimer.getTicks() > 400) {
					mainCharacter.createBullet(charBullet);
					characterShootTimer.start();//reset Timer

				}

				mainCharacter.moveBullets(frameTimer.getTicks() / 1000.0);


				// Score
				if (score > highScore) {
					highScore = score;
					highScoreFileOutput.open("Resource/highscore.txt");
					highScoreFileOutput << highScore;
					highScoreFileOutput.close();

				}
				highScoreText.str("");
				highScoreText << "High score: " << highScore;
				highScoreTexture.loadFromRenderedText(renderer, highScoreText.str(), { 255,255,255,255 }, gugi);
				scoreText.str("");
				scoreText << "Your score: " << score;
				scoreTexture.loadFromRenderedText(renderer, scoreText.str(), { 255,255,255,255 }, gugi);

				//Create enemy
				if (gameTimer.getTicks() > 300) {
					stage = 1;
				}
				if (stage == 1) {
					if (createEnemyTimer.getTicks() > 1000) {
						enemies.createEnemy((rand() % 8) * 50, -GlobalResource::ENEMY_HEIGHT, GlobalResource::ENEMY_VEL, 270);

						createEnemyTimer.start();

					}
				}
				//Enemy shoot

				if (enemyShootTimer.getTicks() > 1000) {
					for (unsigned int index = 0; index < enemies.getEnemies().size(); index++) {
						for (int i = 0; i < level; i++) {
							double angle = i * (360 / level);
							enemies.getEnemies()[index].createBullet(enemyBullets, 0, 0, angle);

						}
					}
					level += 0.5;
					enemyShootTimer.start();
				}


				//Move

				mainCharacter.move(frameTimer.getTicks() / 1000.0);
				enemies.moveEnemy(frameTimer.getTicks() / 1000.0);
				enemyBullets.moveBullets(GlobalResource::ENEMY_BULLET_VEL, frameTimer.getTicks() / 1000.0);
				charBullet.moveBullets(GlobalResource::BULLET_VEL, frameTimer.getTicks() / 1000.0);



				//FPS
				fpsText.str("");
				fpsText << "FPS: " << 1000.0 / frameTimer.getTicks();
				fpsTexture.loadFromRenderedText(renderer, fpsText.str(), { 255,255,255,255 }, gugi);



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
			}

			//Clear screen
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);

			//Render here
			background.render(renderer, 0, scrollingOffset);
			background.render(renderer, 0, scrollingOffset - background.getHeight());
			mainCharacter.render(renderer);
			enemies.render(renderer);
			enemyBullets.render(renderer);
			charBullet.render(renderer);
			scoreBackground.render(renderer, 400, 0);
			fpsTexture.render(renderer, 410, 30);
			highScoreTexture.render(renderer, 410, 350);
			scoreTexture.render(renderer, 410, 400);
			if (isGameOver) {
				gameOverTexture.render(renderer, 90, GlobalResource::MAIN_AREA_HEIGHT / 2);
				restartTexture.render(renderer, 90, GlobalResource::MAIN_AREA_HEIGHT / 2 + 50);
			}




			//Update screen
			SDL_RenderPresent(renderer);
			if (frameTimer.getTicks() < 1000 / 65) {
				SDL_Delay(1000 / 65 - frameTimer.getTicks());
			}
		}
	}
		
	
	

	/*Quit*/ 
	
	background.free();
	mainCharacter.free();
	scoreTexture.free();
	highScoreTexture.free();

	

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

