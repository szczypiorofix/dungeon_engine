/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "GUIElement.h"


GUIElement::GUIElement() {
	this->engine = nullptr;
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
}


GUIElement::GUIElement(DungeonEngine* engine) {
	this->engine = engine;
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
}


GUIElement::~GUIElement() {

}
