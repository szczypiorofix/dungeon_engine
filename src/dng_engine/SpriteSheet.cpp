/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

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
		this->name = name;
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			std::cout << "Unable to create texture from " << name << ". Error: " << SDL_GetError() << std::endl;
			exit(1);
		}
		else {
			this->width = loadedSurface->w;
			this->height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	this->id = imagesEnum;
	this->texture = newTexture;
	this->tileWidth = spriteWidth;
	this->tileHeight = spriteHeight;
}


void SpriteSheet::draw(SDL_Renderer* renderer, SDL_Rect* clip, int x, int y, float scale) {
	if (clip == NULL) return;
	SDL_Rect renderQuad = { x, y, (int) (this->tileWidth * scale), (int) (this->tileHeight * scale) };
	if (clip != NULL) {
		renderQuad.w = (int) (clip->w * scale);
		renderQuad.h = (int) (clip->h * scale);
	}
	SDL_RenderCopy(renderer, this->texture, clip, &renderQuad);
}


SpriteSheet::~SpriteSheet() {
	SDL_DestroyTexture(this->texture);
}


int SpriteSheet::getWidth() {
	return this->width;
}


int SpriteSheet::getHeight() {
	return this->height;
}


int SpriteSheet::getTileWidth() {
	return this->tileWidth;
}


int SpriteSheet::getTileHeight() {
	return this->tileHeight;
}


SDL_Texture* SpriteSheet::getTexture() {
	return this->texture;
}


int SpriteSheet::getColumns() {
	return this->width / this->tileWidth;
}
