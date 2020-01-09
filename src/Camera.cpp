#include "Camera.h"
#include "Engine.h"


Camera::Camera() {
	vec = new Vector2(0.0f, 0.0f);
	mLockCameraOnObjectX = NULL;
	mLockCameraOnObjectY = NULL;
}

Camera::Camera(float cx, float cy) {
	vec = new Vector2(cx, cy);
	mLockCameraOnObjectX = NULL;
	mLockCameraOnObjectY = NULL;
}

Camera::Camera(Vector2 camVec) {
	vec = new Vector2(camVec);
	mLockCameraOnObjectX = NULL;
	mLockCameraOnObjectY = NULL;
}

void Camera::update(float scale) {
	vec->x = (*mLockCameraOnObjectX * scale) - (Engine::SCREEN_WIDTH / 2);
	vec->y = (*mLockCameraOnObjectY * scale) - (Engine::SCREEN_HEIGHT / 2);
}

Camera::~Camera() {
	vec = nullptr;
}

void Camera::lockCameraOnObject(float* x, float* y) {
	 mLockCameraOnObjectX = x;
	 mLockCameraOnObjectY = y;
}

void Camera::lockCameraOnObject(Vector2* lv) {
	mLockCameraOnObjectX = &lv->x;
	mLockCameraOnObjectY = &lv->y;
}
