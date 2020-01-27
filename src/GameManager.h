/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#pragma once

#include <iostream>
#include "Engine.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "TiledMap.h"
#include "Vector2.h"
#include "TextFont.h"


class GameManager
{

public:
	GameManager();
	~GameManager();
	void launch(void);

private:

	Engine* engine;
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
