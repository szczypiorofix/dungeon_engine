/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _MAINGAMESTATE_H_
#define _MAINGAMESTATE_H_
#pragma once

#include "../dng_engine/GameState.h"


class MainGameState : public GameState {

public:

	MainGameState();
	~MainGameState();

	virtual void input(SDL_Event* event);
	virtual void update();
	virtual void render();
};

#endif
