/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _MAINMENUBUTTON_H_
#define _MAINMENUBUTTON_H_
#pragma once

#include "../dng_engine//GUIElement.h"



class MainMenuButton : public GUIElement {

public:
    MainMenuButton(DungeonEngine* engine, int x, int y, int width, int height, std::string text);
    ~MainMenuButton();

    virtual void input(SDL_Event* event);
    virtual void update();
    virtual void render();


private:


    bool focus;
    bool mouseClicked;

    TextFont* textFont;
    std::string text;


};



#endif
