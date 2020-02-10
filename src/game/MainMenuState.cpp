/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainMenuState.h"



MainMenuState::MainMenuState(DungeonEngine* engine, State* s) {
    this->engine = engine;
    this->state = s;

    this->backgroundTexture = new Texture("../res/images/background.png");
    this->logoTexture = new Texture("../res/images/logo-title.png");
    this->testTexture = new Texture("../res/images/dg_people32.png", 32, 32);
    this->mainMenuButtonsTexture = new Texture("../res/images/mm-gui-button.png", 168, 128);
    this->vingueFontTexture = new Texture("../res/fonts/vingue.png");

    this->buttons = new MainMenuButton*[MAX_BUTTONS];

    this->buttons[NEWGAME_BUTTON]   = new MainMenuButton(325, 260, 168, 34, "NEW GAME", this->mainMenuButtonsTexture, this->vingueFontTexture);
    this->buttons[OPTIONS_BUTTON]   = new MainMenuButton(325, 300, 160, 34, "OPTIONS", this->mainMenuButtonsTexture, this->vingueFontTexture);
    this->buttons[EXIT_BUTTON]      = new MainMenuButton(325, 340, 168, 34, "QUIT GAME", this->mainMenuButtonsTexture, this->vingueFontTexture);

    this->textFont = new TextFont("vingue", this->vingueFontTexture);
}


MainMenuState::~MainMenuState() {
    delete this->textFont;
}


void MainMenuState::update() {
    
    if (this->buttons[NEWGAME_BUTTON]->listeners.onMouseButtonLeftClicked) {
        *this->state = State::MAIN_GAME;
    }

    if (this->buttons[EXIT_BUTTON]->listeners.onMouseButtonLeftClicked) {
        this->engine->setQuit(true);
    }

    // !IMPORTANT TO CLEAR THE MOUSE CLICKED FLAG AFTER ANY AOTHER ACTIONS
    for (int i = 0; i < MAX_BUTTONS; i++) {
        this->buttons[i]->update();
    }
    
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
        }
    }

    for (int i = 0; i < MAX_BUTTONS; i++) {
        this->buttons[i]->input(event);
    }

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

    //this->testTexture->drawTile(6, 100, 100);


    for (int i = 0; i < MAX_BUTTONS; i++) {
        this->buttons[i]->render();
    }


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
