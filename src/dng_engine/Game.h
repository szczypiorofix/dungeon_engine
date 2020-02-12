/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _ENGINE_H_
#define _ENGINE_H_
#pragma once


#include "DungeonEngine.h"
#include "Camera.h"
#include "TiledMap.h"
#include "GameState.h"



/**
Main Game class. Does all the stuff with initializing game engine, starting video and audio subsystems. It holds
main game loop with input, update and render parts.
*/
class Game {

public:
	Game(void);
	~Game(void);


protected:
    DungeonEngine* engine;
    Camera* camera;
    TiledMap* tiledMap;

    virtual void input(SDL_Event* event) = 0;
    virtual void update(void) = 0;
    virtual void render(void) = 0;
    
    void gameLoop(void);
    
    State state;

    bool fpsCap;
    int ticks;
    int fps;

private:

    void DE_Input(SDL_Event* event);
    void DE_Update(void);
    void DE_Render(void);

};

#endif
