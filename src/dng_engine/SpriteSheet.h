/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_
#pragma once

#include <iostream>
#include <SDL.h>


class SpriteSheet {

public:
		
	static const int CHARACTERS = 0;
	static const int BASICTILES = 1;
	static const int WALLPAPER  = 2;
	static const int LOGO = 3;
	static const int MAINMENUSHADE = 4;
	static const int GUI_BUTTON = 5;
	static const int GUI_CONTROLLS = 6;

	SpriteSheet(std::string name, SDL_Renderer* renderer, int spriteWidth, int spriteHeight, int imagesEnum);
	~SpriteSheet();

	int getWidth();
	int getHeight();
	int getTileWidth();
	int getTileHeight();
	SDL_Texture* getTexture();
	int getColumns();

	void draw(SDL_Renderer* renderer, SDL_Rect* clip, int x, int y, float scale);
	
private:
	SDL_Texture* texture;
	std::string name;
	int width;
	int height;
	int tileWidth;
	int tileHeight;
	int id;

};

#endif
