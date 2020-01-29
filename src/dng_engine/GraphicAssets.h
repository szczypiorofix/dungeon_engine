/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _GRAPHICASSETS_H_
#define _GRAPHICASSETS_H_
#pragma once

#include <iostream>
#include "SpriteSheet.h"

constexpr int MAX_SPRITESHEETS = 2;


class GraphicAssets {

public:

	static GraphicAssets* getAssets();
	static void loadAsset(std::string fileName, SDL_Renderer* renderer, int spriteWidth, int spriteHeight, int imagesEnum);
	static void releaseAssets();

	SpriteSheet* spriteSheets[MAX_SPRITESHEETS];

private:

	static GraphicAssets* instance;
	GraphicAssets();
	~GraphicAssets();
};

#endif
