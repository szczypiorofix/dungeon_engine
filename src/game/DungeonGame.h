/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _DUNGEONGAME_H_
#define _DUNGEONGAME_H_
#pragma once

#include <iostream>
#include "../dng_engine/Game.h"
#include "MainMenuState.h"
#include "MainGameState.h"

enum class State {
	SPLASH_SCREEN,
	MAIN_MENU,
	OPTIONS,
	MAIN_GAME
};

class DungeonGame : public Game {

public:
	DungeonGame();
	~DungeonGame();

	void launch(void);

	virtual void input(SDL_Event* event);
	virtual void update();
	virtual void render();

	State state;
	MainMenuState* mainMenuState;
	MainGameState* mainGameState;

private:
	
	

	const float SCROLL_SPEED = 32.0f;


};


#endif
