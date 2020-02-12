/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#pragma once

#include <SDL2/SDL.h>
#include "DungeonEngine.h"


enum class State {
	MAIN_MENU,
	MAIN_GAME
};


class GameState {

public:

	GameState(void);
	GameState(DungeonEngine* engine);
	~GameState(void);

	virtual void input(SDL_Event* event) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;

protected:

	DungeonEngine* engine;

};

#endif // !_GAMESTATE_H_
