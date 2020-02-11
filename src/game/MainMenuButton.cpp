/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainMenuButton.h"
#include "../dng_engine/GameState.h"
#include "../dng_engine/FontAssets.h"


MainMenuButton::MainMenuButton(GLfloat x, GLfloat y, GLfloat width, GLfloat height, std::string text, Texture* bt) {
    this->text = text;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->buttonTexture = bt;

    this->textFont = FontAssets::getAssets()->fonts[FontAssets::FONT_ASSETS_VINGUE];
    
    this->listeners = {false};
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
    GLfloat yOffset = 0.0f; // offset to Y when is focus on button or/and button is pressed
    TextureRect tempClip;
    if (this->listeners.onFocus) {
        tempClip = { 0, 32, 168, 32 };
        if (this->listeners.onMouseButtonLeftDown) {
            tempClip = { 0, 64, 168, 32 };
            yOffset = 3.0f;
        }
        else {
            yOffset = 1.0f;
        }
    }
    else {
        tempClip = { 0, 0, 168, 32 };
    }
    
    TextureRect dest = {
        this->x,
        this->y,
        168,
        32
    };
    this->buttonTexture->draw(tempClip, dest);

    this->textFont->draw(this->text.c_str(), this->x + 28.0f, this->y + 8.0f + yOffset, 0.25f);
    
}

