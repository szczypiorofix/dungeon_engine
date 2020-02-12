/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _MAINGAMESTATE_H_
#define _MAINGAMESTATE_H_
#pragma once

#include "../dng_engine/GameState.h"
#include "../dng_engine/TextFont.h"
#include "MainMenuButton.h"



class MainGameState : public GameState {

public:

	MainGameState(DungeonEngine* engine, State* s);
	~MainGameState(void);

	virtual void input(SDL_Event* event);
	virtual void update(void);
	virtual void render(void);

private:
	TextFont* textFont;
	Texture* mainMenuButtonsTexture;
	Texture* vingueFontTexture;
	MainMenuButton* backToMenuButton;

	State* state;

};

#endif
