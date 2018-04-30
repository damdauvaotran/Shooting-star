#include "TextureAPI.h"

using namespace std;

TextureAPI::TextureAPI() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}


TextureAPI::~TextureAPI() {
}

bool TextureAPI::loadFromFile(SDL_Renderer* renderer, std::string path) {
	free();
	SDL_Texture *newTexture = NULL;
	SDL_Surface *newSurface = IMG_Load(path.c_str());
	if (newSurface == NULL) {
		cout << "\nCould not init surface" << IMG_GetError;
	}
	else {
		SDL_SetColorKey(newSurface, 1, SDL_MapRGB(newSurface->format, 0, 255, 255)); //Color key
		newTexture = SDL_CreateTextureFromSurface(renderer, newSurface);
		if (newTexture == NULL) {
			cout << "\nCould not create texture " << SDL_GetError;

		}
		else {
			mWidth = newSurface->w;
			mHeight = newSurface->h;
		}

		SDL_FreeSurface(newSurface);

	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void TextureAPI::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

//Set color modulation  
void TextureAPI::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

//Set blending 
void TextureAPI::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(mTexture, blending);
}
//Set alpha modulation 
void TextureAPI::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

bool TextureAPI::loadFromRenderedText(SDL_Renderer *renderer, std::string textureText, SDL_Color textColor, TTF_Font *gFont) {
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL) {
		cout << "Unable to render text surface! SDL_ttf Error:\n" << TTF_GetError();
	}
	else {
		//Create texture from surface pixels 
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL) {
			cout << "Could not create texture \n" << SDL_GetError();
		}
		else {
			//Get image dimensions 
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		//Get rid of old surface 
		SDL_FreeSurface(textSurface);
	}
	//Return success 
	return mTexture != NULL;
}

void TextureAPI::render(SDL_Renderer*renderer, int x, int y, SDL_Rect *clip, double angle , SDL_Point* center, SDL_RendererFlip flip ) {
	SDL_Rect renderQuad = { x,y,mWidth, mHeight };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int TextureAPI::getWidth() {
	return mWidth;
}
int TextureAPI::getHeight(){
	return mHeight;
}
