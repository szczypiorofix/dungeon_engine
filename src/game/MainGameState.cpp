/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainGameState.h"



MainGameState::MainGameState(DungeonEngine* engine, int* s) {
    this->engine = engine;
    this->state = s;

    this->backToMenuButton = new MainMenuButton(this->engine, 270, 200, 168, 34, "MAIN MENU");

    this->textFont = this->engine->createFont("vingue", true);
}


MainGameState::~MainGameState() {}


void MainGameState::input(SDL_Event* event) {
    
    this->backToMenuButton->input(event);

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
    this->backToMenuButton->update();

    if (this->backToMenuButton->listeners.onMouseButtonClickedLeft.active) {
        *this->state = 0;
    }

}


void MainGameState::render() {
    this->textFont->draw("MAIN GAME", 10, 50, 0.5f, this->engine->scale);

    this->backToMenuButton->render();

}

