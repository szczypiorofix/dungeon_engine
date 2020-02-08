/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "Game.h"


Game::Game() {
	std::cout << "Game::constructor" << std::endl;
	this->tiledMap = nullptr;
    this->camera = nullptr;
    this->engine = new DungeonEngine();
	this->engine->launchSubsystems();
	this->fpsCap = true;
	this->fps = 0;
	this->ticks = 0;
}


Game::~Game() {
}


void Game::gameLoop() {
	this->DE_GameLoop();
}


void Game::DE_GameLoop() {
	
	SDL_Event event;
	this->engine->initTimer();

	double start = SDL_GetTicks();
	double renderTimer = 0, viewTimer = 0;

	int _f = 0, _t = 0;
	double lag = 0.0f;
	double elapsed = 0.0f;
	double previous = SDL_GetTicks();

	constexpr float FRAMES = 60.0f;
	constexpr float TICKS = 30.0f;

	const double MS_PER_UPDATE = 1000.0f / TICKS;
	const double MS_PER_RENDER = 1000.0f / FRAMES;

	while (!this->engine->isQuit()) {

		start = SDL_GetTicks();
		elapsed = start - previous;
		previous = start;
		lag += elapsed;

		viewTimer += elapsed;
		renderTimer += elapsed;

		while (lag >= MS_PER_UPDATE) {
			this->DE_Input(&event);
			this->DE_Update();
			_t++;
			lag -= MS_PER_UPDATE;
		}


		if (fpsCap) {
			if (renderTimer >= MS_PER_RENDER) {
				this->DE_Render();
				renderTimer = 0;
				_f++;
			}
		} else {
			this->DE_Render();
			renderTimer = 0;
			_f++;
		}

		if (viewTimer >= 1000) {
			this->fps = _f;
			this->ticks = _t;
			std::cout << "Wait one second. FPS: " << this->fps << ", TICKS: " << this->ticks << std::endl;
			_f = 0;
			_t = 0;
			viewTimer = 0;
		}

	}

	this->engine->stop();
}


void Game::DE_Input(SDL_Event* event) {
	while (SDL_PollEvent(event) != 0) {
		if (event->type == SDL_QUIT) {
			this->engine->setQuit(true);
		} else {
			this->input(event);
			if (event->type == SDL_KEYDOWN) {
				switch (event->key.keysym.sym) {

				case SDLK_F5:
					this->fpsCap = !this->fpsCap;
					std::cout << "Switching V-SYNC to " << (this->fpsCap ? " ON." : " OFF") << std::endl;
					break;

				}
			}
		}	
	}
}


void Game::DE_Update() {
	this->update();
}


void Game::DE_Render() {
	SDL_SetRenderDrawColor(this->engine->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(this->engine->getRenderer());

	// --------------------------- Render start ---------------------------

	this->render();

	// ---------------------------- Render end ----------------------------

	SDL_RenderPresent(this->engine->getRenderer());
}
