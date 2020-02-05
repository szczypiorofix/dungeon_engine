/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainMenuState.h"



MainMenuState::MainMenuState(DungeonEngine* engine) {
    this->engine = engine;

    void (MainMenuButton::*of)() = &MainMenuButton::f;
    void (MainMenuButton::*ofl)() = &MainMenuButton::fl;
    void (MainMenuButton::*oml)() = &MainMenuButton::ml;
    void (MainMenuButton::*omr)() = &MainMenuButton::mr;
    void (MainMenuButton::*qt)() = &MainMenuButton::quit;
    
    this->newGameButton = new MainMenuButton(this->engine, 270, 260, 168, 34, "NEW GAME");
    
    this->newGameButton->addListener(of, DNG_Events::ON_FOCUS);
    this->newGameButton->addListener(ofl, DNG_Events::ON_FOCUS_LOST);
    this->newGameButton->addListener(oml, DNG_Events::ON_MOUSE_CLICKED_LEFT);
    this->newGameButton->addListener(omr, DNG_Events::ON_MOUSE_CLICKED_RIGHT);


    this->exitButton = new MainMenuButton(this->engine, 270, 300, 168, 34, "QUIT GAME");
    this->exitButton->addListener(qt, DNG_Events::ON_MOUSE_CLICKED_LEFT);
    this->exitButton->addListener(of, DNG_Events::ON_FOCUS);
    this->exitButton->addListener(ofl, DNG_Events::ON_FOCUS_LOST);

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
    this->newGameButton->update();
    this->exitButton->update();
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

    this->newGameButton->input(event);
    this->exitButton->input(event);

}


void MainMenuState::render() {
    SDL_Rect tempClip = { 0, 0, 800, 600 };
    this->engine->drawImage(SpriteSheet::WALLPAPER, tempClip, 0, 0);

    tempClip = { 0, 0, 800, 600 };
    this->engine->drawImage(SpriteSheet::MAINMENUSHADE, tempClip, 0, 0);

    tempClip = { 0, 0, 335, 201 };
    this->engine->drawImage(SpriteSheet::LOGO, tempClip, 210, 15);

    this->newGameButton->render();
    this->exitButton->render();

    //this->textFont->draw("MAIN MENU", 10, 10, .5f, this->engine->scale);
}

