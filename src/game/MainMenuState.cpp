/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainMenuState.h"



MainMenuState::MainMenuState(DungeonEngine* engine, State* s) {
    this->engine = engine;
    this->state = s;

    this->backgroundImageTexture = engine->loadTexture("background.png");

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
    //SDL_Rect tempClip = { 0, 0, 800, 600 };
    //this->engine->drawImage(SpriteSheet::WALLPAPER, tempClip, 0, 0);

    //tempClip = { 0, 0, 800, 600 };
    //this->engine->drawImage(SpriteSheet::MAINMENUSHADE, tempClip, 0, 0);

    //tempClip = { 0, 0, 335, 201 };
    //this->engine->drawImage(SpriteSheet::LOGO, tempClip, 210, 15);

    //for (int i = 0; i < MAX_BUTTONS; i++) {
    //    this->buttons[i]->render();
    //}

    //this->textFont->draw("MAIN MENU", 10, 10, .5f, this->engine->scale);



    // Texture
    glColor4ub(255, 255, 255, 255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->backgroundImageTexture);

    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

        glTexCoord2i(0, 0);
        glVertex2f(0, 0);

        glTexCoord2i(1, 0);
        glVertex2f(800, 0);

        glTexCoord2i(1, 1);
        glVertex2f(800, 600);

        glTexCoord2i(0, 1);
        glVertex2f(0, 600);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    //// Hello World Triangle
    glBegin(GL_TRIANGLES); //GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON
        glColor3ub(255, 0, 0);
        glVertex2f(400, 200);
        glColor3ub(0, 255, 0);
        glVertex2f(600, 400);
        glColor3ub(0, 0, 255);
        glVertex2f(200, 400);
    glEnd();

}

