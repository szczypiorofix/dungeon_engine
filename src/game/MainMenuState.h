/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _MAINMENUSTATE_H_
#define _MAINMENUSTATE_H_
#pragma once

#include "../dng_engine/GameState.h"
#include "MainMenuButton.h"



class MainMenuState : public GameState {

public:

	MainMenuState(DungeonEngine* engine, State* s);
	~MainMenuState();

	virtual void input(SDL_Event* event);
	virtual void update();
	virtual void render();


private:
	TextFont* textFont;
	MainMenuButton* newGameButton;
	MainMenuButton* exitButton;
	
	State* state;
};


#endif
