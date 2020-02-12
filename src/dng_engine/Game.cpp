/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include <iostream>
#include "Game.h"


Game::Game(void) {
	//this->tiledMap = nullptr;
 //   this->camera = nullptr;
    this->engine = new DungeonEngine();
	this->engine->launchSubsystems();
	this->fpsCap = false;
	this->fps = 0;
	this->ticks = 0;
}


Game::~Game(void) {}


void Game::gameLoop(void) {
	
	SDL_Event event;

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
#ifdef _DEBUG 
			std::cout << "FPS: " << this->fps << ", UPDATE: " << this->ticks << std::endl;
#endif			
			_f = 0;
			_t = 0;
			viewTimer = 0;
		}

		// 1ms nap for my CPU
		SDL_Delay(1);

		//this->DE_Input(&event);
		//this->DE_Update();
		//this->DE_Render();

		//SDL_Delay(1000.0f / 60.0f);
	}

	this->engine->stop();
}


void Game::DE_Input(SDL_Event* event) {
	while (SDL_PollEvent(event) != 0) {
		if (event->type == SDL_QUIT) {
			this->engine->setQuit(true);
		} 
		// WINDOW EVENTS
		else if (event->type == SDL_WINDOWEVENT) {
			switch (event->window.event) {
			case SDL_WINDOWEVENT_SHOWN:
				SDL_Log("Window %d shown", event->window.windowID);
				break;
			case SDL_WINDOWEVENT_HIDDEN:
				SDL_Log("Window %d hidden", event->window.windowID);
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				SDL_Log("Window %d exposed", event->window.windowID);
				break;
			case SDL_WINDOWEVENT_MOVED:
				SDL_Log("Window %d moved to %d,%d", event->window.windowID, event->window.data1, event->window.data2);
				break;
			case SDL_WINDOWEVENT_RESIZED:
				SDL_Log("Window %d resized to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				SDL_Log("Window %d size changed to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				SDL_Log("Window %d minimized", event->window.windowID);
				break;
			case SDL_WINDOWEVENT_MAXIMIZED:
				SDL_Log("Window %d maximized", event->window.windowID);
				break;
			case SDL_WINDOWEVENT_RESTORED:
				SDL_Log("Window %d restored", event->window.windowID);
				break;
			case SDL_WINDOWEVENT_ENTER:
				SDL_Log("Mouse entered window %d", event->window.windowID);
				break;
			case SDL_WINDOWEVENT_LEAVE:
				SDL_Log("Mouse left window %d", event->window.windowID);
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				SDL_Log("Window %d gained keyboard focus", event->window.windowID);
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				SDL_Log("Window %d lost keyboard focus", event->window.windowID);
				break;
			case SDL_WINDOWEVENT_CLOSE:
				SDL_Log("Window %d closed", event->window.windowID);
				break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
			case SDL_WINDOWEVENT_TAKE_FOCUS:
				SDL_Log("Window %d is offered a focus", event->window.windowID);
				break;
			case SDL_WINDOWEVENT_HIT_TEST:
				SDL_Log("Window %d has a special hit test", event->window.windowID);
				break;
#endif
			default:
				SDL_Log("Window %d got unknown event %d",
					event->window.windowID, event->window.event);
				break;
			}
		} 
		else {

			// GAME STATES EVENTS
			this->input(event);
			
			// VSYNC ON/OFF
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


void Game::DE_Update(void) {

	this->update();

}


void Game::DE_Render(void) {

	// ######################## OPENGL ########################

	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glOrtho(0, DungeonEngine::SCREEN_WIDTH, DungeonEngine::SCREEN_HEIGHT, 0, -1, 1); // Set the matrix

	// ================================= Render Start =================================
	
	this->render();

	// ================================== Render End ==================================

	glPopMatrix();
	SDL_GL_SwapWindow(this->engine->getWindow());

}
