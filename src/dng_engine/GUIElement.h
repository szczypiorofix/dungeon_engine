/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _GUIELEMENT_H_
#define _GUIELEMENT_H_
#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

class GUIElement {

public:
	GUIElement();
	~GUIElement();

	virtual void input(SDL_Event* event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	typedef struct Listeners {
		bool onFocus;
		bool onFocusLost;
		bool onMouseButtonLeftDown;
		bool onMouseButtonLeftClicked;
		bool onMouseButtonRightDown;
		bool onMouseButtonRightClicked;
	} Listeners;

protected:

	GLfloat x;
	GLfloat y;
	GLfloat width;
	GLfloat height;

};

#endif
