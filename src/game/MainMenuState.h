/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _MAINMENUSTATE_H_
#define _MAINMENUSTATE_H_
#pragma once

#include "../dng_engine/GameState.h"


class MainMenuState : public GameState {

public:

	MainMenuState();
	~MainMenuState();

	virtual void update();
	virtual void input(SDL_Event* event);
	virtual void render();


private:


};


#endif
