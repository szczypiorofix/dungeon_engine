#ifndef _CAMERA_H_
#define _CAMERA_H_
#pragma once

#include "Vector2.h"

class Camera
{
public:
	Camera();
	Camera(float cx, float cy);
	Camera(Vector2 camVec);
	~Camera();
	Vector2* vec;

	float* mLockCameraOnObjectX;
	float* mLockCameraOnObjectY;

	void update(float scale);
	void lockCameraOnObject(float *x, float *y);
	void lockCameraOnObject(Vector2* lv);

};

#endif
