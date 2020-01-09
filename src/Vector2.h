#ifndef _VECTOR2_H_
#define _VECTOR2_H_
#pragma once

class Vector2
{
public:
	Vector2();
	Vector2(float vx, float vy);
	~Vector2();

	float x;
	float y;

	Vector2 operator+(Vector2 v);

	Vector2& operator+=(Vector2& v);

};

#endif
