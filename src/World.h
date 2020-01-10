#ifndef _WORLD_H_
#define _WORLD_H_
#pragma once

#include <SDL.h>
#include "Vector2.h"


class World
{

public:
	World(SDL_Renderer* renderer);
	~World();

	void update(float scale);

	void render(float scale);

	constexpr static int MAP_WIDTH = 40;
	constexpr static int MAP_HEIGHT = 32;

	Vector2* vec;
	Vector2* moveVec;

	/*
	* BLOCKS TYPES
	*/

	const int BGRND_GRASS1 = 11;
	const int BGRND_GRASS2 = 12;



	int mMap[MAP_WIDTH * MAP_HEIGHT];

	int currentWorldSize = MAP_WIDTH * MAP_HEIGHT;

private:
	SDL_Renderer* mRenderer;

	void prepareBackground();
	void randomBackground();

};

#endif
