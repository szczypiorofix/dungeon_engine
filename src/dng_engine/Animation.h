/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#pragma once

#include <SDL.h>
#include "Spritesheet.h"


class Animation {

public:
	Animation(SpriteSheet* spriteSheet, unsigned short speed, unsigned int sw, unsigned int sh, const unsigned short size, const unsigned int* frames);
	~Animation();
	int nextFrame();
	SDL_Rect getFrame(int index);
	int getCurFrame();
	void setCurrentFrame(int curFrame);

private:
	unsigned short size;
	SDL_Rect* frames;
	unsigned short speed;
	int curFrame;
	int counter;
	SpriteSheet* spriteSheet;

};

#endif
