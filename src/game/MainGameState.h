/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _MAINGAMESTATE_H_
#define _MAINGAMESTATE_H_
#pragma once

#include "../dng_engine/GameState.h"
#include "MainMenuButton.h"


class MainGameState : public GameState {

public:

	MainGameState(DungeonEngine* engine, State* s);
	~MainGameState();

	virtual void input(SDL_Event* event);
	virtual void update();
	virtual void render();

private:
	TextFont* textFont;
	
	MainMenuButton* backToMenuButton;

	State* state;
};

#endif
