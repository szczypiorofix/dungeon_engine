/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainGameState.h"
#include "../dng_engine/GraphicAssets.h"
#include "../dng_engine/FontAssets.h"


MainGameState::MainGameState(DungeonEngine* engine, State* s) {
    this->engine = engine;
    this->state = s;

    this->mainMenuButtonsTexture = GraphicAssets::getAssets()->textures[GraphicAssets::IMAGE_ASSETS_MAIN_MENU_BUTTONS];
    this->vingueFontTexture = GraphicAssets::getAssets()->textures[GraphicAssets::IMAGE_ASSETS_VINGUE_FONT];
    this->backToMenuButton = new MainMenuButton(325, 200, 168, 34, "MAIN MENU", this->mainMenuButtonsTexture);

    this->textFont = FontAssets::getAssets()->fonts[FontAssets::FONT_ASSETS_VINGUE];
}


MainGameState::~MainGameState(void) {}


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


void MainGameState::update(void) {
    
    if (this->backToMenuButton->listeners.onMouseButtonLeftClicked) {
        *this->state = State::MAIN_MENU;
    }

    //// !IMPORTANT TO CLEAR THE MOUSE CLICKED FLAG AFTER ANY AOTHER ACTIONS
    this->backToMenuButton->update();

}


void MainGameState::render(void) {

    this->textFont->draw("MAIN GAME", 280, 50, 0.5f);

    this->backToMenuButton->render();

}

