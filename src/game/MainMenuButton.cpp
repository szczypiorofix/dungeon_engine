/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainMenuButton.h"


MainMenuButton::MainMenuButton(DungeonEngine* engine, int x, int y, int width, int height, std::string text) {
    this->engine = engine;
    this->text = text;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;



    this->focus = false;
    this->mouseClicked = false;
    
    this->textFont = new TextFont(engine->getRenderer(), "vingue");
}


MainMenuButton::~MainMenuButton() {

}


void MainMenuButton::input(SDL_Event* event) {
    if (event->type == SDL_MOUSEMOTION) {
        if (event->motion.x > this->x && event->motion.x < this->x + this->width && event->motion.y > this->y && event->motion.y < this->y + this->height) {
            
            if (this->focusListenerSet && !this->focus) {
                (*this->focusCallback) ();
            }

            this->focus = true;
        } else {
            
            if (this->focusLostListenerSet && this->focus) {
                (*this->focusLostCallback) ();
            }

            this->focus = false;
        }
    }
    if (this->focus) {
        if (event->button.type == SDL_MOUSEBUTTONDOWN) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                this->mouseClicked = true;
                if (this->mouseClickedLeftListenerSet) {
                    (*this->mouseClickedLeftCallback) ();
                }
            }
            else if (event->button.button == SDL_BUTTON_RIGHT) {
                if (this->mouseClickedRightListenerSet) {
                    (*this->mouseClickedRightCallback) ();
                }
            }
        }
        else if (event->button.type == SDL_MOUSEBUTTONUP) {
            this->mouseClicked = false;
        }
    }
}


void MainMenuButton::update() {

}


void MainMenuButton::render() {
    int yOffset = 0; // offset to Y when is focus on button or/and button is pressed
    SDL_Rect tempClip;
    if (this->focus) {
        tempClip = { 0, 32, 168, 32 };
        if (this->mouseClicked) {
            tempClip = { 0, 64, 168, 32 };
            yOffset = 3;
        }
        else {
            yOffset = 1;
        }
    }
    else {
        tempClip = { 0, 0, 168, 32 };
    }
    
    engine->drawImage(SpriteSheet::GUI_BUTTON, tempClip, this->x, this->y);
    this->textFont->draw(this->text.c_str(), this->x + 28, this->y + 8 + yOffset, 0.25f, 1.0f);
    
}


