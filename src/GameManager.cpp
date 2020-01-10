#include "GameManager.h"

#include <SDL.h>
#include "Animation.h"
#include "GraphicAssets.h"


GameManager::GameManager() {
	engine = new Engine();
	player = NULL;
	camera = NULL;
	world = NULL;
	currentLockVector = new Vector2(0.0f, 0.0f);
	textFont = NULL;
}

GameManager::~GameManager() {
}


void GameManager::gameLoop() {

	textFont = new TextFont(engine->getRenderer(), "vingue");

	engine->loadMusic("ex-aws_cave.xm");
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(engine->getMusic(), -1); // -1 play forever, 0 - no play
	}

	GraphicAssets::loadAsset("characters.png", engine->getRenderer(), 16, 16, SpriteSheet::CHARACTERS);
	GraphicAssets::loadAsset("basictiles.png", engine->getRenderer(), 16, 16, SpriteSheet::BASICTILES);

	world = new World(engine->getRenderer());

	player = new Player("Player", 0.0f, 0.0f, 16, 16, engine->getRenderer());
	
	camera = new Camera();
	//camera->lockCameraOnObject(&player->mVector->x, &player->mVector->y);

	currentLockVector = world->moveVec;
	camera->lockCameraOnObject(currentLockVector);

	SDL_Event event;
	engine->initTimer();
	while (!engine->isQuit()) {
		
		input(&event);
		update();
		render();

	}

}

void GameManager::input(SDL_Event* event) {
	
	while (SDL_PollEvent(event) != 0) {
		if (event->type == SDL_QUIT) {
			engine->setQuit(true);
		}
		else if (event->type == SDL_MOUSEWHEEL) {
			if (event->button.x == 1) {
				if (engine->scale < Engine::MAX_SCALE) engine->scale += 0.25f;
			}
			else if (event->button.x == -1) {
				if (engine->scale > Engine::MIN_SCALE) engine->scale -= 0.25f;
			}
		}
		else if (event->type == SDL_KEYDOWN) {
			switch (event->key.keysym.sym) {
				case SDLK_ESCAPE:
					engine->setQuit(true);
					break;
				case SDLK_LEFT:
				case SDLK_a:
					currentLockVector->x = -SCROLL_SPEED;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					currentLockVector->x = SCROLL_SPEED;
					break;
				case SDLK_UP:
				case SDLK_w:
					currentLockVector->y = -SCROLL_SPEED;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					currentLockVector->y = SCROLL_SPEED;
					break;
			}
		}
		else if (event->type == SDL_KEYUP) {
			switch (event->key.keysym.sym) {
				case SDLK_LEFT:
				case SDLK_a:
					if (currentLockVector->x < 0) {
						currentLockVector->x = 0;
					}
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					if (currentLockVector->x > 0) {
						currentLockVector->x = 0;
					}
					break;
				case SDLK_UP:
				case SDLK_w:
					if (currentLockVector->y < 0) {
						currentLockVector->y = 0;
					}
				case SDLK_DOWN:
				case SDLK_s:
					if (currentLockVector->y > 0) {
						currentLockVector->y = 0;
					}
					break;
			}
		}
	}
}

void GameManager::update() {

	world->update(engine->scale);

	//player->update(engine->scale);

	

	camera->update(engine->scale);

}

void GameManager::render() {
	SDL_SetRenderDrawColor(engine->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(engine->getRenderer());

	// Render start


	world->render(engine->scale); // , -camera->vec->x, -camera->vec->y);

	//player->draw(engine->scale, -camera->vec->x, -camera->vec->y);



	// Render end

	SDL_RenderPresent(engine->getRenderer());
}

void GameManager::quit() {
	engine->engineStop();
}

void GameManager::launch(void) {
	engine->launchSubsystems();
	gameLoop();
}
