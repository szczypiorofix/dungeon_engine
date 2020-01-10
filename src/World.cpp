#include <iostream>
#include <cstdlib>
#include "World.h"
#include "GraphicAssets.h"
#include "Defines.h"


World::World(SDL_Renderer* renderer)
	/*: mMap { 0 }*/
{
	mRenderer = renderer;
	mMap[0] = 0;
	vec = new Vector2(0.0f, 0.0f);
	moveVec = new Vector2(0.0f, 0.0f);

	prepareBackground();
	randomBackground();
}

World::~World() {
}

void World::prepareBackground() {
	std::cout << "Preparing background of the world." << std::endl;
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			mMap[i * MAP_WIDTH + j] = BGRND_GRASS1;
		}
	}
}

void World::randomBackground() {
	std::cout << "Randomize background of the world." << std::endl;
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			
			if ( (rand() % 100) > 70 && i > 0 && i < MAP_HEIGHT-1 && j > 0 && j < MAP_WIDTH-1 ) {
				mMap[i * MAP_WIDTH + j] = BGRND_GRASS2;
			}
			
		}
	}
}

void World::render(float scale) {

	int col = GraphicAssets::getAssets()->spriteSheets[SpriteSheet::BASICTILES]->getColumns();
	int tileWidth = GraphicAssets::getAssets()->spriteSheets[SpriteSheet::BASICTILES]->getTileWidth();
	int tileHeight = GraphicAssets::getAssets()->spriteSheets[SpriteSheet::BASICTILES]->getTileHeight();

	for (int i = 0; i < currentWorldSize; i++) {
			
		SDL_Rect tempClip = { 
			( mMap[i] % col )  * tileWidth,
			( mMap[i] / col )  * tileHeight,
			tileWidth,
			tileHeight
		};
			
		GraphicAssets::getAssets()->spriteSheets[SpriteSheet::BASICTILES]->draw(
			mRenderer,
			&tempClip,
			(int) ( ( ( i % MAP_WIDTH ) * tileWidth  * scale) - vec->x),
			(int) ( ( ( i / MAP_WIDTH ) * tileHeight * scale) - vec->y),
			scale);
	}
}

void World::update(float scale) {
	vec->x += (moveVec->x * scale);
	vec->y += (moveVec->y * scale);
}
