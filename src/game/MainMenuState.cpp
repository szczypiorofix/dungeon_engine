/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainMenuState.h"



MainMenuState::MainMenuState(DungeonEngine* engine, State* s) {
    this->engine = engine;
    this->state = s;

    this->backgroundTexture = new Texture("background.png");
    this->logoTexture = new Texture("logo-title.png");
    this->testTexture = new Texture("dg_people32.png", 32, 32);

    //this->buttons = new MainMenuButton*[MAX_BUTTONS];

    //this->buttons[NEWGAME_BUTTON] = new MainMenuButton(this->engine, 270, 260, 168, 34, "NEW GAME");
    //this->buttons[OPTIONS_BUTTON] = new MainMenuButton(this->engine, 270, 300, 160, 34, "OPTIONS");
    //this->buttons[EXIT_BUTTON] = new MainMenuButton(this->engine, 270, 340, 168, 34, "QUIT GAME");

    //this->selectedButton = 0;
    //this->buttons[NEWGAME_BUTTON]->setSelected(true);

    //this->textFont = this->engine->createFont("vingue", true);
    //this->engine->loadImageToAssets("world_map_wallpaper.jpg", 32, 32, SpriteSheet::WALLPAPER);
    //this->engine->loadImageToAssets("logo-title.png", 32, 32, SpriteSheet::LOGO);
    //this->engine->loadImageToAssets("mm-background-shade.png", 32, 32, SpriteSheet::MAINMENUSHADE);
    //this->engine->loadImageToAssets("mm-gui-button.png", 32, 32, SpriteSheet::GUI_BUTTON);
    //this->engine->loadImageToAssets("mm-gui-controlls.png", 32, 32, SpriteSheet::GUI_CONTROLLS);
}


MainMenuState::~MainMenuState() {
    //delete this->textFont;
}


void MainMenuState::update() {
    
    //if (this->buttons[NEWGAME_BUTTON]->listeners.onMouseButtonLeftClicked) {
    //    *this->state = State::MAIN_GAME;
    //}

    //if (this->buttons[EXIT_BUTTON]->listeners.onMouseButtonLeftClicked) {
    //    this->engine->setQuit(true);
    //}

    //// !IMPORTANT TO CLEAR THE MOUSE CLICKED FLAG AFTER ANY AOTHER ACTIONS
    //for (int i = 0; i < MAX_BUTTONS; i++) {
    //    this->buttons[i]->update();
    //}
    
}


void MainMenuState::input(SDL_Event* event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_ESCAPE:
            this->engine->setQuit(true);
            break;
        case SDLK_SPACE:
            std::cout << "THIS IS MAIN MENU STATE" << std::endl;
            break;
        //case SDLK_UP:
        //    this->buttons[this->selectedButton]->setSelected(false);
        //    this->selectedButton--;
        //    if (this->selectedButton < 0) {
        //        this->selectedButton = MAX_BUTTONS - 1;
        //    }
        //    this->buttons[this->selectedButton]->setSelected(true);
        //    break;
        //case SDLK_DOWN:
        //    this->buttons[this->selectedButton]->setSelected(false);
        //    this->selectedButton++;
        //    if (this->selectedButton >= MAX_BUTTONS) {
        //        this->selectedButton = 0;
        //    }
        //    this->buttons[this->selectedButton]->setSelected(true);
        //    break;
        }
    }

    //for (int i = 0; i < MAX_BUTTONS; i++) {
    //    this->buttons[i]->input(event);
    //}

}


void MainMenuState::render() {

    TextureRect s = {
        0,
        0,
        928,
        792
    };
    TextureRect d = {
        0,
        0,
        800,
        600
    };
    this->backgroundTexture->draw(s, d);


    s = {
        0,
        0,
        335,
        201
    };
    d = {
        280,
        55,
        250,
        150
    };
    this->logoTexture->draw(s, d);


    this->testTexture->drawTile(7, 100, 100);

    //// Hello World Triangle
    //glBegin(GL_TRIANGLES); //GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON
    //    glColor3ub(255, 0, 0);
    //    glVertex2f(400, 200);
    //    glColor3ub(0, 255, 0);
    //    glVertex2f(600, 400);
    //    glColor3ub(0, 0, 255);
    //    glVertex2f(200, 400);
    //glEnd();

}
