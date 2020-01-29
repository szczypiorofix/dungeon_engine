/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "Camera.h"
#include "DungeonEngine.h"


Camera::Camera() {
	this->vec = new Vector2(0.0f, 0.0f);
	this->lockCameraOnObjectX = nullptr;
	this->lockCameraOnObjectY = nullptr;
}


Camera::Camera(float x, float y) {
	this->vec = new Vector2(x, y);
	this->lockCameraOnObjectX = nullptr;
	this->lockCameraOnObjectY = nullptr;
}


Camera::Camera(Vector2 vec) {
	this->vec = new Vector2(vec);
	this->lockCameraOnObjectX = nullptr;
	this->lockCameraOnObjectY = nullptr;
}


void Camera::update(float scale) {
	this->vec->x = (*this->lockCameraOnObjectX * scale) - (DungeonEngine::SCREEN_WIDTH / 2);
	this->vec->y = (*this->lockCameraOnObjectY * scale) - (DungeonEngine::SCREEN_HEIGHT / 2);
}


Camera::~Camera() {
	this->vec = nullptr;
	this->lockCameraOnObjectX = nullptr;
	this->lockCameraOnObjectY = nullptr;
}


void Camera::lockCameraOnObject(float* x, float* y) {
	 this->lockCameraOnObjectX = x;
	 this->lockCameraOnObjectY = y;
}


void Camera::lockCameraOnObject(Vector2* lv) {
	this->lockCameraOnObjectX = &lv->x;
	this->lockCameraOnObjectY = &lv->y;
}
