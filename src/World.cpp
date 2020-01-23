/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */


#include <iostream>
#include <cstdlib>
#include "World.h"
#include "GraphicAssets.h"
#include "Defines.h"


World::World(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->vector = new Vector2(0.0f, 0.0f);
	this->moveVector = new Vector2(0.0f, 0.0f);
}

World::~World() {
}

void World::render(float scale) {
	int col = GraphicAssets::getAssets()->spriteSheets[SpriteSheet::BASICTILES]->getColumns();
	int tileWidth = GraphicAssets::getAssets()->spriteSheets[SpriteSheet::BASICTILES]->getTileWidth();
	int tileHeight = GraphicAssets::getAssets()->spriteSheets[SpriteSheet::BASICTILES]->getTileHeight();



}

void World::update(float scale) {
	
}
