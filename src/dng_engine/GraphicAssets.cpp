/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "GraphicAssets.h"
#include "Defines.h"


GraphicAssets::GraphicAssets() {
	std::cout << "Creating new assets..." << std::endl;
	spriteSheets[SpriteSheet::BASICTILES] = NULL;
	spriteSheets[SpriteSheet::CHARACTERS] = NULL;
	spriteSheets[SpriteSheet::WALLPAPER] = NULL;
	spriteSheets[SpriteSheet::LOGO] = NULL;
	spriteSheets[SpriteSheet::MAINMENUSHADE] = NULL;
	spriteSheets[SpriteSheet::GUI_BUTTON] = NULL;
	spriteSheets[SpriteSheet::GUI_CONTROLLS] = NULL;
}


GraphicAssets::~GraphicAssets() {

}


void GraphicAssets::releaseAssets() {
	std::cout << "Releasing textures... ";
	for (int i = 0; i < MAX_SPRITESHEETS; i++) {
		delete GraphicAssets::getAssets()->spriteSheets[i];
	}
	std::cout << "done." << std::endl;
}


GraphicAssets* GraphicAssets::getAssets() {
	if (!instance) {
		instance = new GraphicAssets();
	}
	return instance;
}


void GraphicAssets::loadAsset(std::string fileName, SDL_Renderer* renderer, int spriteWidth, int spriteHeight, int imagesEnum) {
	SpriteSheet* tempSpriteSheet = new SpriteSheet(DIR_RES_IMAGES + fileName, renderer, spriteWidth, spriteHeight, imagesEnum);
	GraphicAssets::getAssets()->spriteSheets[imagesEnum] = tempSpriteSheet;
}

GraphicAssets* GraphicAssets::instance = nullptr;
