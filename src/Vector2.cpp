#include "Vector2.h"


Vector2::Vector2() {
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float vx, float vy) {
	x = vx;
	y = vy;
}

Vector2::~Vector2() {
	x = 0.0f;
	y = 0.0f;
}

Vector2 Vector2::operator+(Vector2 v) {
	return Vector2( x + v.x, y + v.y );
}

Vector2& Vector2::operator+=(Vector2& v) {
	x += v.x;
	y += v.y;
	return *this;
}
