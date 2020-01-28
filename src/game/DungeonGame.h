/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _DUNGEONGAME_H_
#define _DUNGEONGAME_H_
#pragma once

#include <iostream>
#include "../dng_engine/Game.h"
#include "Player.h"


class DungeonGame : public Game {

public:
	DungeonGame();
	~DungeonGame();

	void launch(void);

	virtual void input();
	virtual void update();
	virtual void render();

private:
	
	
	Player* player;
	//TiledMap* tiledMap;
	
	Vector2* currentLockVector;
	TextFont* textFont;

	const float SCROLL_SPEED = 32.0f;


};


#endif
