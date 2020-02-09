/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainMenuButton.h"
#include "../dng_engine/GameState.h"



MainMenuButton::MainMenuButton(DungeonEngine* engine, int x, int y, int width, int height, std::string text) {
    this->engine = engine;
    this->text = text;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;    
    //this->textFont = new TextFont(engine->getRenderer(), "vingue");
    this->listeners = {false};
    this->selected = false;
}


MainMenuButton::~MainMenuButton() {}


void MainMenuButton::input(SDL_Event* event) {
    if (event->type == SDL_MOUSEMOTION) {
        if (event->motion.x > this->x && event->motion.x < this->x + this->width && event->motion.y > this->y && event->motion.y < this->y + this->height) {
            this->listeners.onFocus = true;
        } else {
            this->listeners.onFocus = false;
        }
    }
    if (this->listeners.onFocus) {
        if (event->button.type == SDL_MOUSEBUTTONDOWN) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                this->listeners.onMouseButtonLeftDown = true;
            }
            else if (event->button.button == SDL_BUTTON_RIGHT) {
                this->listeners.onMouseButtonRightDown = true;
            }
        }
        else if (event->button.type == SDL_MOUSEBUTTONUP) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                this->listeners.onMouseButtonLeftDown = false;
                this->listeners.onMouseButtonLeftClicked = true;
            }
            else if (event->button.button == SDL_BUTTON_RIGHT) {
                this->listeners.onMouseButtonRightDown = false;
                this->listeners.onMouseButtonRightClicked = true;
            }
        }
    }
}


void MainMenuButton::update() {
    this->listeners.onMouseButtonLeftClicked = false;
    this->listeners.onMouseButtonRightClicked = false;
}


void MainMenuButton::render(void) {
    int yOffset = 0; // offset to Y when is focus on button or/and button is pressed
    SDL_Rect tempClip;
    if (this->listeners.onFocus) {
        tempClip = { 0, 32, 168, 32 };
        if (this->listeners.onMouseButtonLeftDown) {
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

    if (this->selected) {
        tempClip = { 0, 96, 168, 32 };
        engine->drawImage(SpriteSheet::GUI_BUTTON, tempClip, this->x, this->y);
    }

    this->textFont->draw(this->text.c_str(), this->x + 28, this->y + 8 + yOffset, 0.25f, 1.0f);
    
}


void MainMenuButton::setSelected(bool s) {
    this->selected = s;
}

