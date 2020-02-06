/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "MainMenuButton.h"
#include "../dng_engine/GameState.h"


MainMenuButton::MainMenuButton(DungeonEngine* engine, int x, int y, int width, int height, std::string text, State* state) {
    this->engine = engine;
    this->text = text;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->state = state;

    this->listeners.onFocus = {false, false, NULL};
    this->listeners.onFocusLost = { false, false, NULL };
    this->listeners.onMouseButtonClickedLeft = { false, false, NULL };
    this->listeners.onMouseButtonClickedRight = { false, false, NULL };
    
    this->textFont = new TextFont(engine->getRenderer(), "vingue");
}


MainMenuButton::~MainMenuButton() {

}


void MainMenuButton::input(SDL_Event* event) {
    if (event->type == SDL_MOUSEMOTION) {
        if (event->motion.x > this->x && event->motion.x < this->x + this->width && event->motion.y > this->y && event->motion.y < this->y + this->height) {
            if (this->listeners.onFocus.set && !this->listeners.onFocus.active) {
                (this->*listeners.onFocus.callback) ();
            }
            this->listeners.onFocus.active = true;
        } else {
            
            if (this->listeners.onFocusLost.set && this->listeners.onFocus.active) {
                (this->*listeners.onFocusLost.callback) ();
            }
            this->listeners.onFocus.active = false;
        }
    }
    if (this->listeners.onFocus.active) {
        if (event->button.type == SDL_MOUSEBUTTONDOWN) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                this->listeners.onMouseButtonClickedLeft.active = true;
                if (this->listeners.onMouseButtonClickedLeft.set) {
                    (this->*listeners.onMouseButtonClickedLeft.callback) ();
                }
            }
            else if (event->button.button == SDL_BUTTON_RIGHT) {
                this->listeners.onMouseButtonClickedRight.active = true;
                if (this->listeners.onMouseButtonClickedRight.set) {
                    (this->*listeners.onMouseButtonClickedRight.callback) ();
                }
            }
        }
        else if (event->button.type == SDL_MOUSEBUTTONUP) {
            this->listeners.onMouseButtonClickedLeft.active = false;
            this->listeners.onMouseButtonClickedRight.active = false;
        }
    }
}


void MainMenuButton::update() {
    
}


void MainMenuButton::render() {
    int yOffset = 0; // offset to Y when is focus on button or/and button is pressed
    SDL_Rect tempClip;
    if (this->listeners.onFocus.active) {
        tempClip = { 0, 32, 168, 32 };
        if (this->listeners.onMouseButtonClickedLeft.active) {
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


void MainMenuButton::addListener(void (MainMenuButton::*funcCallback)(), DNG_Events eventType) {
    switch (eventType) {
    case DNG_Events::ON_FOCUS:
        this->listeners.onFocus.set = true;
        this->listeners.onFocus.callback = funcCallback;
        break;
    case DNG_Events::ON_FOCUS_LOST:
        this->listeners.onFocusLost.set = true;
        this->listeners.onFocusLost.callback = funcCallback;
        break;
    case DNG_Events::ON_MOUSE_CLICKED_LEFT:
        this->listeners.onMouseButtonClickedLeft.set = true;
        this->listeners.onMouseButtonClickedLeft.callback = funcCallback;
        break;
    case DNG_Events::ON_MOUSE_CLICKED_RIGHT:
        this->listeners.onMouseButtonClickedRight.set = true;
        this->listeners.onMouseButtonClickedRight.callback = funcCallback;
        break;
    }
}


void MainMenuButton::fl() {
    std::cout << "ON FOCUS LOST" << std::endl;
}

void MainMenuButton::f() {
    std::cout << "ON FOCUS" << std::endl;
}

void MainMenuButton::ml() {
    std::cout << "ON MOUSE CLICKED LEFT" << std::endl;
}

void MainMenuButton::mr() {
    std::cout << "ON MOUSE CLICKED RIGHT" << std::endl;
}

void MainMenuButton::quitAction() {
    this->engine->setQuit(true);
}

void MainMenuButton::newGameAction() {
    State s = State::MAIN_GAME;
    this->state = &s;
    std::cout << "NEW GAME" << std::endl;
}
