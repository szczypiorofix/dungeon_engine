/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */


#include "Vector2.h"


Vector2::Vector2() {
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2::~Vector2() {
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2 Vector2::operator+(Vector2 v) {
	return Vector2(this->x + v.x, this->y + v.y );
}

Vector2& Vector2::operator+=(Vector2& v) {
	this->x += v.x;
	this->y += v.y;
	return *this;
}
