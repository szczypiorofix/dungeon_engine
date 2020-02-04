/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "GUIElement.h"


GUIElement::GUIElement() {
	this->engine = nullptr;
}


GUIElement::GUIElement(DungeonEngine* engine) {
	this->engine = engine;
}



GUIElement::~GUIElement() {

}


