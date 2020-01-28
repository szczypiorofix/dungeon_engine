/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _DUNGEONGAME_H_
#define _DUNGEONGAME_H_
#pragma once

#include <iostream>
#include "../dng_engine/DungeonEngine.h"
#include "../dng_engine/SpriteSheet.h"
#include "../dng_engine/TiledMap.h"
#include "../dng_engine/Vector2.h"
#include "../dng_engine/TextFont.h"
#include "Player.h"


class DungeonGame : public DungeonEngine {

public:
	DungeonGame();
	~DungeonGame();
	void launch(void);

private:

	DungeonEngine* engine;
	Player* player;
	TiledMap* tiledMap;
	Camera* camera;
	Vector2* currentLockVector;
	TextFont* textFont;

	const float SCROLL_SPEED = 32.0f;

	void gameLoop();
	void input(SDL_Event* event);
	void update();
	void render();

};


#endif
