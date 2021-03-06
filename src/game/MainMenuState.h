/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _MAINMENUSTATE_H_
#define _MAINMENUSTATE_H_
#pragma once

#include "../dng_engine/GameState.h"
#include "../dng_engine/Texture.h"
#include "../dng_engine/TextFont.h"
#include "MainMenuButton.h"



class MainMenuState : public GameState {

public:

	MainMenuState(DungeonEngine* engine, State* s);
	~MainMenuState(void);

	virtual void input(SDL_Event* event);
	virtual void update(void);
	virtual void render(void);

	// Buttons
	constexpr static int NEWGAME_BUTTON = 0;
	constexpr static int OPTIONS_BUTTON = 1;
	constexpr static int EXIT_BUTTON = 2;

	constexpr static int MAX_BUTTONS = 3;

private:
	//TextFont* textFont;
	MainMenuButton** buttons;
	
	Texture* backgroundTexture;
	Texture* logoTexture;
	Texture* testTexture;
	Texture* mainMenuButtonsTexture;
	Texture* vingueFontTexture;

	State* state;
};


#endif
