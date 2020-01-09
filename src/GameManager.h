#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#pragma once

#include <iostream>
#include "Engine.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "World.h"
#include "TiledMap.h"
#include "Vector2.h"



class GameManager
{

public:
	GameManager();
	~GameManager();
	void launch(void);

private:

	Engine* engine;
	Player* player;
	World* world;
	Camera* camera;
	Vector2* currentLockVector;

	const float SCROLL_SPEED = 2.0f;

	void gameLoop();
	void input(SDL_Event* event);
	void update();
	void render();
	void quit();

};


#endif
