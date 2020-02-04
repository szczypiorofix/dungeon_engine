/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#pragma once

#include <SDL.h>

class GameState {

public:

	GameState();
	~GameState();

	virtual void input(SDL_Event* event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

private:



};

#endif // !_GAMESTATE_H_
