/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "GraphicAssets.h"
#include "Defines.h"


GraphicAssets::GraphicAssets() {
	std::cout << "Creating new graphic assets..." << std::endl;
	this->textures[IMAGE_ASSETS_MAIN_MENU_BACKGROUND] = NULL;
	this->textures[IMAGE_ASSETS_LOGO] = NULL;
	this->textures[IMAGE_ASSETS_MAIN_MENU_BUTTONS] = NULL;
	this->textures[IMAGE_ASSETS_VINGUE_FONT] = NULL;
	this->textures[IMAGE_ASSETS_TEST_TEXTURE] = NULL;
}


GraphicAssets::~GraphicAssets() {}


void GraphicAssets::releaseAssets() {
	std::cout << "Releasing textures... ";
	for (int i = 0; i < MAX_SPRITESHEETS; i++) {
		delete GraphicAssets::getAssets()->textures[i];
	}
	std::cout << "done." << std::endl;
}


GraphicAssets* GraphicAssets::getAssets() {
	if (!instance) {
		instance = new GraphicAssets();
	}
	return instance;
}


void GraphicAssets::addToAssets(std::string fileName, GLfloat tileWidth, GLfloat tileHeight, const int imagesEnum) {
	Texture* tempTexture = new Texture(fileName, tileWidth, tileHeight);
	GraphicAssets::getAssets()->textures[imagesEnum] = tempTexture;
}


void GraphicAssets::addToAssets(std::string fileName, const int imagesEnum) {
	Texture* tempTexture = new Texture(fileName);
	GraphicAssets::getAssets()->textures[imagesEnum] = tempTexture;
}


GraphicAssets* GraphicAssets::instance = nullptr;
