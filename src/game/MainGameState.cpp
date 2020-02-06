/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainGameState.h"



MainGameState::MainGameState(DungeonEngine* engine, State* state) {
    this->engine = engine;
    this->state = state;
    this->textFont = this->engine->createFont("vingue", true);
}


MainGameState::~MainGameState() {



}


void MainGameState::input(SDL_Event* event) {
    
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_ESCAPE:
            this->engine->setQuit(true);
            break;
        case SDLK_SPACE:
            std::cout << "THIS IS MAIN GAME STATE" << std::endl;
            break;
        }
    }

}


void MainGameState::update() {

}


void MainGameState::render() {
    this->textFont->draw("MAIN GAME", 10, 50, 0.5f, this->engine->scale);
}

