/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _MAINMENUBUTTON_H_
#define _MAINMENUBUTTON_H_
#pragma once

#include "../dng_engine/GUIElement.h"
#include "../dng_engine/GameState.h"
#include "../dng_engine/Actions.h"


class MainMenuButton : public GUIElement {

public:
    MainMenuButton(DungeonEngine* engine, int x, int y, int width, int height, std::string text, State* state);
    ~MainMenuButton();

    typedef struct Listener {
        bool set, active;
        ActionsMemFn callback;
    } Listener;

    typedef struct Listeners {
        Listener onFocus;
        Listener onFocusLost;
        Listener onMouseButtonClickedLeft;
        Listener onMouseButtonClickedRight;
    } Listeners;

    virtual void input(SDL_Event* event);
    virtual void update();
    virtual void render();

    void addListener(ActionsMemFn funcCallback, DNG_Events eventType);


    // ACTIONS

    void fl();
    void f();
    void ml();
    void mr();

    void newGameAction();
    void quitAction();

private:

    TextFont* textFont;
    std::string text;
    State* state;
    Listeners listeners;

};



#endif
