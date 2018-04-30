#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;


int main(int argc, char* argv[]) {
	SDL_Window * window = NULL;
	SDL_Renderer *renderer = NULL;
	
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;


	//Initialize 

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << SDL_GetError();
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			cout << "\nWarning: Linear texture filtering not enabled!";
		}
		else {
			window = SDL_CreateWindow("nam dep trai", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);//Create window
			if (window == NULL) {
				cout << "\nCould no init window " << SDL_GetError();
			}
			else {
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				if (renderer == NULL) {
					cout << SDL_GetError();
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



	return 0;

}

