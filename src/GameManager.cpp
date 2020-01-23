/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "GameManager.h"
#include <SDL.h>
#include "Animation.h"
#include "GraphicAssets.h"
#include "LuaHandler.h"


GameManager::GameManager() {
	this->engine = new Engine();
	this->player = nullptr;
	this->camera = nullptr;
	this->world = nullptr;
	this->tiledMap = nullptr;
	this->textFont = nullptr;
	this->currentLockVector = new Vector2(0.0f, 0.0f);
}

GameManager::~GameManager() {
}


void GameManager::gameLoop() {

	this->textFont = this->engine->createFont("vingue", true);

	this->engine->loadMusic("ex-aws_cave.xm");
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(this->engine->getMusic(), -1); // -1 play forever, 0 - no play
		Mix_VolumeMusic(this->engine->settings.musicVolume);
	}

	GraphicAssets::getAssets()->loadAsset("characters.png", this->engine->getRenderer(), 16, 16, SpriteSheet::CHARACTERS);
	GraphicAssets::getAssets()->loadAsset("basictiles.png", this->engine->getRenderer(), 16, 16, SpriteSheet::BASICTILES);

	this->world = new World(this->engine->getRenderer());

	this->tiledMap = new TiledMap("worldmap.tmx");

	LuaHandler* lua = new LuaHandler("script.lua");

	this->player = lua->getPlayer(this->engine->getRenderer());
	if (this->player) {
		std::cout << "Object 'Player' was found. Player name: " << this->player->name << std::endl;
		std::cout << "X: " << this->player->vector->x << ", Y: " << this->player->vector->y << ", player width: " << this->player->width << ", height: " << this->player->height << std::endl;
	}
	else {
		std::cout << "Cannot read object 'Player'." << std::endl;
	}

	delete lua;
	//this->player = new Player("Player", 0.0f, 0.0f, 16, 16, this->engine->getRenderer());
	
	this->camera = new Camera();
	//camera->lockCameraOnObject(&player->mVector->x, &player->mVector->y);

	this->currentLockVector = this->world->moveVector;
	this->camera->lockCameraOnObject(this->currentLockVector);

	SDL_Event event;
	this->engine->initTimer();
	while (!this->engine->isQuit()) {
		
		input(&event);
		update();
		render();

	}

	this->engine->stop();
}

void GameManager::input(SDL_Event* event) {
	
	while (SDL_PollEvent(event) != 0) {
		if (event->type == SDL_QUIT) {
			this->engine->setQuit(true);
		}
		else if (event->type == SDL_MOUSEWHEEL) {
			if (event->button.x == 1) {
				if (this->engine->scale < Engine::MAX_SCALE) this->engine->scale += 0.25f;
			}
			else if (event->button.x == -1) {
				if (this->engine->scale > Engine::MIN_SCALE) this->engine->scale -= 0.25f;
			}
		}
		else if (event->type == SDL_KEYDOWN) {
			switch (event->key.keysym.sym) {
				case SDLK_ESCAPE:
					this->engine->setQuit(true);
					break;
				case SDLK_LEFT:
				case SDLK_a:
					this->currentLockVector->x = -SCROLL_SPEED;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					this->currentLockVector->x = SCROLL_SPEED;
					break;
				case SDLK_UP:
				case SDLK_w:
					this->currentLockVector->y = -SCROLL_SPEED;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					this->currentLockVector->y = SCROLL_SPEED;
					break;
			}
		}
		else if (event->type == SDL_KEYUP) {
			switch (event->key.keysym.sym) {
				case SDLK_LEFT:
				case SDLK_a:
					if (this->currentLockVector->x < 0) {
						this->currentLockVector->x = 0;
					}
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					if (this->currentLockVector->x > 0) {
						this->currentLockVector->x = 0;
					}
					break;
				case SDLK_UP:
				case SDLK_w:
					if (this->currentLockVector->y < 0) {
						this->currentLockVector->y = 0;
					}
				case SDLK_DOWN:
				case SDLK_s:
					if (this->currentLockVector->y > 0) {
						this->currentLockVector->y = 0;
					}
					break;
			}
		}
	}
}

void GameManager::update() {

	this->world->update(this->engine->scale);

	//player->update(engine->scale);


	this->camera->update(this->engine->scale);

}

void GameManager::render() {
	SDL_SetRenderDrawColor(this->engine->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(this->engine->getRenderer());

	// Render start


	this->world->render(this->engine->scale); // , -camera->vec->x, -camera->vec->y);

	//player->draw(engine->scale, -camera->vec->x, -camera->vec->y);

	this->textFont->draw("DUPA BLADA", 10, 50, 0.5f, this->engine->scale);


	// Render end

	SDL_RenderPresent(this->engine->getRenderer());
}

void GameManager::launch(void) {
	this->engine->launchSubsystems();
	this->gameLoop();
}
