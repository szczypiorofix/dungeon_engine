/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainMenuState.h"


MainMenuState::MainMenuState(DungeonEngine* engine) {
    this->engine = engine;
    this->button1 = new MainMenuButton(engine, 60, 180, "NEW GAME");
    this->textFont = this->engine->createFont("vingue", true);
    this->engine->loadImageToAssets("world_map_wallpaper.jpg", 32, 32, SpriteSheet::WALLPAPER);
    this->engine->loadImageToAssets("logo-title.png", 32, 32, SpriteSheet::LOGO);
    this->engine->loadImageToAssets("mm-background-shade.png", 32, 32, SpriteSheet::MAINMENUSHADE);
    this->engine->loadImageToAssets("mm-gui-button.png", 32, 32, SpriteSheet::GUI_BUTTON);
    this->engine->loadImageToAssets("mm-gui-controlls.png", 32, 32, SpriteSheet::GUI_CONTROLLS);
}


MainMenuState::~MainMenuState() {

    delete this->textFont;

}


void MainMenuState::update() {
    this->button1->update();
}


void MainMenuState::input(SDL_Event* event) {
    //if (event->type == SDL_MOUSEWHEEL) {
    //    if (event->button.x == 1) {
    //        if (this->engine->scale < DungeonEngine::MAX_SCALE) this->engine->scale += 0.25f;
    //    }
    //    else if (event->button.x == -1) {
    //        if (this->engine->scale > DungeonEngine::MIN_SCALE) this->engine->scale -= 0.25f;
    //    }
    //}
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_ESCAPE:
            this->engine->setQuit(true);
            break;
        case SDLK_SPACE:
            std::cout << "THIS IS MAIN MENU STATE" << std::endl;
            break;
        }
    }

    this->button1->input(event);

}


void MainMenuState::render() {
    SDL_Rect tempClip = { 0, 0, 800, 600 };
    engine->drawImage(SpriteSheet::WALLPAPER, tempClip, 0, 0);

    tempClip = { 0, 0, 800, 600 };
    engine->drawImage(SpriteSheet::MAINMENUSHADE, tempClip, 0, 0);

    tempClip = { 0, 0, 335, 201 };
    engine->drawImage(SpriteSheet::LOGO, tempClip, 210, 15);

    button1->render();

    //this->textFont->draw("MAIN MENU", 10, 10, .5f, this->engine->scale);
}

