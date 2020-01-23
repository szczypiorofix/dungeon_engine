/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "Camera.h"
#include "Engine.h"


Camera::Camera() {
	this->vec = new Vector2(0.0f, 0.0f);
	this->lockCameraOnObjectX = NULL;
	this->lockCameraOnObjectY = NULL;
}

Camera::Camera(float x, float y) {
	this->vec = new Vector2(x, y);
	this->lockCameraOnObjectX = NULL;
	this->lockCameraOnObjectY = NULL;
}

Camera::Camera(Vector2 vec) {
	this->vec = new Vector2(vec);
	this->lockCameraOnObjectX = NULL;
	this->lockCameraOnObjectY = NULL;
}

void Camera::update(float scale) {
	this->vec->x = (*this->lockCameraOnObjectX * scale) - (Engine::SCREEN_WIDTH / 2);
	this->vec->y = (*this->lockCameraOnObjectY * scale) - (Engine::SCREEN_HEIGHT / 2);
}

Camera::~Camera() {
	this->vec = nullptr;
}

void Camera::lockCameraOnObject(float* x, float* y) {
	 this->lockCameraOnObjectX = x;
	 this->lockCameraOnObjectY = y;
}

void Camera::lockCameraOnObject(Vector2* lv) {
	this->lockCameraOnObjectX = &lv->x;
	this->lockCameraOnObjectY = &lv->y;
}
