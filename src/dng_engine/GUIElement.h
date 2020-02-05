/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _GUIELEMENT_H_
#define _GUIELEMENT_H_
#pragma once

#include <SDL.h>
#include "DungeonEngine.h"



enum class DNG_Events {
	ON_FOCUS,
	ON_FOCUS_LOST,
	ON_MOUSE_CLICKED_LEFT,
	ON_MOUSE_CLICKED_RIGHT
};



class GUIElement {

public:
	GUIElement();
	GUIElement(DungeonEngine* engine);
	~GUIElement();

	virtual void input(SDL_Event* event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;


protected:
	DungeonEngine* engine;

	int x;
	int y;
	int width;
	int height;

};

#endif
