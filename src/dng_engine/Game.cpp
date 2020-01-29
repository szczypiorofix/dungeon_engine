/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "Game.h"


Game::Game() {
    
	std::cout << "Game::constructor" << std::endl;

    this->camera = nullptr;
    this->engine = new DungeonEngine();
	this->engine->launchSubsystems();

}

Game::~Game() {
	
}



void Game::gameLoop() {
	this->DE_GameLoop();
}


void Game::DE_GameLoop() {
	
	SDL_Event event;
	this->engine->initTimer();

	while (!this->engine->isQuit()) {

		this->DE_Input(&event);
		this->DE_Update();
		this->DE_Render();

	}

	this->engine->stop();
}

void Game::DE_Input(SDL_Event* event) {
	while (SDL_PollEvent(event) != 0) {
		if (event->type == SDL_QUIT) {
			this->engine->setQuit(true);
		} else {
			this->input(event);
		}	
	}
}

void Game::DE_Update() {
	this->update();
}

void Game::DE_Render() {
	SDL_SetRenderDrawColor(this->engine->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(this->engine->getRenderer());

	// Render start

	this->render();

	// Render end

	SDL_RenderPresent(this->engine->getRenderer());
}

