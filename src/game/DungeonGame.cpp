/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "DungeonGame.h"
#include "../dng_engine/GraphicAssets.h"
#include "../dng_engine/FontAssets.h"



DungeonGame::DungeonGame() {
	this->mainMenuState = nullptr;
	this->mainGameState = nullptr;
	this->currentState = nullptr;

	this->state = State::MAIN_MENU;
}


DungeonGame::~DungeonGame() {}


void DungeonGame::input(SDL_Event* event) {
	if (event->type == SDL_KEYUP) {
		switch (event->key.keysym.sym) {
		case SDLK_1:
			this->state = State::MAIN_MENU;
			break;
		case SDLK_2:
			this->state = State::MAIN_GAME;
			break;
		}
	}
	switch (this->state) {
		case State::MAIN_GAME:
			this->mainGameState->input(event);
			break;
		case State::MAIN_MENU:
			this->mainMenuState->input(event);
			break;
		default:
			exit(1);
			break;
	}

	/*if (event->type == SDL_MOUSEWHEEL) {
			if (event->button.x == 1) {
				if (this->engine->scale < DungeonEngine::MAX_SCALE) this->engine->scale += 0.25f;
			}
			else if (event->button.x == -1) {
				if (this->engine->scale > DungeonEngine::MIN_SCALE) this->engine->scale -= 0.25f;
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
		}*/

}


void DungeonGame::update() {

	switch (this->state) {
		case State::MAIN_GAME:
			this->mainGameState->update();
			break;
		case State::MAIN_MENU:
			this->mainMenuState->update();
			break;
		default:
			exit(1);
			break;
	}

}


void DungeonGame::render() {
	//for (int l = 0; l < this->tiledMap->map.layerCounter; l++) {
	//	for (int i = 0; i < this->tiledMap->map.width * this->tiledMap->map.height; i++) {
	//		int id = (this->tiledMap->map.layers[l]->data.arr[i]) - 1;
	//		int col = this->tiledMap->map.tileSets[0]->source->columns; // tilesets -> columns
	//		if (id > 0) {
	//			SDL_Rect tempClip = {
	//			((id % col) * this->tiledMap->map.tileWidth),
	//			((id / col) * this->tiledMap->map.tileHeight),
	//			this->tiledMap->map.tileWidth,
	//			this->tiledMap->map.tileHeight
	//			};

	//			engine->drawImage(
	//				SpriteSheet::BASICTILES,
	//				tempClip,
	//				(int)this->currentLockVector->x + ((i % this->tiledMap->map.layers[l]->width) * this->tiledMap->map.tileWidth),
	//				(int)this->currentLockVector->y + ((i / this->tiledMap->map.layers[l]->width) * this->tiledMap->map.tileHeight)
	//			);
	//		}			
	//	}
	//}

	//player->draw(engine->scale, -camera->vec->x, -camera->vec->y);


	switch (this->state) {
		case State::MAIN_GAME:
			this->mainGameState->render();
			break;
		case State::MAIN_MENU:
			this->mainMenuState->render();
			break;
		default:
			exit(1);
			break;
	}

}


void DungeonGame::launch(void) {
	std::cout << "Dungeon game launch" << std::endl;
	

	/*this->backgroundTexture = new Texture("../res/images/background.png");
	this->logoTexture = new Texture("../res/images/logo-title.png");
	this->testTexture = new Texture("../res/images/dg_people32.png", 32, 32);
	this->mainMenuButtonsTexture = new Texture("../res/images/mm-gui-button.png", 168, 128);
	this->vingueFontTexture = new Texture("../res/fonts/vingue.png");*/

	// LOADING GRAPHIC ASSETS
	GraphicAssets::addToAssets("../res/images/background.png", GraphicAssets::IMAGE_ASSETS_MAIN_MENU_BACKGROUND);
	GraphicAssets::addToAssets("../res/images/logo-title.png", GraphicAssets::IMAGE_ASSETS_LOGO);
	GraphicAssets::addToAssets("../res/images/mm-gui-button.png", 168, 128, GraphicAssets::IMAGE_ASSETS_MAIN_MENU_BUTTONS);
	GraphicAssets::addToAssets("../res/fonts/vingue.png", GraphicAssets::IMAGE_ASSETS_VINGUE_FONT);
	GraphicAssets::addToAssets("../res/images/dg_people32.png", 32, 32, GraphicAssets::IMAGE_ASSETS_TEST_TEXTURE);

	// LOADING FONT ASSETS
	FontAssets::addToAssets("vingue", GraphicAssets::getAssets()->textures[GraphicAssets::IMAGE_ASSETS_VINGUE_FONT], FontAssets::FONT_ASSETS_VINGUE);


	this->mainMenuState = new MainMenuState(this->engine, &this->state);
	this->mainGameState = new MainGameState(this->engine, &this->state);
	
	this->currentState = this->mainMenuState;

	// LOGGING SYSTEM
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
	SDL_LogError(SDL_LOG_PRIORITY_ERROR, "############# ERROR !!! ###############");
	// LOGGING SYSTEM


	engine->loadMusic("menu-music.ogg");
	engine->playMusic(true, 3);

	/*	
	this->tiledMap = new TiledMap("worldmap.tmx");*/


	//LuaHandler* lua = new LuaHandler("script.lua");
	//this->player = lua->getPlayer(this->engine->getRenderer());
	//if (this->player) {
	//	std::cout << "Object 'Player' was found. Player name: " << this->player->name << std::endl;
	//	std::cout << "X: " << this->player->vector->x << ", Y: " << this->player->vector->y << ", player width: " << this->player->width << ", height: " << this->player->height << std::endl;
	//} else {
	//	std::cout << "Cannot read object 'Player'." << std::endl;
	//}
	//delete lua;


	//this->player = new Player("Player", 0.0f, 0.0f, 16, 16, this->engine->getRenderer());
	//this->camera = new Camera();

	//this->currentLockVector = this->player->vector;

	//camera->lockCameraOnObject(&player->moveVector->x, &player->moveVector->y);

	this->gameLoop();
}
