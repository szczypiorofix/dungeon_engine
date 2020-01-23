/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#pragma once

#include "Vector2.h"


class GameObject {

public:

	GameObject();
	GameObject(Vector2* vec, int width, int height);
	~GameObject();

	int getTileX(unsigned int tileWidth);
	int getTileY(unsigned int tileHeight);

	Vector2* vector;
	int width;
	int height;

};

#endif
