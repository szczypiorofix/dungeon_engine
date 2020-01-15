#ifndef _CAMERA_H_
#define _CAMERA_H_
#pragma once

#include "Vector2.h"

class Camera
{
public:
	Camera();
	Camera(float x, float y);
	Camera(Vector2 vec);
	~Camera();
	Vector2* vec;

	float* lockCameraOnObjectX;
	float* lockCameraOnObjectY;

	void update(float scale);
	void lockCameraOnObject(float *x, float *y);
	void lockCameraOnObject(Vector2* lv);

};

#endif
