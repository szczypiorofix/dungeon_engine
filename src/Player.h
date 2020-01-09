#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once

#include <iostream>
#include <SDL.h>
#include "Vector2.h"
#include "Animation.h"
#include "GameObject.h"


class Player : public GameObject
{

public:
	Player(std::string name, float x, float y, int width, int height, SDL_Renderer* renderer);
	~Player();

	Vector2* mMoveVector;

	std::string getName();
	float getSpeed();
	int getWidth();
	int getHeight();
	int getTileX();
	int getTileY();
	int getTileIndex();
	bool isMoving();
	SDL_Rect getCollision();
	Animation** getAnimation();

	void draw(float scale, float ox, float oy);
	void update(float scale);

	void setAnimation(Animation** anim);

	void setDirection(Direction dir);
	void setMoving(bool moving);

	Direction getDirection();

private:
	std::string mName;
	float mSpeed;
	int mTileX;
	int mTileY;
	int mTileIndex;
	bool mMoving;
	SDL_Rect mCol;
	Direction mDirection;
	SDL_Renderer* mRenderer;
	Animation** mWalkingAnimation;
};

#endif
