/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "GUIElement.h"


GUIElement::GUIElement() {
	this->engine = nullptr;
    this->focusListenerSet = false;
    this->mouseClickedLeftListenerSet = false;
}


GUIElement::GUIElement(DungeonEngine* engine) {
	this->engine = engine;
}



GUIElement::~GUIElement() {

}


void GUIElement::addListener(void (*funcCallback)(), DNG_Events eventType) {
    switch (eventType) {
    case DNG_Events::ON_FOCUS:
        this->focusListenerSet = true;
        this->focusCallback = funcCallback;
        break;
    case DNG_Events::ON_FOCUS_LOST:
        this->focusLostListenerSet = true;
        this->focusLostCallback = funcCallback;
        break;
    case DNG_Events::ON_MOUSE_CLICKED_LEFT:
        this->mouseClickedLeftListenerSet = true;
        this->mouseClickedLeftCallback = funcCallback;
        break;
    case DNG_Events::ON_MOUSE_CLICKED_RIGHT:
        this->mouseClickedRightListenerSet = true;
        this->mouseClickedRightCallback = funcCallback;
        break;
    }
}

