/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _GUIELEMENT_H_
#define _GUIELEMENT_H_
#pragma once

#include <SDL.h>
#include "DungeonEngine.h"


class GUIElement {

public:
	GUIElement();
	GUIElement(DungeonEngine* engine);
	~GUIElement();

	virtual void input(SDL_Event* event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	typedef struct Listeners {
		bool onFocus;
		bool onFocusLost;
		bool onMouseButtonLeftDown;
		bool onMouseButtonLeftUp;
		bool onMouseButtonLeftClicked;
		bool onMouseButtonRightDown;
		bool onMouseButtonRightUp;
		bool onMouseButtonRightClicked;
	} Listeners;

protected:
	DungeonEngine* engine;

	int x;
	int y;
	int width;
	int height;

};

#endif
