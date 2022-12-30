#pragma once
#include <iostream>
#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
class TextureAPI {
public:
	TextureAPI();
	~TextureAPI();

	bool loadFromFile(SDL_Renderer* renderer, std::string path, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);

	void free();

	//Set color modulation  
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending 
	void setBlendMode(SDL_BlendMode blending);
	//Set alpha modulation 
	void setAlpha(Uint8 alpha);
	//Load text
	bool loadFromRenderedText(SDL_Renderer *renderer, std::string textureText, SDL_Color textColor, TTF_Font *gFont);

	void render(SDL_Renderer*, int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();
private:
	SDL_Texture * mTexture;

	int mWidth;
	int mHeight;

};
