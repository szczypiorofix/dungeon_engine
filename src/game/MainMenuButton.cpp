/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainMenuButton.h"


MainMenuButton::MainMenuButton(DungeonEngine* engine, int x, int y, std::string text) {
    this->engine = engine;
    this->text = text;
    this->x = x;
    this->y = y;
    this->focus = false;
    this->press = false;
    this->textFont = new TextFont(engine->getRenderer(), "vingue");
}


MainMenuButton::~MainMenuButton() {

}


void MainMenuButton::input(SDL_Event* event) {
    if (event->type == SDL_MOUSEMOTION) {
        if (event->motion.x > this->x && event->motion.x < this->x + 168 && event->motion.y > this->y && event->motion.y < this->y + 34) {
            this->focus = true;
        } else {
            this->focus = false;
        }
    }
    if (event->button.type == SDL_MOUSEBUTTONDOWN) {
        if (event->button.button == SDL_BUTTON_LEFT) {
            this->press = true;

        }
    }
    else if (event->button.type == SDL_MOUSEBUTTONUP) {
        this->press = false;
    }
}


void MainMenuButton::update() {

}


void MainMenuButton::render() {
    
    SDL_Rect tempClip;
    if (this->focus) {
        tempClip = { 0, 34, 168, 32 };
        if (this->press) {
            tempClip = { 0, 68, 168, 28 };
            engine->drawImage(SpriteSheet::GUI_BUTTON, tempClip, this->x, this->y + 4);
        }
        else {
            engine->drawImage(SpriteSheet::GUI_BUTTON, tempClip, this->x, this->y + 2);
        }
    }
    else {
        tempClip = { 0, 0, 168, 32 };
        engine->drawImage(SpriteSheet::GUI_BUTTON, tempClip, this->x, this->y);
    }
    
    this->textFont->draw(this->text.c_str(), this->x, this->y, 0.25f, this->engine->scale);
    
}


