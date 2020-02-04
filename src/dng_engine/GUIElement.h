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

protected:
	DungeonEngine* engine;

};

#endif
