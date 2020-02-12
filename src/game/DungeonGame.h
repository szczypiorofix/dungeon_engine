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


/**
Dungeon Game main class. Extends Game class and its virtual methods: input, update and render.
It holds 2 (for now) States: Main Menu State and Main Game State, both with separate game loop implementations.
*/
class DungeonGame : public Game {

public:
	DungeonGame(void);
	~DungeonGame(void);

	void launch(void);

	virtual void input(SDL_Event* event);
	virtual void update(void);
	virtual void render(void);

	MainMenuState* mainMenuState;
	MainGameState* mainGameState;

	GameState* currentState;

private:

};


#endif
