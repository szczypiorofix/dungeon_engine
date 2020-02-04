/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainMenuState.h"


MainMenuState::MainMenuState() {

}


MainMenuState::~MainMenuState() {


}


void MainMenuState::update() {

}


void MainMenuState::input(SDL_Event* event) {
    
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_ESCAPE:
            //this->engine->setQuit(true);
            std::cout << "QUIT..." << std::endl;
            break;
        }
    }

}


void MainMenuState::render() {

}

