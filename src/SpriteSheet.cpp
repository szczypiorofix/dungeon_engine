#include "SpriteSheet.h"
#include <SDL_image.h>


SpriteSheet::SpriteSheet(std::string name, SDL_Renderer* renderer, int spriteWidth, int spriteHeight, int imagesEnum) {
	std::cout << "Loading image " << name << std::endl;
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(name.c_str());
	if (loadedSurface == NULL) {
		std::cout << "Unable to load image " << name << ". SDL_image error: " << IMG_GetError() << std::endl;
		exit(1);
	}
	else {
		mName = name;
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			std::cout << "Unable to create texture from " << name << ". Error: " << SDL_GetError() << std::endl;
			exit(1);
		}
		else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mId = imagesEnum;
	mTexture = newTexture;
	mTileWidth = spriteWidth;
	mTileHeight = spriteHeight;
}

void SpriteSheet::draw(SDL_Renderer* renderer, SDL_Rect* clip, int x, int y, float scale) {
	if (clip == NULL) return;
	SDL_Rect renderQuad = { x, y, (int) (mTileWidth * scale), (int) (mTileHeight * scale) };
	if (clip != NULL) {
		renderQuad.w = (int) (clip->w * scale);
		renderQuad.h = (int) (clip->h * scale);
	}
	SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

SpriteSheet::~SpriteSheet() {

}

int SpriteSheet::getWidth() {
	return mWidth;
}

int SpriteSheet::getHeight() {
	return mHeight;
}

int SpriteSheet::getTileWidth() {
	return mTileWidth;
}

int SpriteSheet::getTileHeight() {
	return mTileHeight;
}

SDL_Texture* SpriteSheet::getTexture() {
	return mTexture;
}

int SpriteSheet::getColumns() {
	return mWidth / mTileWidth;
}
