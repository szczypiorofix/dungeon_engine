/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _WORLD_H_
#define _WORLD_H_
#pragma once

#include <SDL.h>
#include "Vector2.h"
#include "Level.h"


class World {

public:
	World(SDL_Renderer* renderer);
	~World();

	Vector2* moveVector;
	Vector2* vector;

	Level* currentLevel;

	void update(float scale);

	void render(float scale);


private:
	SDL_Renderer* renderer;

};

#endif
