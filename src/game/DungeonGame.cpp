/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "DungeonGame.h"




DungeonGame::DungeonGame() {

	this->mainMenuState = nullptr;
	this->mainGameState = nullptr;
	this->currentState = nullptr;

	this->state = State::MAIN_MENU;

}


DungeonGame::~DungeonGame() {}


void DungeonGame::input(SDL_Event* event) {

	if (event->type == SDL_KEYDOWN) {
		switch (event->key.keysym.sym) {
			case SDLK_1:
				std::cout << "switching to main menu state" << std::endl;
				this->state = State::MAIN_MENU;
				break;
			case SDLK_2:
				std::cout << "switching to main game state" << std::endl;
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
	
	this->mainMenuState = new MainMenuState(this->engine, &this->state);
	this->mainGameState = new MainGameState(this->engine, &this->state);
	
	this->currentState = this->mainMenuState;

	

	// engine->loadMusic("ex-aws_cave.xm");
	engine->loadMusic("menu-music.ogg");
	engine->playMusic(true, 25);

	/*engine->loadImageToAssets("dg_humans32.png", 32, 32, SpriteSheet::CHARACTERS);
	engine->loadImageToAssets("dg_grounds32.png", 32, 32, SpriteSheet::BASICTILES);
	
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
