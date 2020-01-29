/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _ENGINE_H_
#define _ENGINE_H_
#pragma once

#include "../dng_engine/DungeonEngine.h"
#include "../dng_engine/Camera.h"
#include "../dng_engine/TiledMap.h"


class Game {

public:

	Game();
	~Game();


protected:
    DungeonEngine* engine;
    Camera* camera;
    TiledMap* tiledMap;

    virtual void input(SDL_Event* event) = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    
    void gameLoop();
    

private:

    void DE_GameLoop();
    void DE_Input(SDL_Event* event);
    void DE_Update();
    void DE_Render();

};

#endif