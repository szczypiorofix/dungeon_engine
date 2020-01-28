/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once

#include <iostream>
#include <SDL.h>

#include "../dng_engine/Defines.h"
#include "../dng_engine/Vector2.h"
#include "../dng_engine/Animation.h"
#include "GameObject.h"


class Player : public GameObject {

public:
	Player(std::string name, float x, float y, int width, int height, SDL_Renderer* renderer);
	~Player();

	Vector2* moveVector;

	std::string name;
	float speed;
	int tileX;
	int tileY;
	int tileIndex;
	bool moving;
	SDL_Rect col;
	int direction;
	Animation** walkingAnimation;

	void draw(float scale, float x, float y);
	void update(float scale);

private:
	SDL_Renderer* renderer;
};

#endif
