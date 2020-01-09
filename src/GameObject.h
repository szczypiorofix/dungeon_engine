#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#pragma once

#include "Vector2.h"


enum Direction {
	DIR_UP = 0,
	DIR_RIGHT = 1,
	DIR_DOWN = 2,
	DIR_LEFT = 3,
	DIR_UP_RIGHT = 4,
	DIR_DOWN_RIGHT = 5,
	DIR_DOWN_LEFT = 6,
	DIR_UP_LEFT = 7
};


class GameObject
{

public:

	GameObject();
	GameObject(Vector2* vec, int width, int height);
	~GameObject();

	int getTileX(unsigned int tileWidth);
	int getTileY(unsigned int tileHeight);

	Vector2* mVector;
	int mWidth;
	int mHeight;

};

#endif
