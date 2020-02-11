/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _MAINMENUBUTTON_H_
#define _MAINMENUBUTTON_H_
#pragma once

#include "../dng_engine/GUIElement.h"
#include "../dng_engine/GameState.h"
#include "../dng_engine/Texture.h"
#include "../dng_engine/TextFont.h"



class MainMenuButton : public GUIElement {

public:
    MainMenuButton(GLfloat x, GLfloat y, GLfloat width, GLfloat height, std::string text, Texture* buttonTexture, Texture* fontTexture);
    ~MainMenuButton();

    virtual void input(SDL_Event* event);
    virtual void update();
    virtual void render();

    Listeners listeners;
    Texture* buttonTexture;
    Texture* fontTexture;

private:

    TextFont* textFont;
    std::string text;
    
};



#endif
