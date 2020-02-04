/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "GameState.h"


GameState::GameState() {
    this->engine = NULL;
}


GameState::GameState(DungeonEngine* engine) {
    this->engine = engine;
}


GameState::~GameState() {

}
